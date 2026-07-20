#pragma once

#include <graphics.h>
#include <random>
#include <vector>
#include "RelevantData.h"
#include "snake.h"

struct Food
{
    int x = -1;
    int y = -1;
    bool active = true;
    DWORD lastSpawnTime = 0;

    bool TrySpawn(const std::vector<std::pair<location, int>>& snakeBody)
    {

        DWORD now = GetTickCount();
        if (now - lastSpawnTime < FOOD_SPAWN_INTERVAL) return false;

        static std::random_device rd;
        static std::mt19937 gen(rd());
        int cols = MAP_W / BODYJOINT_LENGTH;
        int rows = MAP_H / BODYJOINT_LENGTH;
        std::uniform_int_distribution<> distX(0, cols - 1);
        std::uniform_int_distribution<> distY(0, rows - 1);

        for (int attempt = 0; attempt < 200; ++attempt)
        {
            x = distX(gen) * BODYJOINT_LENGTH;
            y = distY(gen) * BODYJOINT_LENGTH;

            bool onSnake = false;
            for (const auto& seg : snakeBody)
            {
                if (seg.first.x == x && seg.first.y == y)
                {
                    onSnake = true;
                    break;
                }
            }
            if (!onSnake)
            {
                lastSpawnTime = now;
                return true;
            }
        }
        lastSpawnTime = now;
        return true;
    }


    void Draw()
    {
        setfillcolor(FOOD_COLOR);
        fillrectangle(x, y, x + FOOD_SIZE, y + FOOD_SIZE);

    }


};
