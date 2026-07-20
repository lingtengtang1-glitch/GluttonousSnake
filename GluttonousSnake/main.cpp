#include "RelevantData.h"
#include "Draw.h"
#include "snake.h"
#include <iostream>
using namespace std;

int Count = 0;

enum Screen
{
    INITIALMENU,
	GAME,
	GAMEOVER,
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
Snake snake(400, 300, 1);

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
        case PAUSEPAGE:
            if (Game.Mouse_X >= CONTINUEBUTTON_X1 && Game.Mouse_X <= CONTINUEBUTTON_X2 &&
                Game.Mouse_Y >= CONTINUEBUTTON_Y1 && Game.Mouse_Y <= CONTINUEBUTTON_Y2)
            {
                Game.currentScreen = GAMEOVER;
            }
            else if (Game.Mouse_X >= RESTARTBUTTON_PAUSE_X1 && Game.Mouse_X <= RESTARTBUTTON_PAUSE_X2 &&
                Game.Mouse_Y >= RESTARTBUTTON_PAUSE_Y1 && Game.Mouse_Y <= RESTARTBUTTON_PAUSE_Y2)
            {
                Game.currentScreen = GAME;
            }
            else if (Game.Mouse_X >= EXITBUTTON_PAUSE_X1 && Game.Mouse_X <= EXITBUTTON_PAUSE_X2 &&
                Game.Mouse_Y >= EXITBUTTON_PAUSE_Y1 && Game.Mouse_Y <= EXITBUTTON_PAUSE_Y2)
            {
                Game.currentScreen = INITIALMENU;
            }
        case GAMEOVER:
            if (Game.Mouse_X >= RESTARTBUTTON_GAMEOVER_X1 && Game.Mouse_X <= RESTARTBUTTON_GAMEOVER_X2 &&
                Game.Mouse_Y >= RESTARTBUTTON_GAMEOVER_Y1 && Game.Mouse_Y <= RESTARTBUTTON_GAMEOVER_Y2)
            {
                Game.currentScreen = GAME;
            }
            else if (Game.Mouse_X >= EXITBUTTON_GAMEOVER_X1 && Game.Mouse_X <= EXITBUTTON_GAMEOVER_X2 &&
                Game.Mouse_Y >= EXITBUTTON_GAMEOVER_Y1 && Game.Mouse_Y <= EXITBUTTON_GAMEOVER_Y2)
            {
                Game.currentScreen = INITIALMENU;
			}
    }
}

