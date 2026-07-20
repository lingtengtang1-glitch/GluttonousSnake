#pragma once

#include <graphics.h>
#include <iostream>
#include <vector>
#include "RelevantData.h"
struct location
{
	int x;
	int y;
};
class Snake
{
public:
	Snake(int x, int y,int direct) : head_x(x), head_y(y){
		body.push_back(std::make_pair(location{x, y}, direct));
	}
	void ChangeDirection()
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			if(direction != 2)
				direction = 0; // up
		}
		else if(GetAsyncKeyState('A') & 0x8000)
		{
			if (direction != 1)
				direction = 3; // left
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			if (direction != 0)
				direction = 2; // down
		}
		else if(GetAsyncKeyState('D') & 0x8000)
		{
			if (direction != 3)
				direction = 1; // right
		}
	}
	void Move()
	{
		for(int i = body.size() - 1; i > 0; --i)
		{
			body[i] = body[i - 1];
		}
		switch(direction)
		{
			case 0: 
				head_y -= speed; 
				break; // up
			case 1: 
				head_x += speed; 
				break; // right
			case 2: 
				head_y += speed;
				break; // down
			case 3: 
				head_x -= speed;
				break; // left
		}
		body[0] = std::make_pair(location{ head_x, head_y }, direction);
	}
	int getBodySize() const
	{
		return body.size();
	}
	void AddBodySegment()
	{
		int tmp_x = body.back().first.x;
		int tmp_y = body.back().first.y;
		int direct = body.back().second;
		switch (direct)
		{
		case 0:
			tmp_y += BODYJOINT_LENGTH;
			break;
		case 1:
			tmp_x -= BODYJOINT_LENGTH;
			break;
		case 2:
			tmp_y -= BODYJOINT_LENGTH;
			break;
		case 3:
			tmp_x += BODYJOINT_LENGTH;
			break;
		}
		body.push_back(std::make_pair(location{ tmp_x, tmp_y }, direct));
	}
	int direction = 0; // 0: up, 1: right, 2: down, 3: left
	int speed = BODYJOINT_LENGTH;
	int length = 1;
	int head_x;
	int head_y;
	std::vector<std::pair<location, int>> body;
};