#pragma once
#include "windows.h"

class Player;

//기본 에너미
class Enemy {
public:
	Enemy(int X, int Y, bool C);						//생성자

	const int GetXPos() const;							//XPos값 얻기
	const int GetYPos() const;							//YPos값 얻기
	const bool GetCharging() const;						//Charging값 얻기
	
	void ChangeCharging();								//Charging값을 바꾼다.
	void SetCharging();									//공격 턴이 끝났을 때 모든 Charging값을 false로 바꾼다.

private:
	int XPos;											//적의 X축 위치
	int YPos;											//적의 Y축 위치
	bool Charging;										//충전 상태
};



//직선포 에너미
class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, int C, int R);				//생성자

	const int GetRange() const;							//Range값 얻기

	void SetRange();									//Range값을 정한다.
		
	void PaintLEnmey(HDC hdc) const;					//직선포적 적을 그린다.
	void PaintLShot(HDC hdc) const;						//직선포적 포를 그린다.
private:
	int Range;											//피격 범위
};

//광역포 에너미
class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, int C, int D);				//생성자

	const int GetDirection() const;						//Direction값 얻기

	void SetDirection();								//Direction값을 정한다.

	void PaintWEnmey(HDC hdc) const;					//광역포적 적을 그린다.
	void PaintWShot(HDC hdc) const;						//광역포적 포를 그린다.
private:
	int Direction;										//광역 방향
};

//폭탄 에너미
class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, int C, int DX, int DY);		//생성자

	const int GetDXPos() const;					//DXPos값 얻기
	const int GetDYPos() const;					//DYPos값 얻기

	virtual void SetDropPos();							//DXPos값과 DYPos값을 정한다.

	void PaintBEnmey(HDC hdc) const;					//폭탄적 적을 그린다.
	void PaintBShot(HDC hdc) const;						//폭탄적 폭탄을 그린다.
private:
	int DXPos;											//떨어지는 X축 위치
	int DYPos;											//떨어지는 Y축 위치
};

//범위포 에너미
class RectEnemy : public BombEnemy {
public:
	RectEnemy(int X, int Y, int C, int DX, int DY, int Co);	//생성자

	const int GetCount() const;								//Count값 얻기

	void SetCount();										//Count값을 정한다.

	void PaintREnmey(HDC hdc) const;						//범위포적 적을 그린다.
	void PaintRShot(HDC hdc) const;							//범위포적 포를 그린다.
private:
	int Count;												//떨어지는 포의 개수
};







