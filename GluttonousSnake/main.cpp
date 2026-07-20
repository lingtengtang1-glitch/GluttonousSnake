#include "RelevantData.h"
#include "Draw.h"
#include "snake.h"
#include "food.h"
#include <iostream>
#include <fstream>
using namespace std;
int Score = 0;
int Record;
bool BreakRecord = false;

vector<Food> SnakeFood;

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
Snake snake((400 / BODYJOINT_LENGTH) * BODYJOINT_LENGTH, (300 / BODYJOINT_LENGTH)* BODYJOINT_LENGTH, 1);

Snake snake_initial;


void Restart()
{
    if (BreakRecord)
    {
        Record = Score;
        ofstream fout("Record.txt");
        fout << Record;
    }
    snake = snake_initial;
    Score = 0;
    SnakeFood.clear();
    BreakRecord = false;
}

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
                Restart();
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
                Game.currentScreen = GAME;
            }
            else if (Game.Mouse_X >= RESTARTBUTTON_PAUSE_X1 && Game.Mouse_X <= RESTARTBUTTON_PAUSE_X2 &&
                Game.Mouse_Y >= RESTARTBUTTON_PAUSE_Y1 && Game.Mouse_Y <= RESTARTBUTTON_PAUSE_Y2)
            {
                Restart();
                Game.currentScreen = GAME;
            }
            else if (Game.Mouse_X >= EXITBUTTON_PAUSE_X1 && Game.Mouse_X <= EXITBUTTON_PAUSE_X2 &&
                Game.Mouse_Y >= EXITBUTTON_PAUSE_Y1 && Game.Mouse_Y <= EXITBUTTON_PAUSE_Y2)
            {
                Game.currentScreen = INITIALMENU;
            }
            break;
        case GAMEOVER:
            if (Game.Mouse_X >= RESTARTBUTTON_GAMEOVER_X1 && Game.Mouse_X <= RESTARTBUTTON_GAMEOVER_X2 &&
                Game.Mouse_Y >= RESTARTBUTTON_GAMEOVER_Y1 && Game.Mouse_Y <= RESTARTBUTTON_GAMEOVER_Y2)
            {
                Restart();
                Game.currentScreen = GAME;
            }
            else if (Game.Mouse_X >= EXITBUTTON_GAMEOVER_X1 && Game.Mouse_X <= EXITBUTTON_GAMEOVER_X2 &&
                Game.Mouse_Y >= EXITBUTTON_GAMEOVER_Y1 && Game.Mouse_Y <= EXITBUTTON_GAMEOVER_Y2)
            {
                Game.currentScreen = INITIALMENU;
			}
            break;
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

