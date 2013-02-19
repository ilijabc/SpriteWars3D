/*
	by Ilija
*/


#include "Color.h"
#include "mymath.h"


//init common colors
Color Color::Transparent(0, 0, 0, 0);
Color Color::White(255, 255, 255);
Color Color::Black(0, 0, 0);
Color Color::Red(255, 0, 0);
Color Color::Green(0, 255, 0);
Color Color::Blue(0, 0, 255);
Color Color::Yellow(255, 255, 0);
Color Color::Gray(128, 128, 128);


void Color::addBrightness(s32 x)
{
	R = CLAMP(R + x, 0, 255);
	G = CLAMP(G + x, 0, 255);
	B = CLAMP(B + x, 0, 255);
}
