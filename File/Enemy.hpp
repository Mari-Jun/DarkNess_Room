#pragma once
#include "windows.h"

//�⺻ ���ʹ�
class Enemy {
public:
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
	virtual const int GetDXPos() const;					//DXPos�� ���
	virtual const int GetDYPos() const;					//DYPos�� ���

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
	virtual const int GetDXPos() const;					//DXPos�� ���
	virtual const int GetDYPos() const;					//DYPos�� ���
	const int GetCount() const;							//Count�� ���

	virtual void SetDropPos();							//DXPos���� DYPos���� ���Ѵ�.
	void SetCount();									//Count���� ���Ѵ�.

	void PaintREnmey(HDC hdc) const;					//�������� ���� �׸���.
	void PaintRShot(HDC hdc) const;						//�������� ���� �׸���.
private:
	int Count;											//�������� ���� ����
};







