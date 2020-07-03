#pragma once
#include "windows.h"

static HBRUSH OldEBrush;
static HPEN OldEPen;

class Player;
class LevelSet;

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
	void Reset();

	virtual void SetHitCheck(Player* player, const bool OnOff) const = 0;		//HitCheck�� �����Ѵ�.

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

	virtual void SetHitCheck(Player* player, const bool OnOff) const;
		
	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//�������� ���� �׸���.
private:
	int Range;													//�ǰ� ����
	int Direction;												//�� ����
};

void CreateLEnemy(LineEnemy** Lenemy, HINSTANCE hInst);
void DeleteLEnemy(LineEnemy** Lenemy);
void SelectLShot(LineEnemy** Lenemy, const int WaitTime);
int ChangeLInfo(LineEnemy** Lenmey, Player* player);
void ResetLEnemy(LineEnemy** Lenemy);


//������ ���ʹ�

static HBITMAP WEBitmap1;
static HBITMAP WEBitmap2;
static HBITMAP WSBitmap[7];

static HBRUSH WSBrush;
static HPEN WSPen;


class WideEnemy : public FixEnemy {
public:
	explicit WideEnemy(int C, int D, int X, int Y, int Di);

	const int GetDirection() const;								//Direction�� ���

	void SetDirection();										//Direction���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//�������� ���� �׸���.
private:
	int Direction;												//���� ����
};

void CreateWEnemy(WideEnemy** Wenemy, HINSTANCE hInst);
void DeleteWEnemy(WideEnemy** Wenemy);
void ChangeWInfo(WideEnemy* WenemSy, Player* player, const int WaitTime);
void ResetWEnemy(WideEnemy* Wenemy);

//��ź ���ʹ�

static HBITMAP BBitmap;
static HBITMAP EXBitmap[11];

static HBRUSH BBrush;
static HPEN BPen;


class BombEnemy : public MoveEnemy {
public:
	explicit BombEnemy(int C, int D, int X, int Y);

	void SetDropPos();									//DXPos���� DYPos���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//��ź�� ���� �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;			//��ź�� ��ź�� �׸���.
};

void CreateBEnemy(BombEnemy** Benemy, HINSTANCE hInst);
void DeleteBEnemy(BombEnemy** Benemy);
void SelectBShot(BombEnemy** Benemy, const int WaitTime);
int ChangeBInfo(BombEnemy** Benemy, Player* player);
void ResetBEnemy(BombEnemy** Benemy);

//���� ����� ���ʹ�

static HBITMAP ABitmap;
static HBITMAP ASBitmap[11];

static HBRUSH ABrush;
static HPEN APen;

class AirEnemy : public MoveEnemy {
public:
	explicit AirEnemy(int C, int D, int X, int Y, int DX, int DY);

	const int GetDXPos() const;
	const int GetDYPos() const;

	void SetDropPos(Player* player);									//DXPos���� DYPos���� ���Ѵ�.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;					//���� ����⸦ �׸���.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;		//���� ��������� �׸���.

private:
	int DXPos;
	int DYPos;
};

void CreateAEnemy(AirEnemy** Aenemy, HINSTANCE hInst);
void DeleteAEnemy(AirEnemy** Aenemy);
void SelectAShot(AirEnemy** Aenemy, Player* player, const int WaitTime);
int ChangeAInfo(AirEnemy** Aenemy, Player* player);
void ResetAEnemy(AirEnemy** Aenemy);


//��ü ���ʹ� ���� �ý���

void AllEnemySet(LineEnemy** LEnemy, WideEnemy* WEnemy, BombEnemy** BEnemy, AirEnemy** AEnemy, Player* player, LevelSet* Level);
void AllEnemyReset(LineEnemy** LEnemy, WideEnemy* WEnemy, BombEnemy** BEnemy, AirEnemy** AEnemy);
void AllEnemyPaint(LineEnemy** LEnemy, WideEnemy* WEnemy, BombEnemy** BEnemy, AirEnemy** AEnemy, HDC Gamedc[]);