#pragma once
#include <windows.h>

static HBRUSH BackGroundBrush1;
static HBRUSH BackGroundBrush2;
static HBRUSH BackGroundBrush3;
static HBRUSH OldBackGroundBrush;

static HPEN BackGroundPen1;
static HPEN BackGroundPen2;
static HPEN BackGroundPen3;

void CreateInterface();				//사용할 객체 초기화
void DeleteInterface();				//사용된 객체 삭제
void PaintBackGround(HDC hdc);