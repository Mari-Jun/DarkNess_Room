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
		
	//�÷��̾� ����
	const int GetXPos() const;								//XPos���� �ҷ��´�.
	const int GetYPos() const;								//YPos���� �ҷ��´�.

	void MoveBasic();										//Move�� �������� ���
	const bool MoveRangeCheck() const;						//�����ϼ� �ִ� ���� üũ
	void MoveLeft();										//�������� �̵�
	void MoveRight();										//���������� �̵�		
	void MoveTop();											//�������� �̵�	
	void MoveBottom();										//�Ʒ������� �̵�

	void SetPoint(POINT* Pos, double Num) const;			//Pos[5] ����
	void PaintPlayer(HDC hdc) const;						//Player �׸���

	//�������̽� ����
	const int GetHealth() const;							//Health���� ��ȯ�Ѵ�.
	const int GetSkillQ() const;							//SkillQ���� ��ȯ�Ѵ�.
	const int GetSkillW() const;							//SkillW���� ��ȯ�Ѵ�.
	const int GetSkillE() const;							//SkillE���� ��ȯ�Ѵ�.

	void PaintPlayerIF(HDC hdc) const;						//Player �������̽� �׸���

private:
	int XPos;
	int YPos;
	int Health;
	int SkillQ;
	int SkillW;
	int SkillE;
};

void CreatePlayer(Player** player);					//Player�� ����� ���� ��ü�� ����
void DeletePlayer(Player** player);					//Player�� ���� ������� ��ü�� ����

