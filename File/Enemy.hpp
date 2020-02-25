#pragma once
#include "windows.h"

static int EDelay[100];
static int ECharging[100];

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
	void ChangeCharging();											//Charging���� 1�� ���ҽ�Ų��.
	void SetDelay();												//Delay���� �����Ѵ�.
	void ChangeDelay();												//Delay���� 1�� ���ҽ�Ų��.

	//��� �� ���� �����Լ�
	virtual const bool HitPlayer(Player* player) const = 0;			//�ǰ� Ȯ��	

	virtual void PaintEnmey(HDC hdc) const = 0;
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


class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, int C, int D, int R, int Di);				

	const int GetRange() const;									//Range�� ���
	const int GetDirection() const;								//Direction�� ��� 1: �� 2: �� -2: �� -1: �Ʒ�

	void SetRange();											//Range���� ���Ѵ�.

	virtual const bool HitPlayer(Player* player) const;			//�ǰ� Ȯ��
		
	virtual void PaintEnmey(HDC hdc) const;						//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Range;													//�ǰ� ����
	int Direction;												//�� ����
};

void CreateLEnemy(LineEnemy** Lenemy);
void DeleteLEnemy(LineEnemy** Lenemy);
void SelectLShot(LineEnemy** Lenemy);



//������ ���ʹ�
class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, bool C, int D, int Di);

	const int GetDirection() const;								//Direction�� ���

	void SetDirection();										//Direction���� ���Ѵ�.

	virtual const bool HitPlayer(Player* player) const;			//�ǰ� Ȯ��

	virtual void PaintEnmey(HDC hdc) const;						//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Direction;												//���� ����
};

//��ź ���ʹ�
class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, int C, int D, int DX, int DY);		

	const int GetDXPos() const;									//DXPos�� ���
	const int GetDYPos() const;									//DYPos�� ���

	virtual void SetDropPos();									//DXPos���� DYPos���� ���Ѵ�.

	virtual const bool HitPlayer(Player* player) const;			//�ǰ� Ȯ��

	virtual void PaintEnmey(HDC hdc) const;						//��ź�� ���� �׸���.
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

	virtual const bool HitPlayer(Player* player) const;				//�ǰ� Ȯ��

	virtual void PaintEnmey(HDC hdc) const;							//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;							//�������� ���� �׸���.
private:
	int Count;														//�������� ���� ����
};



void CreateWEnemy(WideEnemy** Wenemy);
void CreateBEnemy(BombEnemy** Benemy);
void CreateREnemy(RectEnemy** Renemy);





