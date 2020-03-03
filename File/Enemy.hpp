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

	virtual void SetHitCheck(Player* player, bool OnOff) const = 0;		//HitCheck�� �����Ѵ�.

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const = 0;
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2S) const = 0;
	
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
static HBITMAP LSBitMap[22];

class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, int C, int D, int R, int Di);				

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

static HBRUSH WSBrush1;
static HBRUSH WSBrush2;

static HPEN WSPen;

static HBITMAP WEBitmap1;
static HBITMAP WEBitmap2;
static HBITMAP WSBitmap[7];


class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, int C, int D, int Di);

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

static HBRUSH BBrush1;
static HPEN BPen1;


class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, int C, int D, int DX, int DY);		

	const int GetDXPos() const;									//DXPos�� ���
	const int GetDYPos() const;									//DYPos�� ���

	virtual void SetDropPos();									//DXPos���� DYPos���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//��ź�� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;			//��ź�� ��ź�� �׸���.
private:
	int DXPos;													//�������� X�� ��ġ
	int DYPos;													//�������� Y�� ��ġ
};

void CreateBEnemy(BombEnemy** Benemy);
void DeleteBEnemy(BombEnemy** Benemy);
void SelectBShot(BombEnemy** Benemy);
int ChangeBInfo(BombEnemy** Benemy, Player* player);

//������ ���ʹ�
class RectEnemy : public BombEnemy {
public:
	RectEnemy(int X, int Y, int C, int D, int DX, int DY, int Co);	

	const int GetCount() const;										//Count�� ���

	void SetCount();												//Count���� ���Ѵ�.

virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;				//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;							//�������� ���� �׸���.
private:
	int Count;														//�������� ���� ����
};



void CreateREnemy(RectEnemy** Renemy);





