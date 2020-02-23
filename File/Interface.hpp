#pragma once
#include <windows.h>

static HBRUSH OldBackGroundBrush;

static HPEN BackGroundPen1;

static HBITMAP BackGroundBit1;
static HBITMAP BackGroundBit2;
static HBITMAP BackGroundBit3;
static HBITMAP BackGroundBit4;
static HBITMAP OldBackGroundBit;

void CreateInterface();				//사용할 객체 초기화
void DeleteInterface();				//사용된 객체 삭제
void PaintBackGround(HDC hdc, HDC Bithdc);