/**
Bitmap class - loads and displays Microsoft .bmp format
============   ========================================
Copyright (C) 2010  Alistair McMonnies.

Bitmap transparency code adapted from code by
Copyright (c) 2006, Daniel Livingstone

Original loader code adapted from code posted by
Copyright (C) 2006  Chris Backhouse.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*******************************************************
* alistair.mcmonnies@uws.ac.uk                        *
* daniel.livingstone@uws.ac.uk                        *
* cjbackhouse@hotmail.com 		www.backhouse.tk       *
*******************************************************

I would appreciate it if anyone using this in something cool would tell me
so I can see where it ends up.

=================
CLASS INFORMATION
=================

-------------
Bitmap class:
-------------
Takes a filename and (optionally) a boolean flag for transparency.
Creates an object that can be rendered in various ways into an OpenGL
display:
1) render the whole bitmap at 0, 0
2) render the whole bitmap at pos_x, pos_y
3) render a rectanglar area of the bitmap at pos_x, pos_y

----------------------------------
Loads: (thanks to Chris Backhouse)
----------------------------------
24bit bitmaps
256 colour bitmaps
16 colour bitmaps
2 colour bitmaps  (Thanks to Charles Rabier)

-------------
Restrictions:
-------------
This code is designed for use in openGL programs, so bitmaps not correctly padded will
not load properly, I believe this only applies to:
256cols if width is not a multiple of 4
16cols if width is not a multiple of 8
2cols if width is not a multiple of 32

OpenGL display needs to be scaled to pixel coordinates (or close) to prevent huge
over-stretching of bitmap's pixels.  Use (e.g.):
glOrtho2D(0, pixels_across, 0, pixels_up);  for origin at bottom-left.

In code that creates a mix of drawn and bitmapped graphics, if transparency is
applied to the bitmaps, all drawn vertices must also have alpha values - i.e.
use glColor4f() or glColor4fv() to set the colour of shapes drawn using:
glBegin(GL_XXX)...glEnd()

-------------
Sample code:
-------------
Bitmap *bmp = new Bitmap(filename, false);	// false = does not need transparency.
bmp->drawAt(10, 10);						// renders full bitmap at (10, 10)
bmp->drawAt(10, 100, 0, 0, 50, 80);			// renders bottom left 50x80 pixels at (10, 100).
*/

#include "Bitmap.h"
#include <gl/glut.h>

Bitmap::Bitmap(const char fname[], bool transparency){
	bytes = 0;					// Thanks and kudos to Ian McCulloch for pointing out 
	// that this is necessary.
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname);
}

Bitmap::Bitmap(std::string fname, bool transparency){
	bytes = 0;
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname.c_str());
}

void Bitmap::setCurrentImage(const char fname[], bool transparency){
	bytes = 0;
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname);
}

void Bitmap::setCurrentImage(std::string fname, bool transparency){
	withAlpha = transparency;
	loaded = false;
	BMPLoadGL(fname.c_str());
}

Bitmap::~Bitmap(){
	glDeleteTextures(1, &texture);
}

GLubyte& Bitmap::pixel(int x, int y, int c){
	if (withAlpha && loaded)
		return bytes[(y*width + x) * 4 + c];
	else
		return bytes[(y*width + x) * 3 + c];
}

void Bitmap::allocateMem(){
	// Note - only allocate 3 bytes per pixel for now - loader code is for a
	// plain bitmap.  BMPSetTransparency() re-allocates enough memory for
	// 4 bytes per pixel.
	bytes = new GLubyte[width*height * 3];
}

std::string TranslateBMPError(BMPError err)
{
	switch (err)
	{
	case(BMPNOTABITMAP) :
		return "This file is not a bitmap, specifically it doesn't start 'BM'";
	case(BMPNOOPEN) :
		return "Failed to open the file, suspect it doesn't exist";
	case(BMPFILEERROR) :
		return "ferror said we had an error. This error seems to not always mean anything, try ignoring it";
	case(BMPBADINT) :
		return "sizeof(int)!=4 quite a lot of rewriting probably needs to be done on the code";
	case(BMPNOERROR) :
		return "No errors detected";
	case(BMPUNKNOWNFORMAT) :
		return "Unknown bmp format, ie not 24bit, 256,16 or 2 colour";
	default:
		return "Not a valid error code";
	}
}

