#ifndef COLOR_H
#define COLOR_H


#include "common.h"


struct Color
{
	Color()							{ R = 0; G = 0; B = 0; A = 255; }
	Color(u8 r, u8 g, u8 b)			{ R = r; G = g; B = b; A = 255; }
	Color(u8 a, u8 r, u8 g, u8 b)	{ R = r; G = g; B = b; A = a; }
	Color(const Color& c)			{ R = c.R; G = c.G; B = c.B; A = c.A; }
	Color(u32 c)
	{
		A = c >> 24;
		R = (c >> 16) & 0xFF;
		G = (c >> 8) & 0xFF;
		B = c & 0xFF;
	};

	inline f32 getRf() const { return (f32)R / 255.0f; }
	inline f32 getGf() const { return (f32)G / 255.0f; }
	inline f32 getBf() const { return (f32)B / 255.0f; }
	inline f32 getAf() const { return (f32)A / 255.0f; }

	u8 R, G, B, A;

	void addBrightness(s32 x);

	//common colors
	static Color Transparent;
	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color Yellow;
	static Color Gray;
};


#endif // COLOR_H
