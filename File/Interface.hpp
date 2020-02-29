#pragma once
#include <windows.h>

static HBRUSH OldBackGroundBrush;

static HPEN BackGroundPen1;
static HPEN OldBackGroundPen;

static HBITMAP BackGroundBit[4];

class Interface {
public:
	Interface(int L, int P);

	const int GetLevel() const;			//Level값 반환
	const int GetPercent() const;		//Percent값 반환

	void ChangeLevel();					//Level 변환
	void ChangePercent();				//Percent 변환

	void PaintBackGround(HDC hdc, HDC Bithdc);
	void PaintBackGroundLine(HDC hdc);
private:
	int Level;
	int Percent;
};

void CreateInterface(Interface** inter);				//사용할 객체 초기화
void DeleteInterface(Interface** inter);				//사용된 객체 삭제
//void PaintBackGround(HDC hdc, HDC Bithdc);