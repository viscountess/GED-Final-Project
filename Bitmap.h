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

#ifndef BITMAP_H
#define BITMAP_H

#include <string>
typedef unsigned char BYTE;
#define BMPError char
#include<gl/glut.h>

enum Orientation{
	NORMAL,
	MIRROR_X,
	MIRROR_Y,
	ROT_90,
	ROT_180,
	ROT_270
};

class Bitmap
{
public:
	Bitmap(const char fname[], bool transparency = false);
	Bitmap(std::string fname, bool transparency = false);
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	void draw();	// Draw at
	void draw(int x, int y, int w, int h);
	void drawAt(int pos_x, int pos_y);
	void drawAt(int pos_x, int pos_y, int seg_x, int seg_y, int seg_w, int seg_h);
	void setCurrentImage(const char fname[], bool transparency = false);
	void setCurrentImage(std::string fname, bool transparency = false);
	void setOrientation(Orientation o){ orient = o; }
	Orientation getOrientation(){ return orient; }
	GLubyte* getBytes(){ return bytes; }
	~Bitmap();
private:
	BMPError BMPLoad(const char fname[]);
	BMPError BMPLoadGL(const char fname[]);
	BMPError BMPSetTransparency();
	void drawTexture(float tex_x1, float tex_y1, float text_x2, float tex_y2,
		int scr_x1, int scr_y1, int scr_x2, int scr_y2);
	GLubyte& pixel(int x, int y, int c);
	void allocateMem();
	int width, height;
	GLubyte* bytes;			///OpenGL formatted pixels
	GLuint texture;
	bool withAlpha;
	bool loaded;
	Orientation orient;
};

#define BMPNOTABITMAP 'b'	///Possible error flags
#define BMPNOOPEN 'o'
#define BMPFILEERROR 'f'
#define BMPBADINT 'i'
#define BMPNOERROR '\0'
#define BMPUNKNOWNFORMAT 'u'

///Translates BMPError error codes into English
std::string TranslateBMPError(BMPError err);

#endif