static void DrawTitle(LPCTSTR str)
{
    settextstyle(TITLE_TEXT_H, 0, _T("impact"));
    settextcolor(COLOR_TITLE);
    setbkmode(TRANSPARENT);

    int tw = textwidth(str);
    int th = textheight(str);
    int Text_X = (WINDOW_W - tw) / 2;
    int Text_Y = TITLE_Y;
    outtextxy(Text_X, Text_Y, str);
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

static void DrawContinueButton(bool hovered)
{
    if (hovered)
        DrawButton(CONTINUEBUTTON_X1, CONTINUEBUTTON_Y1, CONTINUEBUTTON_X2, CONTINUEBUTTON_Y2,
            BUTTON_RX, BUTTON_RY, _T("CONTINUE"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), CONTINUEBUTTON_TEXT_H);
    else
        DrawButton(CONTINUEBUTTON_X1, CONTINUEBUTTON_Y1, CONTINUEBUTTON_X2, CONTINUEBUTTON_Y2,
            BUTTON_RX, BUTTON_RY, _T("CONTINUE"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), CONTINUEBUTTON_TEXT_H);
}

static void DrawRestartButto_PausePage(bool hovered)
{
    if (hovered)
        DrawButton(RESTARTBUTTON_PAUSE_X1, RESTARTBUTTON_PAUSE_Y1, RESTARTBUTTON_PAUSE_X2, RESTARTBUTTON_PAUSE_Y2,
            BUTTON_RX, BUTTON_RY, _T("RESTART"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), RESTARTBUTTON_PAUSE_TEXT_H);
    else
        DrawButton(RESTARTBUTTON_PAUSE_X1, RESTARTBUTTON_PAUSE_Y1, RESTARTBUTTON_PAUSE_X2, RESTARTBUTTON_PAUSE_Y2,
            BUTTON_RX, BUTTON_RY, _T("RESTART"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), RESTARTBUTTON_PAUSE_TEXT_H);
}

static void DrawExitButton_PausePage(bool hovered)
{
    if (hovered)
        DrawButton(EXITBUTTON_PAUSE_X1, EXITBUTTON_PAUSE_Y1, EXITBUTTON_PAUSE_X2, EXITBUTTON_PAUSE_Y2,
            BUTTON_RX, BUTTON_RY, _T("EXIT"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), EXITBUTTON_PAUSE_TEXT_H);
    else
        DrawButton(EXITBUTTON_PAUSE_X1, EXITBUTTON_PAUSE_Y1, EXITBUTTON_PAUSE_X2, EXITBUTTON_PAUSE_Y2,
            BUTTON_RX, BUTTON_RY, _T("EXIT"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), EXITBUTTON_PAUSE_TEXT_H);
}

static void DrawRestartButton_GameOver(bool hovered)
{
    if (hovered)
        DrawButton(RESTARTBUTTON_GAMEOVER_X1, RESTARTBUTTON_GAMEOVER_Y1, RESTARTBUTTON_GAMEOVER_X2, RESTARTBUTTON_GAMEOVER_Y2,
            BUTTON_RX, BUTTON_RY, _T("RESTART"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), RESTARTBUTTON_GAMEOVER_TEXT_H);
    else
        DrawButton(RESTARTBUTTON_GAMEOVER_X1, RESTARTBUTTON_GAMEOVER_Y1, RESTARTBUTTON_GAMEOVER_X2, RESTARTBUTTON_GAMEOVER_Y2,
            BUTTON_RX, BUTTON_RY, _T("RESTART"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), RESTARTBUTTON_GAMEOVER_TEXT_H);
}

static void DrawExitButton_GameOver(bool hovered)
{
    if (hovered)
        DrawButton(EXITBUTTON_GAMEOVER_X1, EXITBUTTON_GAMEOVER_Y1, EXITBUTTON_GAMEOVER_X2, EXITBUTTON_GAMEOVER_Y2,
            BUTTON_RX, BUTTON_RY, _T("EXIT"), COLOR_BUTTON_CLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), EXITBUTTON_GAMEOVER_TEXT_H);
    else
        DrawButton(EXITBUTTON_GAMEOVER_X1, EXITBUTTON_GAMEOVER_Y1, EXITBUTTON_GAMEOVER_X2, EXITBUTTON_GAMEOVER_Y2,
            BUTTON_RX, BUTTON_RY, _T("EXIT"), COLOR_BUTTON_UNCLICK,
            COLOR_BUTTON_TEXT, _T("Consolas"), EXITBUTTON_GAMEOVER_TEXT_H);
}

void DrawInitialMenu()
{
    DrawTitle(_T("Gluttonous Snake"));
    bool inside_beginbutton = Game.Mouse_X >= BEGINBUTTON_X1 && Game.Mouse_X <= BEGINBUTTON_X2 &&
        Game.Mouse_Y >= BEGINBUTTON_Y1 && Game.Mouse_Y <= BEGINBUTTON_Y2;
    DrawBeginningButton(inside_beginbutton);

    bool inside_exitbutton = Game.Mouse_X >= EXITBUTTON_X1 && Game.Mouse_X <= EXITBUTTON_X2 &&
        Game.Mouse_Y >= EXITBUTTON_Y1 && Game.Mouse_Y <= EXITBUTTON_Y2;
    DrawExitButton(inside_exitbutton);
}

void DrawGame()
{
    cleardevice();
    if (Count == 0)
    {
		snake.AddBodySegment();
    }
	static DWORD lastMoveTime = GetTickCount();
    DWORD currentTime = GetTickCount();

    const int MOVE_INTERVAL = 150;

    if (currentTime - lastMoveTime >= MOVE_INTERVAL)
    {
        snake.Move();
		lastMoveTime = currentTime;
    }
    else
    {
		snake.ChangeDirection();
    }

    for(int i = 0; i < snake.body.size(); ++i)
    {
        cout << snake.body.size() << endl;
        int x = snake.body[i].first.x;
        int y = snake.body[i].first.y;
        int direction = snake.body[i].second;
        setfillcolor(RGB(0, 255, 0));
        fillrectangle(x, y, x + BODYJOINT_LENGTH, y + BODYJOINT_LENGTH);
	}
    FlushBatchDraw();
    Count = (Count + 1) % 1000;
	Sleep(0); // Control the speed of the game loop

}

