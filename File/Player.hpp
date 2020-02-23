#pragma once
#include <windows.h>

class Player {

public:
	Player(int X, int Y);							//Player 생성자
		
	const int GetXPos() const;						//XPos값을 불러온다.
	const int GetYPos() const;						//YPos값을 불러온다.

	void MoveBasic();								//Move의 전반적인 담당
	const bool MoveRangeCheck() const;				//움직일수 있는 범위 체크
	void MoveLeft();								//왼쪽으로 이동
	void MoveRight();								//오른쪽으로 이동		
	void MoveTop();									//위쪽으로 이동	
	void MoveBottom();								//아래쪽으로 이동

	void PaintPlayer(HDC hdc) const;				//Player 그리기

private:
	int XPos;
	int YPos;
};

void CreatePlayer(Player** player);					//Player를 만들기 위한 객체들 생성
void DeletePlayer(Player** player);					//Player를 위해 만들어진 객체들 삭제