BMPError Bitmap::BMPSetTransparency(){
	// Make sure GL is set up to display images with transparency,,,
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Allocate enough memory for a RGBA bitmap...
	GLubyte *transTex = new GLubyte[height*width * 4];
	GLubyte r, g, b;
	GLubyte *src = bytes;
	// find out what colour is our transparent colour for this bitmap (the top-left pixel)...
	r = *src++;
	g = *src++;
	b = *src;
	// Now set source and destination pointers in preparation for transferring the pixels...
	src = bytes;
	GLubyte *dest = transTex;
	// iterate through image, set alpha = 0 for transparent bits
	for (int y = 0; y<height; y++)
	{
		for (int x = 0; x<width; x++)
		{
			*dest++ = *src++;
			*dest++ = *src++;
			*dest++ = *src++;
			if (*(dest - 3) == r && *(dest - 2) == g && *(dest - 1) == b)
				*dest++ = 0;
			else
				*dest++ = 255;
		}
	}
	// Can now get rid of the old (RGB) pixels...
	delete[] bytes;
	// ...and  replace with the new (RGBA) pixels...
	bytes = transTex;
	return BMPNOERROR;
}

BMPError Bitmap::BMPLoad(const char* fname)
{
	if (sizeof(int) != 4) return BMPBADINT;

	FILE* f = NULL;
	errno_t err = fopen_s(&f, fname, "rb");		//open for reading in binary mode
	if (err != 0) {
		return BMPNOOPEN;
	}
	char header[54];
	fread(header, 54, 1, f);			//read the 54byte main header

	if (header[0] != 'B' || header[1] != 'M') {
		fclose(f);
		return BMPNOTABITMAP;		//all bitmaps should start "BM"
	}

	//it seems gimp sometimes makes its headers small, so we have to do this. hence all the fseeks
	int offset = *(unsigned int*)(header + 10);

	width = *(int*)(header + 18);
	height = *(int*)(header + 22);
	//now the bitmap knows how big it is it can allocate its memory
	allocateMem();
	int bits = int(header[28]);		//colourdepth

	int x, y, c;
	BYTE cols[256 * 4];				//colourtable
	switch (bits)
	{
	case(24) :
		fseek(f, offset, SEEK_SET);
		fread(bytes, width*height * 3, 1, f);		//24bit is easy
		for (x = 0; x<width*height * 3; x += 3)			//except the format is BGR, grr
		{
			GLubyte temp = bytes[x];
			bytes[x] = bytes[x + 2];
			bytes[x + 2] = temp;
		}
		break;

	case(8) :
		fread(cols, 256 * 4, 1, f);						//read colortable
		fseek(f, offset, SEEK_SET);
		for (y = 0; y<height; ++y)						//(Notice 4bytes/col for some reason)
		for (x = 0; x<width; ++x)
		{
			GLubyte byte;
			fread(&byte, 1, 1, f);					//just read byte					
			for (int c = 0; c<3; ++c) {
				int cc = byte * 4 + 2 - c;
				pixel(x, y, c) = cols[cc];	//and look up in the table
			}
		}
		break;

	case(4) :
		fread(cols, 16 * 4, 1, f);
		fseek(f, offset, SEEK_SET);
		for (y = 0; y<256; ++y)
		for (x = 0; x<256; x += 2)
		{
			GLubyte byte;
			fread(&byte, 1, 1, f);						//as above, but need to exract two
			for (c = 0; c<3; ++c)						//pixels from each byte
				pixel(x, y, c) = cols[byte / 16 * 4 + 2 - c];
			for (c = 0; c<3; ++c)
				pixel(x + 1, y, c) = cols[byte % 16 * 4 + 2 - c];
		}
		break;

	case(1) :
		fread(cols, 8, 1, f);
		fseek(f, offset, SEEK_SET);
		for (y = 0; y<height; ++y)
		for (x = 0; x<width; x += 8)
		{
			BYTE byte;
			fread(&byte, 1, 1, f);
			//Every byte is eight pixels
			//so I'm shifting the byte to the relevant position, then masking out
			//all but the lowest bit in order to get the index into the colourtable.
			for (int x2 = 0; x2<8; ++x2)
			for (int c = 0; c<3; ++c)
				pixel(x + x2, y, c) = cols[((byte >> (7 - x2)) & 1) * 4 + 2 - c];
		}
		break;

	default:
		fclose(f);
		return BMPUNKNOWNFORMAT;
	}

	if (ferror(f))
	{
		fclose(f);
		return BMPFILEERROR;
	}
	loaded = true;
	fclose(f);
	return BMPNOERROR;
}

