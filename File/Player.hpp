#pragma once
#include <windows.h>

static const double PI = 3.1415926535897;

static HBRUSH PlayerIFBrush1;
static HBRUSH OldPBrush;

static HPEN PlayerPen1;
static HPEN OldPPen;

static HFONT PlayerIFFont1;
static HFONT PlayerIFFont2;

class Player {

public:
	explicit Player(int X, int Y, int H, int Q, int W, int E);	
		
	//플레이어 관련
	const int GetXPos() const;								//XPos값을 불러온다.
	const int GetYPos() const;								//YPos값을 불러온다.

	void MoveBasic();										//Move의 전반적인 담당
	const bool MoveRangeCheck() const;						//움직일수 있는 범위 체크
	void MoveLeft();										//왼쪽으로 이동
	void MoveRight();										//오른쪽으로 이동		
	void MoveTop();											//위쪽으로 이동	
	void MoveBottom();										//아래쪽으로 이동

	void SetPoint(POINT* Pos, double Num) const;			//Pos[5] 세팅
	void PaintPlayer(HDC hdc) const;						//Player 그리기

	//인터페이스 관련
	const int GetHealth() const;							//Health값을 반환한다.
	const int GetSkillQ() const;							//SkillQ값을 반환한다.
	const int GetSkillW() const;							//SkillW값을 반환한다.
	const int GetSkillE() const;							//SkillE값을 반환한다.

	void PaintPlayerIF(HDC hdc) const;						//Player 인터페이스 그리기

private:
	int XPos;
	int YPos;
	int Health;
	int SkillQ;
	int SkillW;
	int SkillE;
};

void CreatePlayer(Player** player);					//Player를 만들기 위한 객체들 생성
void DeletePlayer(Player** player);					//Player를 위해 만들어진 객체들 삭제

