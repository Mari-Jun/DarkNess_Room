#pragma once
#include <windows.h>

static HBRUSH BackGroundBrush1;
static HBRUSH BackGroundBrush2;
static HBRUSH BackGroundBrush3;
static HBRUSH OldBackGroundBrush;

static HPEN BackGroundPen1;
static HPEN BackGroundPen2;
static HPEN BackGroundPen3;

static HBITMAP BackGroundBit1;
static HBITMAP BackGroundBit2;
static HBITMAP BackGroundBit3;
static HBITMAP BackGroundBit4;
static HBITMAP OldBackGroundBit;

void CreateInterface();				//����� ��ü �ʱ�ȭ
void DeleteInterface();				//���� ��ü ����
void PaintBackGround(HDC hdc, HDC Bithdc);