bool JudgeIfGameOver()
{
    if (snake.head_x > MAP_W || snake.head_y > MAP_H || snake.head_x < 0 || snake.head_y < 0) return true;
    for (int i = 1; i < snake.body.size(); i++)
    {
        if (snake.head_x == snake.body[i].first.x && snake.head_y == snake.body[i].first.y)
        {
            return true;
        }
    }
    return false;
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

bool Check_FoodEaten()
{
    int x = snake.head_x;
    int y = snake.head_y;
    for (int i = SnakeFood.size() - 1; i >= 0; i--)
    {
        if (x == SnakeFood[i].x && y == SnakeFood[i].y)
        {
            SnakeFood.erase(SnakeFood.begin() + i);
            return true;
        }
    }
    return false;
}

void DrawMap()
{
    setfillcolor(COLOR_MAP_EDGE);
    setlinecolor(COLOR_BACKGROUND);
    rectangle(0, 0, MAP_W, MAP_H);
    setlinecolor(COLOR_MAP_EDGE);
}

static void DrawScore_GamePage()
{
    settextstyle(SCORE_GAME_H, 0, _T("impact"));
    int tx = (WINDOW_W + MAP_W - textwidth(_T("Score:"))) / 2;
    int ty = 30;
    Draw_Text(tx, ty, _T("Score:"), COLOR_SCORE_GAME, _T("impact"), SCORE_GAME_H);

    int tx_S = (WINDOW_W + MAP_W - textwidth(std::to_wstring(Score).c_str())) / 2;
    int ty_S = ty + 40;
    Draw_Text(tx_S,ty_S, std::to_wstring(Score).c_str(), COLOR_SCORE_GAME, _T("Consolas"), SCORE_GAME_H);

    settextstyle(SCORE_GAME_H, 0, _T("impact"));
    int tx_RT = (WINDOW_W + MAP_W - textwidth(_T("Record:"))) / 2;
    int ty_RT = ty_S + 60;
    Draw_Text(tx_RT, ty_RT, _T("Record:"), COLOR_RECORD_GAME, _T("impact"), RECORD_GAME_H);

    int tx_RN = (WINDOW_W + MAP_W - textwidth(std::to_wstring(Record).c_str())) / 2;
    int ty_RN = ty_RT + 40;
    Draw_Text(tx_RN, ty_RN, std::to_wstring(Record).c_str(), COLOR_RECORD_GAME, _T("Consolas"), RECORD_GAME_H);
}

void DrawGame()
{
    cleardevice();
	static DWORD lastMoveTime = GetTickCount();
    DWORD currentTime = GetTickCount();

    static Food tmp_food;
    if (tmp_food.TrySpawn(snake.body))
        SnakeFood.push_back(tmp_food);
    


    if (currentTime - lastMoveTime >= MOVE_INTERVAL)
    {
        snake.Move();
        if (Check_FoodEaten())
        {
            snake.AddBodySegment();
            Score++;
            if (Score > Record && BreakRecord == false)
            {
                BreakRecord = true;
            }
        }
		lastMoveTime = currentTime;
        if (JudgeIfGameOver())
        {
            Game.currentScreen = GAMEOVER;
            return;
        }
    }
    else
    {
		snake.ChangeDirection();
    }
    DrawScore_GamePage();
    snake.Draw();

    for (int i = 0; i < SnakeFood.size(); ++i)
    {
        SnakeFood[i].Draw();
    }
    DrawMap();

    FlushBatchDraw();
	Sleep(0); // Control the speed of the game loop

}

static void DrawScore_GameOverPage()
{
    settextstyle(SCORE_TEXT_H, 0, _T("Consolas"));

    std::wstring scoreStr = _T("Score: ") + std::to_wstring(Score);

    int tx = (WINDOW_W - textwidth(scoreStr.c_str())) / 2;
    int ty = 200;
    Draw_Text(tx, ty, scoreStr.c_str(), COLOR_SCORE_TEXT, _T("Consolas"), SCORE_TEXT_H);

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

    if (BreakRecord)
    {
        wstring congrats = L"Congratulations! You break the record!";

        settextstyle(CONGRATULATION_H, 0, _T("impact"));
        int tw = textwidth(congrats.c_str());

        int tx = (WINDOW_W - tw) / 2;
        int ty = 140;

        Draw_Text(tx, ty, congrats.c_str(), RED, L"impact", CONGRATULATION_H);
    }

    /*if (BreakRecord)
    {
        settextstyle(CONGRATULATION_H, 0, _T("impact"));
        BreakRecord = false;
        int tx = (WINDOW_W - textwidth(L"Congratulation! You break the record!")) / 2;
        int ty = TITLE_Y + 50;
        Draw_Text(tx, ty, L"Congratulation! You break the record!", RED, L"impact", TITLE_TEXT_H);
    }*/
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
    ifstream fin("Record.txt");
    fin >> Record;
    fin.close();

    for (int i = 0; i < INITIAL_LENGTH - 1; i++)
        snake.AddBodySegment();

    snake_initial = snake;
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
            if (BreakRecord)
            {
                ofstream fout("Record.txt");
                Record = Score;
                fout << Score;
                fout.close();
            }
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
