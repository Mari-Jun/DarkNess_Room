#pragma once
#include "windows.h"

static HBRUSH OldEBrush;
static HPEN OldEPen;

class Player;
class LevelSet;

//기본 에너미
class Enemy {
public:
	explicit Enemy(int C, int D);							

	const int GetCharging() const;									//Charging값 얻기
	const int GetDelay() const;										//Delay값 얻기
	
	void SetCharging();												//Charging값을 지정한다. (사실상 고정)
	bool ChangeCharging();											//Charging값을 1씩 감소시킨다.
	void SetDelay(int D);											//Delay값을 지정한다.
	bool ChangeDelay();												//Delay값을 1씩 감소시킨다.
	void Reset();

	virtual void SetHitCheck(Player* player, const bool OnOff) const = 0;		//HitCheck를 설정한다.

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const = 0;
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2S) const = 0;
	
private:
	
	int Charging;													//남은 발사 시간
	int Delay;														//남은 발사 시작 시간
};

//고정 에너미
class FixEnemy : public Enemy {
public:
	explicit FixEnemy(int C, int D, int X, int Y);

	const int GetXPos() const;										//XPos값 얻기
	const int GetYPos() const;										//YPos값 얻기

private:
	int XPos;														//적의 X축 위치
	int YPos;														//적의 Y축 위치
};

//이동 에너미
class MoveEnemy : public Enemy {
public:
	explicit MoveEnemy(int C, int D, int X, int Y);

	const int GetXPos() const;										//XPos값 얻기
	const int GetYPos() const;										//YPos값 얻기

	void ChangeXPos(int X);											//XPos값 변경
	void ChangeYPos(int Y);											//YPos값 변경

private:
	int XPos;														//적의 X축 위치
	int YPos;														//적의 Y축 위치
};


//직선포 에너미

static HBITMAP LBitMap[4];
static HBITMAP LSBitMap[22];

static HBRUSH LBrush;
static HPEN LPen;

class LineEnemy : public FixEnemy {
public:
	explicit LineEnemy(int C, int D, int X, int Y, int R, int Di);

	const int GetRange() const;									//Range값 얻기
	const int GetDirection() const;								//Direction값 얻기 1: 위 2: 왼 -2: 오 -1: 아래

	void SetRange();											//Range값을 정한다.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;
		
	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//직선포적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//직선포적 포를 그린다.
private:
	int Range;													//피격 범위
	int Direction;												//포 방향
};

void CreateLEnemy(LineEnemy** Lenemy, HINSTANCE hInst);
void DeleteLEnemy(LineEnemy** Lenemy);
void SelectLShot(LineEnemy** Lenemy, const int WaitTime);
int ChangeLInfo(LineEnemy** Lenmey, Player* player);
void ResetLEnemy(LineEnemy** Lenemy);


//광역포 에너미

static HBITMAP WEBitmap1;
static HBITMAP WEBitmap2;
static HBITMAP WSBitmap[7];

static HBRUSH WSBrush;
static HPEN WSPen;


class WideEnemy : public FixEnemy {
public:
	explicit WideEnemy(int C, int D, int X, int Y, int Di);

	const int GetDirection() const;								//Direction값 얻기

	void SetDirection();										//Direction값을 정한다.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//광역포적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;						//광역포적 포를 그린다.
private:
	int Direction;												//광역 방향
};

void CreateWEnemy(WideEnemy** Wenemy, HINSTANCE hInst);
void DeleteWEnemy(WideEnemy** Wenemy);
void ChangeWInfo(WideEnemy* WenemSy, Player* player, const int WaitTime);
void ResetWEnemy(WideEnemy* Wenemy);

//폭탄 에너미

static HBITMAP BBitmap;
static HBITMAP EXBitmap[11];

static HBRUSH BBrush;
static HPEN BPen;


class BombEnemy : public MoveEnemy {
public:
	explicit BombEnemy(int C, int D, int X, int Y);

	void SetDropPos();									//DXPos값과 DYPos값을 정한다.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;			//폭탄적 적을 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;			//폭탄적 폭탄을 그린다.
};

void CreateBEnemy(BombEnemy** Benemy, HINSTANCE hInst);
void DeleteBEnemy(BombEnemy** Benemy);
void SelectBShot(BombEnemy** Benemy, const int WaitTime);
int ChangeBInfo(BombEnemy** Benemy, Player* player);
void ResetBEnemy(BombEnemy** Benemy);

//유도 비행기 에너미

static HBITMAP ABitmap;
static HBITMAP ASBitmap[11];

static HBRUSH ABrush;
static HPEN APen;

class AirEnemy : public MoveEnemy {
public:
	explicit AirEnemy(int C, int D, int X, int Y, int DX, int DY);

	const int GetDXPos() const;
	const int GetDYPos() const;

	void SetDropPos(Player* player);									//DXPos값과 DYPos값을 정한다.

	virtual void SetHitCheck(Player* player, const bool OnOff) const;

	virtual void PaintEnmey(HDC hdc, HDC Bithdc) const;					//유도 비행기를 그린다.
	virtual void PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const;		//유도 비행기포를 그린다.

private:
	int DXPos;
	int DYPos;
};

void CreateAEnemy(AirEnemy** Aenemy, HINSTANCE hInst);
void DeleteAEnemy(AirEnemy** Aenemy);
void SelectAShot(AirEnemy** Aenemy, Player* player, const int WaitTime);
int ChangeAInfo(AirEnemy** Aenemy, Player* player);
void ResetAEnemy(AirEnemy** Aenemy);


//전체 에너미 관리 시스템

void AllEnemySet(LineEnemy** LEnemy, WideEnemy* WEnemy, BombEnemy** BEnemy, AirEnemy** AEnemy, Player* player, LevelSet* Level);
void AllEnemyReset(LineEnemy** LEnemy, WideEnemy* WEnemy, BombEnemy** BEnemy, AirEnemy** AEnemy);
void AllEnemyPaint(LineEnemy** LEnemy, WideEnemy* WEnemy, BombEnemy** BEnemy, AirEnemy** AEnemy, HDC Gamedc[]);