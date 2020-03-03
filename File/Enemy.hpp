#pragma once
#include "windows.h"

static HBRUSH OldEBrush;
static HPEN OldEPen;

class Player;

//기본 에너미
class Enemy {
public:
	explicit Enemy(int X, int Y, int C, int D);							

	const int GetXPos() const;										//XPos값 얻기
	const int GetYPos() const;										//YPos값 얻기
	const int GetCharging() const;									//Charging값 얻기
	const int GetDelay() const;										//Delay값 얻기
	
	void SetCharging();												//Charging값을 지정한다. (사실상 고정)
	bool ChangeCharging();											//Charging값을 1씩 감소시킨다.
	void SetDelay(int D);											//Delay값을 지정한다.
	bool ChangeDelay();												//Delay값을 1씩 감소시킨다.

	virtual void SetHitCheck(Player* player, bool OnOff) const = 0;		//HitCheck를 설정한다.

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const = 0;
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2S) const = 0;
	
private:
	int XPos;														//적의 X축 위치
	int YPos;														//적의 Y축 위치
	int Charging;													//남은 발사 시간
	int Delay;														//남은 발사 시작 시간
};



//직선포 에너미

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

	const int GetRange() const;									//Range값 얻기
	const int GetDirection() const;								//Direction값 얻기 1: 위 2: 왼 -2: 오 -1: 아래

	void SetRange();											//Range값을 정한다.

	virtual void SetHitCheck(Player* player, bool OnOff) const;
		
	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//직선포적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//직선포적 포를 그린다.
private:
	int Range;													//피격 범위
	int Direction;												//포 방향
};

void CreateLEnemy(LineEnemy** Lenemy);
void DeleteLEnemy(LineEnemy** Lenemy);
void SelectLShot(LineEnemy** Lenemy);
int ChangeLInfo(LineEnemy** Lenmey, Player* player);


//광역포 에너미

static HBRUSH WSBrush1;
static HBRUSH WSBrush2;

static HPEN WSPen;

static HBITMAP WEBitmap1;
static HBITMAP WEBitmap2;
static HBITMAP WSBitmap[7];


class WideEnemy : public Enemy {
public:
	WideEnemy(int X, int Y, int C, int D, int Di);

	const int GetDirection() const;								//Direction값 얻기

	void SetDirection();										//Direction값을 정한다.

	virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//광역포적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//광역포적 포를 그린다.
private:
	int Direction;												//광역 방향
};

void CreateWEnemy(WideEnemy** Wenemy);
void DeleteWEnemy(WideEnemy** Wenemy);
void ChangeWInfo(WideEnemy* WenemSy, Player* player);

//폭탄 에너미

static HBITMAP BBitmap;
static HBITMAP EXBitmap[11];

static HBRUSH BBrush1;
static HPEN BPen1;


class BombEnemy : public Enemy {
public:
	BombEnemy(int X, int Y, int C, int D, int DX, int DY);		

	const int GetDXPos() const;									//DXPos값 얻기
	const int GetDYPos() const;									//DYPos값 얻기

	virtual void SetDropPos();									//DXPos값과 DYPos값을 정한다.

	virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//폭탄적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;			//폭탄적 폭탄을 그린다.
private:
	int DXPos;													//떨어지는 X축 위치
	int DYPos;													//떨어지는 Y축 위치
};

void CreateBEnemy(BombEnemy** Benemy);
void DeleteBEnemy(BombEnemy** Benemy);
void SelectBShot(BombEnemy** Benemy);
int ChangeBInfo(BombEnemy** Benemy, Player* player);

//범위포 에너미
class RectEnemy : public BombEnemy {
public:
	RectEnemy(int X, int Y, int C, int D, int DX, int DY, int Co);	

	const int GetCount() const;										//Count값 얻기

	void SetCount();												//Count값을 정한다.

virtual void SetHitCheck(Player* player, bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;				//범위포적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;							//범위포적 포를 그린다.
private:
	int Count;														//떨어지는 포의 개수
};



void CreateREnemy(RectEnemy** Renemy);





