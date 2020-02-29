#pragma once
#include <windows.h>

static HBRUSH OldBackGroundBrush;

static HPEN BackGroundPen1;
static HPEN OldBackGroundPen;

static HBITMAP BackGroundBit[4];

class Interface {
public:
	Interface(int L, int P);

	const int GetLevel() const;			//Level�� ��ȯ
	const int GetPercent() const;		//Percent�� ��ȯ

	void ChangeLevel();					//Level ��ȯ
	void ChangePercent();				//Percent ��ȯ

	void PaintBackGround(HDC hdc, HDC Bithdc);
	void PaintBackGroundLine(HDC hdc);
private:
	int Level;
	int Percent;
};

void CreateInterface(Interface** inter);				//����� ��ü �ʱ�ȭ
void DeleteInterface(Interface** inter);				//���� ��ü ����
//void PaintBackGround(HDC hdc, HDC Bithdc);