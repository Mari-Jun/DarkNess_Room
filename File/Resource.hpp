#pragma once

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <mmsystem.h>
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

//ÀüÃ¼ ¸Ê
static const int ALLMAPX = 1440;
static const int ALLMAPY = 1530;

//Ä«¸Þ¶ó ¸Ê
static const int CLEFTWALL = 30;
static const int CRIGHTWALL = 1410;
static const int CTOPWALL = 30;
static const int CBOTTOMWALL = 1410;

//ÇÃ·¹ÀÌ °ø°£ ¸Ê
static const int LEFTWALL = 120;
static const int RIGHTWALL = 1320;
static const int TOPWALL = 120;
static const int BOTTOMWALL = 1320;

//Áß°£ ¼¶
static const int LLEFTWALL = (LEFTWALL + RIGHTWALL) / 2 - 120;
static const int LRIGHTWALL = LLEFTWALL + 240;
static const int LTOPWALL = (TOPWALL + BOTTOMWALL) / 2 - 120;
static const int LBOTTOMWALL = LTOPWALL + 240;

//ÇÃ·¹ÀÌ¾î ÀÎÅÍÆäÀÌ½º ¸Ê
static const int PLEFTWALL = 30;
static const int PRIGHTWALL = 1250;
static const int PTOPWALL = 1440;
static const int PBOTTOMWALL = 1500;