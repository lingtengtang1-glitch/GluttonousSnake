#include <graphics.h>
#include <iostream>
using namespace std;

// Window properties
#define WINDOW_W 800
#define WINDOW_H 600
#define COLOR_BG RGB(255,255,255)

// Title properties
#define COLOR_TITLE RGB(25,55,109)
#define TITLE_TEXT_H 100
#define TITLE_Y 50

// Button properties
#define COLOR_BUTTON_UNCLICK RGB(25,55,109)
#define COLOR_BUTTON_CLICK RGB(70,130,180)
#define BUTTON_RX 50
#define BUTTON_RY 50
#define COLOR_BUTTON_TEXT RGB(255,255,255)

// Beginning button properties
#define BEGINBUTTON_X1 250
#define BEGINBUTTON_Y1 300
#define BEGINBUTTON_X2 550
#define BEGINBUTTON_Y2 400
#define BEGINBUTTON_TEXT_H 80

// Exit button properties
#define EXITBUTTON_X1 280
#define EXITBUTTON_Y1 410
#define EXITBUTTON_X2 520
#define EXITBUTTON_Y2 490
#define EXITBUTTON_TEXT_H 60

void DrawTitle()
{
    settextstyle(TITLE_TEXT_H, 0, _T("Impact"));
    settextcolor(COLOR_TITLE);
    setbkmode(TRANSPARENT);

    int tw = textwidth(_T("Gluttonous Snake"));
    int th = textheight(_T("Gluttonous Snake"));
    int Text_X = (WINDOW_W - tw) / 2;
    int Text_Y = TITLE_Y;
    outtextxy(Text_X, Text_Y, _T("Gluttonous Snake"));
}

void DrawBeginningButton(bool hovered)
{
    setfillcolor(hovered ? COLOR_BUTTON_CLICK : COLOR_BUTTON_UNCLICK);
    fillroundrect(BEGINBUTTON_X1, BEGINBUTTON_Y1, BEGINBUTTON_X2, BEGINBUTTON_Y2,
                  BUTTON_RX, BUTTON_RY);

    settextstyle(BEGINBUTTON_TEXT_H, 0, _T("Consolas"));
    settextcolor(COLOR_BUTTON_TEXT);
    setbkmode(TRANSPARENT);

    int tw = textwidth(_T("START"));
    int th = textheight(_T("START"));
    int Text_X = (BEGINBUTTON_X1 + BEGINBUTTON_X2 - tw) / 2;
    int Text_Y = (BEGINBUTTON_Y1 + BEGINBUTTON_Y2 - th) / 2;
    outtextxy(Text_X, Text_Y, _T("START"));
}

void DrawExitButton(bool hovered)
{
    setfillcolor(hovered ? COLOR_BUTTON_CLICK : COLOR_BUTTON_UNCLICK);
    fillroundrect(EXITBUTTON_X1, EXITBUTTON_Y1, EXITBUTTON_X2, EXITBUTTON_Y2,
        BUTTON_RX, BUTTON_RY);

    settextstyle(EXITBUTTON_TEXT_H, 0, _T("Consolas"));
    settextcolor(COLOR_BUTTON_TEXT);
    setbkmode(TRANSPARENT);

    int tw = textwidth(_T("EXIT"));
    int th = textheight(_T("EXIT"));
    int Text_X = (EXITBUTTON_X1 + EXITBUTTON_X2 - tw) / 2;
    int Text_Y = (EXITBUTTON_Y1 + EXITBUTTON_Y2 - th) / 2;
    outtextxy(Text_X, Text_Y, _T("EXIT"));
}

void Initial()
{
    initgraph(WINDOW_W, WINDOW_H);
    setbkcolor(COLOR_BG);
    cleardevice();

    DrawBeginningButton(false);
    DrawExitButton(false);

    ExMessage msg;
    bool Correct_Click = false;

    while (1)
    {
        DrawTitle();

        if (peekmessage(&msg, EX_MOUSE))
        {
            int Mouse_X = msg.x;
            int Mouse_Y = msg.y;
            bool inside_beginbutton = Mouse_X >= BEGINBUTTON_X1 && Mouse_X <= BEGINBUTTON_X2 &&
                Mouse_Y >= BEGINBUTTON_Y1 && Mouse_Y <= BEGINBUTTON_Y2;

            if (msg.message == WM_LBUTTONDOWN)
            {
                if (inside_beginbutton)
                {
                    break;
                }
            }
            else if (inside_beginbutton != Correct_Click)
            {
                Correct_Click = inside_beginbutton;
            }
            DrawBeginningButton(Correct_Click);

            bool inside_exitbutton = Mouse_X >= EXITBUTTON_X1 && Mouse_X <= EXITBUTTON_X2 &&
                Mouse_Y >= EXITBUTTON_Y1 && Mouse_Y <= EXITBUTTON_Y2;

            if (msg.message == WM_LBUTTONDOWN)
            {
                if (inside_exitbutton)
                {
                    break;
                }
            }
            else if (inside_exitbutton != Correct_Click)
            {
                Correct_Click = inside_exitbutton;
            }
            DrawExitButton(Correct_Click);
        }
    }

    closegraph();
}

int main()
{
    Initial();
    return 0;
}
