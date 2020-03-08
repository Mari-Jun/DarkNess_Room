#pragma once
#include <windows.h>

static HPEN BackGroundPen1;
static HPEN OldBackGroundPen;

static HFONT InterfaceFont1;

static HBITMAP BackGroundBit[4];

class Interface {
public:
	Interface(int L, int S);

	const int GetLevel() const;			//Level값 반환
	const int GetScore() const;			//Score값 반환

	void ChangeLevel();					//Level 변환
	void ChangeScore();					//Percent 변환

	void PaintInterface(HDC hdc);
	void PaintBackGround(HDC hdc, HDC Bithdc);
	void PaintBackGroundLine(HDC hdc);
private:
	int Level;
	int Score;
};

void CreateInterface(Interface** inter);				//사용할 객체 초기화
void DeleteInterface(Interface** inter);				//사용된 객체 삭제
//void PaintBackGround(HDC hdc, HDC Bithdc);