#pragma once

#include <graphics.h>
#include  <string>
#include <tchar.h>

void DrawButton(int x1, int y1, int x2, int y2, int rx,int ry,COLORREF Color_Button);

void DrawButton(int x1, int y1, int x2, int y2, int rx, int ry, LPCTSTR Text, COLORREF Color_Button, COLORREF Color_Text, LPCTSTR Style,int Text_H);
