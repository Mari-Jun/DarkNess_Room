#pragma once

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <mmsystem.h>
#include <wingdi.h>
#include <fmod.h>

#pragma comment(lib,"winmm")
#pragma comment(lib,"fmodL_vc.lib")
#pragma comment(lib,"msimg32.lib")

using namespace std;

static const int FrameX = GetSystemMetrics(SM_CXFRAME);
static const int FrameY = GetSystemMetrics(SM_CYFRAME);
static const int CaptionY = GetSystemMetrics(SM_CYCAPTION);
static const int ScreenX = 1280;
static const int ScreenY = 820;
static const int WindowX = ScreenX + (FrameX << 2);
static const int WindowY = ScreenY + (FrameY << 2) + CaptionY;
static const int WindowPosX = (GetSystemMetrics(SM_CXSCREEN) - WindowX) / 2;
static const int WindowPosY = (GetSystemMetrics(SM_CYSCREEN) - WindowY) / 2;

//전체 맵
static const int ALLMAPX = 1440;
static const int ALLMAPY = 1530;

//카메라 맵
static const int CLEFTWALL = 30;
static const int CRIGHTWALL = 1410;
static const int CTOPWALL = 30;
static const int CBOTTOMWALL = 1410;

//플레이 공간 맵
static const int LEFTWALL = 120;
static const int RIGHTWALL = 1320;
static const int TOPWALL = 120;
static const int BOTTOMWALL = 1320;

//중간 섬
static const int LLEFTWALL = (LEFTWALL + RIGHTWALL) / 2 - 120;
static const int LRIGHTWALL = LLEFTWALL + 240;
static const int LTOPWALL = (TOPWALL + BOTTOMWALL) / 2 - 120;
static const int LBOTTOMWALL = LTOPWALL + 240;

//플레이어 인터페이스 맵
static const int PLEFTWALL = 30;
static const int PRIGHTWALL = 1250;
static const int PTOPWALL = 1440;
static const int PBOTTOMWALL = 1500;

//에너미 최대 수
static const int LENEMYMAX = 80;
static const int BENEMYMAX = 4;