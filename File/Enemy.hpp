#pragma once
#include "windows.h"

static HBRUSH OldEBrush;
static HPEN OldEPen;

class Player;

//�⺻ ���ʹ�
class Enemy {
public:
	explicit Enemy(int C, int D);							

	const int GetCharging() const;									//Charging�� ���
	const int GetDelay() const;										//Delay�� ���
	
	void SetCharging();												//Charging���� �����Ѵ�. (��ǻ� ����)
	bool ChangeCharging();											//Charging���� 1�� ���ҽ�Ų��.
	void SetDelay(int D);											//Delay���� �����Ѵ�.
	bool ChangeDelay();												//Delay���� 1�� ���ҽ�Ų��.

	virtual void SetHitCheck(Player* player, bool OnOff) const = 0;		//HitCheck�� �����Ѵ�.

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const = 0;
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2S) const = 0;
	
private:
	
	int Charging;													//���� �߻� �ð�
	int Delay;														//���� �߻� ���� �ð�
};

//���� ���ʹ�
class FixEnemy : public Enemy {
public:
	explicit FixEnemy(int C, int D, int X, int Y);

	const int GetXPos() const;										//XPos�� ���
	const int GetYPos() const;										//YPos�� ���

private:
	int XPos;														//���� X�� ��ġ
	int YPos;														//���� Y�� ��ġ
};

//�̵� ���ʹ�
class MoveEnemy : public Enemy {
public:
	explicit MoveEnemy(int C, int D, int X, int Y);

	const int GetXPos() const;										//XPos�� ���
	const int GetYPos() const;										//YPos�� ���

	void ChangeXPos(int X);											//XPos�� ����
	void ChangeYPos(int Y);											//YPos�� ����

private:
	int XPos;														//���� X�� ��ġ
	int YPos;														//���� Y�� ��ġ
};


//������ ���ʹ�

static HBITMAP LBitMap[4];
static HBITMAP LSBitMap[22];

static HBRUSH LBrush;
static HPEN LPen;

class LineEnemy : public FixEnemy {
public:
	explicit LineEnemy(int C, int D, int X, int Y, int R, int Di);

	const int GetRange() const;									//Range�� ���
	const int GetDirection() const;								//Direction�� ��� 1: �� 2: �� -2: �� -1: �Ʒ�

	void SetRange();											//Range���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff) const;
		
	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//�������� ���� �׸���.
private:
	int Range;													//�ǰ� ����
	int Direction;												//�� ����
};

void CreateLEnemy(LineEnemy** Lenemy);
void DeleteLEnemy(LineEnemy** Lenemy);
void SelectLShot(LineEnemy** Lenemy);
int ChangeLInfo(LineEnemy** Lenmey, Player* player);


//������ ���ʹ�

static HBITMAP WEBitmap1;
static HBITMAP WEBitmap2;
static HBITMAP WSBitmap[7];

static HBRUSH WSBrush;
static HPEN WSPen;


class WideEnemy : public FixEnemy {
public:
	WideEnemy(int C, int D, int X, int Y, int Di);

	const int GetDirection() const;								//Direction�� ���

	void SetDirection();										//Direction���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//�������� ���� �׸���.
private:
	int Direction;												//���� ����
};

void CreateWEnemy(WideEnemy** Wenemy);
void DeleteWEnemy(WideEnemy** Wenemy);
void ChangeWInfo(WideEnemy* WenemSy, Player* player);

//��ź ���ʹ�

static HBITMAP BBitmap;
static HBITMAP EXBitmap[11];

static HBRUSH BBrush;
static HPEN BPen;


class BombEnemy : public MoveEnemy {
public:
	BombEnemy(int C, int D, int X, int Y);

	void SetDropPos();									//DXPos���� DYPos���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//��ź�� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;			//��ź�� ��ź�� �׸���.
};

void CreateBEnemy(BombEnemy** Benemy);
void DeleteBEnemy(BombEnemy** Benemy);
void SelectBShot(BombEnemy** Benemy);
int ChangeBInfo(BombEnemy** Benemy, Player* player);

//���� ����� ���ʹ�

static HBITMAP ABitmap[2];
static HBITMAP ASBitmap[11];

static HBRUSH ABrush;
static HPEN APen;

class AirEnemy : public MoveEnemy {
public:
	AirEnemy(int C, int D, int X, int Y, int DX, int DY);

	void SetDropPos(Player* player);									//DXPos���� DYPos���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;					//���� ����⸦ �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;		//���� ��������� �׸���.

private:
	int DXPos;
	int DYPos;
};



void CreateAEnemy(AirEnemy** Aenemy);
void DeleteAEnemy(AirEnemy** Aenemy);





