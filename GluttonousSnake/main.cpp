#include "RelevantData.h"
#include "Draw.h"
#include <iostream>
using namespace std;

enum Screen
{
    INITIALMENU,
	GAME,
	GAMEOVER,
    GAMEWIN,
    PAUSEPAGE
};

struct AppState
{
    bool isRunning = 1;
    bool isGameStarted = 0;

    int Mouse_X;
    int Mouse_Y;
    bool Mouse_Clicked = false;

    Screen currentScreen = INITIALMENU;
}Game;

void MouseClickEvent(ExMessage msg)
{
    Game.Mouse_X = msg.x;
    Game.Mouse_Y = msg.y;
    Game.Mouse_Clicked = true;

    switch (Game.currentScreen)
    {
		//handel the mouse click event for the initial menu screen
        case INITIALMENU:
            if (Game.Mouse_X >= BEGINBUTTON_X1 && Game.Mouse_X <= BEGINBUTTON_X2 &&
                Game.Mouse_Y >= BEGINBUTTON_Y1 && Game.Mouse_Y <= BEGINBUTTON_Y2)
            {
                Game.currentScreen = GAME;
            }
            else if (Game.Mouse_X >= EXITBUTTON_X1 && Game.Mouse_X <= EXITBUTTON_X2 &&
                Game.Mouse_Y >= EXITBUTTON_Y1 && Game.Mouse_Y <= EXITBUTTON_Y2)
            {
                Game.isRunning = false;
            }
		    break;
            
    }
}

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

void DrawInitialMenu()
{
    DrawTitle();
    bool inside_beginbutton = Game.Mouse_X >= BEGINBUTTON_X1 && Game.Mouse_X <= BEGINBUTTON_X2 &&
        Game.Mouse_Y >= BEGINBUTTON_Y1 && Game.Mouse_Y <= BEGINBUTTON_Y2;
    DrawBeginningButton(inside_beginbutton);

    bool inside_exitbutton = Game.Mouse_X >= EXITBUTTON_X1 && Game.Mouse_X <= EXITBUTTON_X2 &&
        Game.Mouse_Y >= EXITBUTTON_Y1 && Game.Mouse_Y <= EXITBUTTON_Y2;
    DrawExitButton(inside_exitbutton);
}


int main()
{
    initgraph(WINDOW_W, WINDOW_H);
    setbkcolor(COLOR_BG);
    cleardevice();
	ExMessage MouseMsg;

    BeginBatchDraw();

    while (Game.isRunning)
    {
        cleardevice();

        switch (Game.currentScreen)
        {
        case INITIALMENU:
            DrawInitialMenu();
            break;
        case GAME:
            // DrawGame();
            break;
        case GAMEOVER:
            // DrawGameOver();
            break;
        case GAMEWIN:
            // DrawGameWin();
            break;
        case PAUSEPAGE:
            // DrawPausePage();
            break;
        }

        FlushBatchDraw();

        if (peekmessage(&MouseMsg, EX_MOUSE))
        {
            Game.Mouse_X = MouseMsg.x;
			Game.Mouse_Y = MouseMsg.y;
            if (MouseMsg.message == WM_LBUTTONDOWN)
            {
                MouseClickEvent(MouseMsg);
			}
        }
    }

    EndBatchDraw();
	closegraph();


    return 0;
}
