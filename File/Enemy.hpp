#pragma once
#include "windows.h"

class Player;

//�⺻ ���ʹ�
class Enemy {
public:
	Enemy(int X, int Y, bool C);						//������

	const int GetXPos() const;							//XPos�� ���
	const int GetYPos() const;							//YPos�� ���
	const bool GetCharging() const;						//Charging�� ���
	
	void ChangeCharging();								//Charging���� �ٲ۴�.
	void SetCharging();									//���� ���� ������ �� ��� Charging���� false�� �ٲ۴�.

private:
	int XPos;											//���� X�� ��ġ
	int YPos;											//���� Y�� ��ġ
	bool Charging;										//���� ����
};



//������ ���ʹ�
class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, int C, int R);				//������

	const int GetRange() const;							//Range�� ���

	void SetRange();									//Range���� ���Ѵ�.
		
	void PaintLEnmey(HDC hdc) const;					//�������� ���� �׸���.
	void PaintLShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Range;											//�ǰ� ����
};

//������ ���ʹ�
class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, int C, int D);				//������

	const int GetDirection() const;						//Direction�� ���

	void SetDirection();								//Direction���� ���Ѵ�.

	void PaintWEnmey(HDC hdc) const;					//�������� ���� �׸���.
	void PaintWShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Direction;										//���� ����
};

//��ź ���ʹ�
class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, int C, int DX, int DY);		//������

	const int GetDXPos() const;					//DXPos�� ���
	const int GetDYPos() const;					//DYPos�� ���

	virtual void SetDropPos();							//DXPos���� DYPos���� ���Ѵ�.

	void PaintBEnmey(HDC hdc) const;					//��ź�� ���� �׸���.
	void PaintBShot(HDC hdc) const;						//��ź�� ��ź�� �׸���.
private:
	int DXPos;											//�������� X�� ��ġ
	int DYPos;											//�������� Y�� ��ġ
};

//������ ���ʹ�
class RectEnemy : public BombEnemy {
public:
	RectEnemy(int X, int Y, int C, int DX, int DY, int Co);	//������

	const int GetCount() const;								//Count�� ���

	void SetCount();										//Count���� ���Ѵ�.

	void PaintREnmey(HDC hdc) const;						//�������� ���� �׸���.
	void PaintRShot(HDC hdc) const;							//�������� ���� �׸���.
private:
	int Count;												//�������� ���� ����
};







