#pragma once
#include "windows.h"

class Player;

//�⺻ ���ʹ�
class Enemy {
public:
	explicit Enemy(int X, int Y, bool C, int D);							

	const int GetXPos() const;										//XPos�� ���
	const int GetYPos() const;										//YPos�� ���
	const bool GetCharging() const;									//Charging�� ���
	const int GetDelay() const;										//Delay�� ���
	
	void ChangeCharging();											//Charging���� �ٲ۴�.
	void SetCharging();												//���� ���� ������ �� ��� Charging���� false�� �ٲ۴�.
	void ChangeDelay();												//Delay���� �ٲ۴�.

	//��� �� ���� �����Լ�
	virtual const bool HitPlayer(Player* player) const = 0;			//�ǰ� Ȯ��	

	virtual void PaintEnmey(HDC hdc) const = 0;
	virtual void PaintShot(HDC hdc) const = 0;
	
private:
	int XPos;														//���� X�� ��ġ
	int YPos;														//���� Y�� ��ġ
	bool Charging;													//���� ����
	int Delay;														//�߻� ������ �ð�
};



//������ ���ʹ�
class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, bool C, int D, int R);				

	const int GetRange() const;									//Range�� ���

	void SetRange();											//Range���� ���Ѵ�.

	virtual const bool HitPlayer(Player* player) const;			//�ǰ� Ȯ��
		
	virtual void PaintEnmey(HDC hdc) const;						//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Range;													//�ǰ� ����
};

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
	BombEnemy(int X, int Y, bool C, int D, int DX, int DY);		

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
	RectEnemy(int X, int Y, bool C, int D, int DX, int DY, int Co);	

	const int GetCount() const;										//Count�� ���

	void SetCount();												//Count���� ���Ѵ�.

	virtual const bool HitPlayer(Player* player) const;			//�ǰ� Ȯ��

	virtual void PaintEnmey(HDC hdc) const;							//�������� ���� �׸���.
	virtual void PaintShot(HDC hdc) const;							//�������� ���� �׸���.
private:
	int Count;														//�������� ���� ����
};


void CreateLEnemy(LineEnemy** Lenemy);
void CreateWEnemy(WideEnemy** Wenemy);
void CreateBEnemy(BombEnemy** Benemy);
void CreateREnemy(RectEnemy** Renemy);





