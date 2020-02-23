#pragma once
#include <windows.h>

//class Camera;

class Player {

public:
	Player(int X, int Y);							//������
		
	const int GetXPos() const;						//XPos���� �ҷ��´�.
	const int GetYPos() const;						//YPos���� �ҷ��´�.

	void MoveBasic();
	const bool MoveRangeCheck() const;
	void MoveLeft();							
	void MoveRight();
	void MoveTop();
	void MoveBottom();

	void PaintPlayer(HDC hdc) const;				//Player �׸���

private:
	int XPos;
	int YPos;
};

void CreatePlayer(Player** player);
void DeletePlayer(Player** player);

