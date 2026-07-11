#include "RelevantData.h"
#include "Draw.h"
#include <iostream>
using namespace std;

static void DrawTitle()
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

static void DrawBeginningButton(bool hovered)
{
    if (hovered)
        DrawButton(BEGINBUTTON_X1, BEGINBUTTON_Y1, BEGINBUTTON_X2, BEGINBUTTON_Y2,
            BUTTON_RX, BUTTON_RY, _T("START"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), BEGINBUTTON_TEXT_H);
    else
        DrawButton(BEGINBUTTON_X1, BEGINBUTTON_Y1, BEGINBUTTON_X2, BEGINBUTTON_Y2,
            BUTTON_RX, BUTTON_RY, _T("START"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), BEGINBUTTON_TEXT_H);
}

static void DrawExitButton(bool hovered)
{
    if (hovered)
        DrawButton(EXITBUTTON_X1, EXITBUTTON_Y1, EXITBUTTON_X2, EXITBUTTON_Y2,
            BUTTON_RX, BUTTON_RY, _T("EXIT"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), EXITBUTTON_TEXT_H);
    else
        DrawButton(EXITBUTTON_X1, EXITBUTTON_Y1, EXITBUTTON_X2, EXITBUTTON_Y2,
            BUTTON_RX, BUTTON_RY, _T("EXIT"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), EXITBUTTON_TEXT_H);
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

            DrawBeginningButton(inside_beginbutton);



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

            DrawExitButton(inside_exitbutton);
            
        }
    }

    closegraph();
}

int main()
{
    Initial();
    return 0;
}
