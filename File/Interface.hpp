#pragma once
#include <windows.h>

static HPEN BackGroundPen1;
static HPEN OldBackGroundPen;

static HFONT InterfaceFont1;

static HBITMAP BackGroundBit[4];

class Interface {
public:
	Interface(int L, int S);

	const int GetLevel() const;			//Level�� ��ȯ
	const int GetScore() const;			//Score�� ��ȯ

	void ChangeLevel();					//Level ��ȯ
	void ChangeScore();					//Percent ��ȯ

	void PaintInterface(HDC hdc);
	void PaintBackGround(HDC hdc, HDC Bithdc);
	void PaintBackGroundLine(HDC hdc);
private:
	int Level;
	int Score;
};

void CreateInterface(Interface** inter);				//����� ��ü �ʱ�ȭ
void DeleteInterface(Interface** inter);				//���� ��ü ����
//void PaintBackGround(HDC hdc, HDC Bithdc);