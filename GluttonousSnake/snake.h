#pragma once

#include <graphics.h>
#include <iostream>
#include <vector>
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
			direction = 0; // up
		}
		else if(GetAsyncKeyState('A') & 0x8000)
		{
			direction = 3; // left
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			direction = 2; // down
		}
		else if(GetAsyncKeyState('D') & 0x8000)
		{
			direction = 1; // right
		}
	}
	void Move()
	{
		ChangeDirection();
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
	int direction = 0; // 0: up, 1: right, 2: down, 3: left
	int speed = 1;
	int length = 1;
	int head_x;
	int head_y;
	std::vector<std::pair<location, int>> body;
};