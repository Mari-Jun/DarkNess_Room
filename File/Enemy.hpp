#pragma once
#include "windows.h"

static HBRUSH OldEBrush;
static HPEN OldEPen;

class Player;

//�⺻ ���ʹ�
class Enemy {
public:
	explicit Enemy(int X, int Y, int C, int D);							

	const int GetXPos() const;										//XPos�� ���
	const int GetYPos() const;										//YPos�� ���
	const int GetCharging() const;									//Charging�� ���
	const int GetDelay() const;										//Delay�� ���
	
	void SetCharging();												//Charging���� �����Ѵ�. (��ǻ� ����)
	bool ChangeCharging();											//Charging���� 1�� ���ҽ�Ų��.
	void SetDelay(int D);											//Delay���� �����Ѵ�.
	bool ChangeDelay();												//Delay���� 1�� ���ҽ�Ų��.

	virtual void SetHitCheck(Player* player, bool OnOff) = 0;		//HitCheck�� �����Ѵ�.

	virtual void PaintEnmey(HDC hdc, HDC BIthdc) const = 0;
	virtual void PaintShot(HDC hdc) const = 0;
	
private:
	int XPos;														//���� X�� ��ġ
	int YPos;														//���� Y�� ��ġ
	int Charging;													//���� �߻� �ð�
	int Delay;														//���� �߻� ���� �ð�
};



//������ ���ʹ�
static HBRUSH LBrush1;
static HBRUSH LBrush2;
static HBRUSH LBrush3;

static HPEN LPen1;
static HPEN LPen2;
static HPEN LPen3;

static HBITMAP LBitMap[4];

class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, int C, int D, int R, int Di);				

	const int GetRange() const;									//Range�� ���
	const int GetDirection() const;								//Direction�� ��� 1: �� 2: �� -2: �� -1: �Ʒ�

	void SetRange();											//Range���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff);
		
	virtual void PaintEnmey(HDC hdc, HDC BIthdc) const;			//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Range;													//�ǰ� ����
	int Direction;												//�� ����
};

void CreateLEnemy(LineEnemy** Lenemy);
void DeleteLEnemy(LineEnemy** Lenemy);
void SelectLShot(LineEnemy** Lenemy);
int ChangeLInfo(LineEnemy** Lenmey, Player* player);


static HBRUSH WEBrush;
static HBRUSH WSBrush1;
static HBRUSH WSBrush2;

static HPEN WEPen;
static HPEN WSPen;

//������ ���ʹ�
class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, int C, int D, int Di);

	const int GetDirection() const;								//Direction�� ���

	void SetDirection();										//Direction���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff);

	virtual void PaintEnmey(HDC hdc, HDC BIthdc) const;			//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Direction;												//���� ����
};

void CreateWEnemy(WideEnemy** Wenemy);
void DeleteWEnemy(WideEnemy** Wenemy);
int ChangeWInfo(LineEnemy** Lenmey, Player* player);

//��ź ���ʹ�
class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, int C, int D, int DX, int DY);		

	const int GetDXPos() const;									//DXPos�� ���
	const int GetDYPos() const;									//DYPos�� ���

	virtual void SetDropPos();									//DXPos���� DYPos���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff);

	virtual void PaintEnmey(HDC hdc, HDC BIthdc) const;			//��ź�� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;						//��ź�� ��ź�� �׸���.
private:
	int DXPos;													//�������� X�� ��ġ
	int DYPos;													//�������� Y�� ��ġ
};

//������ ���ʹ�
class RectEnemy : public BombEnemy {
public:
	RectEnemy(int X, int Y, int C, int D, int DX, int DY, int Co);	

	const int GetCount() const;										//Count�� ���

	void SetCount();												//Count���� ���Ѵ�.

virtual void SetHitCheck(Player* player, bool OnOff);

	virtual void PaintEnmey(HDC hdc, HDC BIthdc) const;				//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;							//�������� ���� �׸���.
private:
	int Count;														//�������� ���� ����
};


void CreateBEnemy(BombEnemy** Benemy);
void CreateREnemy(RectEnemy** Renemy);