void Bitmap::drawTexture(float tex_x1, float tex_y1, float tex_x2, float tex_y2,
	int scr_x1, int scr_y1, int scr_x2, int scr_y2){
	// Draw a rectangle from a texture into a rectangle on the screen.
	// Orientation is determined by the correspondence from tex_ordinate to scr_ordinate.
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	switch (orient){
	case NORMAL:
		glTexCoord2d(tex_x1, tex_y1);	glVertex2d(scr_x1, scr_y1);
		glTexCoord2d(tex_x2, tex_y1);	glVertex2d(scr_x2, scr_y1);
		glTexCoord2d(tex_x2, tex_y2);	glVertex2d(scr_x2, scr_y2);
		glTexCoord2d(tex_x1, tex_y2);	glVertex2d(scr_x1, scr_y2);
		break;
	case MIRROR_X:
		glTexCoord2d(tex_x2, tex_y1);	glVertex2d(scr_x1, scr_y1);
		glTexCoord2d(tex_x1, tex_y1);	glVertex2d(scr_x2, scr_y1);
		glTexCoord2d(tex_x1, tex_y2);	glVertex2d(scr_x2, scr_y2);
		glTexCoord2d(tex_x2, tex_y2);	glVertex2d(scr_x1, scr_y2);
		break;
	case MIRROR_Y:
		glTexCoord2d(tex_x1, tex_y2);	glVertex2d(scr_x1, scr_y1);
		glTexCoord2d(tex_x2, tex_y2);	glVertex2d(scr_x2, scr_y1);
		glTexCoord2d(tex_x2, tex_y1);	glVertex2d(scr_x2, scr_y2);
		glTexCoord2d(tex_x1, tex_y1);	glVertex2d(scr_x1, scr_y2);
		break;
	case ROT_90:
		glTexCoord2d(tex_x1, tex_y2);	glVertex2d(scr_x1, scr_y1);
		glTexCoord2d(tex_x1, tex_y1);	glVertex2d(scr_x2, scr_y1);
		glTexCoord2d(tex_x2, tex_y1);	glVertex2d(scr_x2, scr_y2);
		glTexCoord2d(tex_x2, tex_y2);	glVertex2d(scr_x1, scr_y2);
		break;
	case ROT_180:
		glTexCoord2d(tex_x2, tex_y2);	glVertex2d(scr_x1, scr_y1);
		glTexCoord2d(tex_x1, tex_y2);	glVertex2d(scr_x2, scr_y1);
		glTexCoord2d(tex_x1, tex_y1);	glVertex2d(scr_x2, scr_y2);
		glTexCoord2d(tex_x2, tex_y1);	glVertex2d(scr_x1, scr_y2);
		break;
	case ROT_270:
		glTexCoord2d(tex_x2, tex_y1);	glVertex2d(scr_x1, scr_y1);
		glTexCoord2d(tex_x2, tex_y2);	glVertex2d(scr_x2, scr_y1);
		glTexCoord2d(tex_x1, tex_y2);	glVertex2d(scr_x2, scr_y2);
		glTexCoord2d(tex_x1, tex_y1);	glVertex2d(scr_x1, scr_y2);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* GL_QUADS drawing a texture at 0, 0
* ==================================
* This just draws the texture at full size (in pixel coordinates in this case)
* on to the display at the bottom-left corner.
*/
void Bitmap::draw() {
	drawTexture(0, 0, 1, 1, 0, 0, width, height);
}

void Bitmap::draw(int x, int y, int w, int h){
	drawTexture(0, 0, 1, 1, x, y, w, h);
}

/** GL_QUADS drawing a texture.
* ===========================
* The idea here is to draw the texture's vertices (anti-clockwise) into a screen
* area (specified, in this case, in pixel coordinates).  Each glTexCoord2d() indicates
* a point on the texture map (for a simple drawAt(), this is the corners) given in the
* range 0 -> 1. Each corresponding glVertex2d() gives the point on the display that the
* texture's corner will render to.  Because we are drawing at (pos_x, pos_y), the four
* corner points need to be exressed relative to this point.
*/
void Bitmap::drawAt(int pos_x, int pos_y){
	drawTexture(0, 0, 1, 1, pos_x, pos_y, pos_x + width, pos_y + height);
}

/** GL_QUADS drawing a retangular segment of a texture.
* ===================================================
* In this case, it is not the whole texture that is to be drawn.  The glTextCoord2d()
* ordinates given are (in this case) pixel coordinates within the texture map.  These
* have to be expressed as fractions of the texture width and height, so need to pre-
* calculate these (rx1, rx2, ry1, ry2) before doing the rendering.
*/
void Bitmap::drawAt(int pos_x, int pos_y, int seg_x, int seg_y, int seg_w, int seg_h){
	float rx1, ry1, rx2, ry2;
	rx1 = (float)seg_x / width;
	ry1 = (float)seg_y / height;
	rx2 = (float)(seg_x + seg_w) / width;
	ry2 = (float)(seg_y + seg_h) / height;
	drawTexture(rx1, ry1, rx2, ry2, pos_x, pos_y, pos_x + seg_w, pos_y + seg_h);
}

BMPError Bitmap::BMPLoadGL(const char fname[])
{
	BMPError e = BMPLoad(fname);
	if (e != BMPNOERROR) return e;
	orient = NORMAL;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (withAlpha) {
		BMPSetTransparency();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	delete[] bytes;
	return BMPNOERROR;
}
