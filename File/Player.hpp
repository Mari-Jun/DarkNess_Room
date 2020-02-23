#pragma once
#include <windows.h>

//class Camera;

class Player {

public:
	Player(int X, int Y);							//생성자
		
	const int GetXPos() const;						//XPos값을 불러온다.
	const int GetYPos() const;						//YPos값을 불러온다.

	void MoveBasic();
	const bool MoveRangeCheck() const;
	void MoveLeft();							
	void MoveRight();
	void MoveTop();
	void MoveBottom();

	void PaintPlayer(HDC hdc) const;				//Player 그리기

private:
	int XPos;
	int YPos;
};

void CreatePlayer(Player** player);
void DeletePlayer(Player** player);

