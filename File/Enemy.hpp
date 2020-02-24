#pragma once
#include "windows.h"

class Player;

//기본 에너미
class Enemy {
public:
	explicit Enemy(int X, int Y, bool C, int D);							

	const int GetXPos() const;										//XPos값 얻기
	const int GetYPos() const;										//YPos값 얻기
	const bool GetCharging() const;									//Charging값 얻기
	const int GetDelay() const;										//Delay값 얻기
	
	void ChangeCharging();											//Charging값을 바꾼다.
	void SetCharging();												//공격 턴이 끝났을 때 모든 Charging값을 false로 바꾼다.
	void ChangeDelay();												//Delay값을 바꾼다.

	//모든 적 순수 가상함수
	virtual const bool HitPlayer(Player* player) const = 0;			//피격 확인	

	virtual void PaintEnmey(HDC hdc) const = 0;
	virtual void PaintShot(HDC hdc) const = 0;
	
private:
	int XPos;														//적의 X축 위치
	int YPos;														//적의 Y축 위치
	bool Charging;													//충전 상태
	int Delay;														//발사 딜레이 시간
};



//직선포 에너미
class LineEnemy : public Enemy {
public:
	LineEnemy(int X, int Y, bool C, int D, int R);				

	const int GetRange() const;									//Range값 얻기

	void SetRange();											//Range값을 정한다.

	virtual const bool HitPlayer(Player* player) const;			//피격 확인
		
	virtual void PaintEnmey(HDC hdc) const;						//직선포적 적을 그린다.
	virtual void PaintShot(HDC hdc) const;						//직선포적 포를 그린다.
private:
	int Range;													//피격 범위
};

//광역포 에너미
class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, bool C, int D, int Di);

	const int GetDirection() const;								//Direction값 얻기

	void SetDirection();										//Direction값을 정한다.

	virtual const bool HitPlayer(Player* player) const;			//피격 확인

	virtual void PaintEnmey(HDC hdc) const;						//광역포적 적을 그린다.
	virtual void PaintShot(HDC hdc) const;						//광역포적 포를 그린다.
private:
	int Direction;												//광역 방향
};

//폭탄 에너미
class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, bool C, int D, int DX, int DY);		

	const int GetDXPos() const;									//DXPos값 얻기
	const int GetDYPos() const;									//DYPos값 얻기

	virtual void SetDropPos();									//DXPos값과 DYPos값을 정한다.

	virtual const bool HitPlayer(Player* player) const;			//피격 확인

	virtual void PaintEnmey(HDC hdc) const;						//폭탄적 적을 그린다.
	virtual void PaintShot(HDC hdc) const;						//폭탄적 폭탄을 그린다.
private:
	int DXPos;													//떨어지는 X축 위치
	int DYPos;													//떨어지는 Y축 위치
};

//범위포 에너미
class RectEnemy : public BombEnemy {
public:
	RectEnemy(int X, int Y, bool C, int D, int DX, int DY, int Co);	

	const int GetCount() const;										//Count값 얻기

	void SetCount();												//Count값을 정한다.

	virtual const bool HitPlayer(Player* player) const;			//피격 확인

	virtual void PaintEnmey(HDC hdc) const;							//범위포적 적을 그린다.
	virtual void PaintShot(HDC hdc) const;							//범위포적 포를 그린다.
private:
	int Count;														//떨어지는 포의 개수
};


void CreateLEnemy(LineEnemy** Lenemy);
void CreateWEnemy(WideEnemy** Wenemy);
void CreateBEnemy(BombEnemy** Benemy);
void CreateREnemy(RectEnemy** Renemy);





