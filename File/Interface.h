#pragma once
#include <windows.h>

static HBRUSH BackGroundBrush1;
static HBRUSH BackGroundBrush2;
static HBRUSH BackGroundBrush3;
static HBRUSH OldBackGroundBrush;

static HPEN BackGroundPen1;
static HPEN BackGroundPen2;
static HPEN BackGroundPen3;

void CreateInterface();				//����� ��ü �ʱ�ȭ
void DeleteInterface();				//���� ��ü ����
void PaintBackGround(HDC hdc);