static void DrawScore_GameOverPage()
{
    settextstyle(SCORE_TEXT_H, 0, _T("Consolas"));
	int tx = (WINDOW_W - textwidth(_T("Score: 0"))) / 2;
    int ty = 200;
	DrawText(tx, ty, _T("Score: 0"), COLOR_SCORE_TEXT, _T("Consolas"), SCORE_TEXT_H);

}


void DrawGameOver()
{
	DrawTitle(_T("Game Over"));
	bool inside_restartbutton = Game.Mouse_X >= RESTARTBUTTON_GAMEOVER_X1 && Game.Mouse_X <= RESTARTBUTTON_GAMEOVER_X2 &&
		Game.Mouse_Y >= RESTARTBUTTON_GAMEOVER_Y1 && Game.Mouse_Y <= RESTARTBUTTON_GAMEOVER_Y2;
	DrawRestartButton_GameOver(inside_restartbutton);
	bool inside_exitbutton = Game.Mouse_X >= EXITBUTTON_GAMEOVER_X1 && Game.Mouse_X <= EXITBUTTON_GAMEOVER_X2 &&
		Game.Mouse_Y >= EXITBUTTON_GAMEOVER_Y1 && Game.Mouse_Y <= EXITBUTTON_GAMEOVER_Y2;
	DrawExitButton_GameOver(inside_exitbutton);
	DrawScore_GameOverPage();

}

void DrawPausePage()
{
	DrawTitle(_T("Game Paused"));
    bool inside_continuebutton = Game.Mouse_X >= CONTINUEBUTTON_X1 && Game.Mouse_X <= CONTINUEBUTTON_X2 &&
		Game.Mouse_Y >= CONTINUEBUTTON_Y1 && Game.Mouse_Y <= CONTINUEBUTTON_Y2;
	DrawContinueButton(inside_continuebutton);

	bool inside_restartbutton = Game.Mouse_X >= RESTARTBUTTON_PAUSE_X1 && Game.Mouse_X <= RESTARTBUTTON_PAUSE_X2 &&
		Game.Mouse_Y >= RESTARTBUTTON_PAUSE_Y1 && Game.Mouse_Y <= RESTARTBUTTON_PAUSE_Y2;
	DrawRestartButto_PausePage(inside_restartbutton);
    
	bool inside_exitbutton = Game.Mouse_X >= EXITBUTTON_PAUSE_X1 && Game.Mouse_X <= EXITBUTTON_PAUSE_X2 &&
		Game.Mouse_Y >= EXITBUTTON_PAUSE_Y1 && Game.Mouse_Y <= EXITBUTTON_PAUSE_Y2;
	DrawExitButton_PausePage(inside_exitbutton);

}

int main()
{
    initgraph(WINDOW_W, WINDOW_H);
    setbkcolor(COLOR_BG);
    cleardevice();
	ExMessage Msg;

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
            DrawGame();
            break;
        case GAMEOVER:
            DrawGameOver();
            break;
        case PAUSEPAGE:
            DrawPausePage();
            break;
        }

        FlushBatchDraw();

        if (peekmessage(&Msg, EX_MOUSE))
        {
            Game.Mouse_X = Msg.x;
			Game.Mouse_Y = Msg.y;
            if (Msg.message == WM_LBUTTONDOWN)
            {
                MouseClickEvent(Msg);
			}
        }
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            if(Game.currentScreen == GAME)
            {
                Game.currentScreen = PAUSEPAGE;
                Sleep(200);
            }
            else if(Game.currentScreen == PAUSEPAGE)
            {
                Game.currentScreen = GAME;
                Sleep(200);
			}
		}
    }

    EndBatchDraw();
	closegraph();


    return 0;
}
