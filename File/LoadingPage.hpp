#pragma once
#include <windows.h>

//LoadingPage에서 사용되는 것들
static HFONT LoadingPageFont1;
static HFONT LoadingPageFont2;

static HBRUSH LoadingPageBrush1;
static HBRUSH LoadingPageBrush2;

static HPEN LoadingPagePen1;

void CreateLoadingPage();
void DeleteLoadingPage();
void PaintLoadingPage(HDC hdc, const int Count, const int Page);
