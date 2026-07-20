#include "Draw.h"

void DrawButton(int x1, int y1, int x2, int y2, int rx, int ry, COLORREF Color_Button)
{
	setfillcolor(Color_Button);
	fillroundrect(x1, y1, x2, y2, rx, ry);
}

void DrawButton(int x1, int y1, int x2, int y2, int rx, int ry, LPCTSTR Text, COLORREF Color_Button, COLORREF Color_Text, LPCTSTR Style, int Text_H)
{
	setfillcolor(Color_Button);
	fillroundrect(x1, y1, x2, y2, rx, ry);

	settextstyle(Text_H,0,Style);
	settextcolor(Color_Text);
	setbkmode(TRANSPARENT);

	int tw = textwidth(Text);
	int th = textheight(Text);
	int Text_X = (x1 + x2 - tw) / 2;
	int Text_Y = (y1 + y2 - th) / 2;
	outtextxy(Text_X, Text_Y, Text);

}

void Draw_Text(int x, int y, LPCTSTR Text, COLORREF Color_Text, LPCTSTR Style, int Text_H)
{
	settextstyle(Text_H, 0, Style);
	settextcolor(Color_Text);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, Text);
}
