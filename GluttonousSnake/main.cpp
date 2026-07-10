#include <graphics.h>
#include <iostream>
using namespace std;

#define WINDOW_W 800
#define WINDOW_H 600
#define COLOR_BG RGB(255,255,255)

#define COLOR_BEGINBUTTON_UNCLICK RGB(25,55,109)
#define COLOR_BEGINBUTTON_CLICK RGB(70,130,180)
#define BEGINBUTTON_X1 250
#define BEGINBUTTON_Y1 100
#define BEGINBUTTON_X2 550
#define BEGINBUTTON_Y2 200
#define BEGINBUTTON_RX 50
#define BEGINBUTTON_RY 50
#define COLOR_BEGINBUTTON_TEXT RGB(255,255,255)
#define BEGINBUTTON_TEXT_H 80

void initial()
{
    initgraph(WINDOW_W, WINDOW_H);
    setbkcolor(COLOR_BG);
    cleardevice();

    setfillcolor(COLOR_BEGINBUTTON_UNCLICK);
    fillroundrect(BEGINBUTTON_X1, BEGINBUTTON_Y1, BEGINBUTTON_X2, BEGINBUTTON_Y2,
        BEGINBUTTON_RX, BEGINBUTTON_RY);

    settextstyle(BEGINBUTTON_TEXT_H, 0, _T("Consolas"));
    settextcolor(COLOR_BEGINBUTTON_TEXT);
    setbkmode(TRANSPARENT);

    int tw = textwidth(_T("START"));
    int th = textheight(_T("START"));
    int Text_X = (BEGINBUTTON_X1 + BEGINBUTTON_X2 - tw) / 2;
    int Text_Y = (BEGINBUTTON_Y1 + BEGINBUTTON_Y2 - th) / 2;
    outtextxy(Text_X, Text_Y, _T("START"));


    ExMessage msg;
    bool Correct_Click = false;

    while (1)
    {
        if (peekmessage(&msg, EX_MOUSE))
        {
            int Mouse_X = msg.x;
            int Mouse_Y = msg.y;
            bool inside = Mouse_X >= BEGINBUTTON_X1 && Mouse_X <= BEGINBUTTON_X2 &&
                Mouse_Y >= BEGINBUTTON_Y1 && Mouse_Y <= BEGINBUTTON_Y2;

            if (msg.message == WM_LBUTTONDOWN)
            {
                if (inside)
                {
                    break;
                }
            }
            else if (inside != Correct_Click)
            {
                Correct_Click = inside;
                setfillcolor(Correct_Click ? COLOR_BEGINBUTTON_CLICK : COLOR_BEGINBUTTON_UNCLICK);
                fillroundrect(BEGINBUTTON_X1, BEGINBUTTON_Y1, BEGINBUTTON_X2, BEGINBUTTON_Y2,
                    BEGINBUTTON_RX, BEGINBUTTON_RY);

                settextstyle(BEGINBUTTON_TEXT_H, 0, _T("Consolas"));
                settextcolor(COLOR_BEGINBUTTON_TEXT);
                setbkmode(TRANSPARENT);

                int Text_W = textwidth(_T("START"));
                int Text_H = textheight(_T("START"));
                int Text_X = (BEGINBUTTON_X1 + BEGINBUTTON_X2 - Text_W) / 2;
                int Text_Y = (BEGINBUTTON_Y1 + BEGINBUTTON_Y2 - Text_H) / 2;
                outtextxy(Text_X, Text_Y, _T("START"));
            }
        }
    }

    closegraph();
}

int main()
{
	initial();
    return 0;
}
