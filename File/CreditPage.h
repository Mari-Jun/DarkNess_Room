#pragma once
#include <windows.h>

//CreditPage에서 사용되는 것들

static HFONT CreditPageFont1;

void CreateCreditPage();
void DeleteCreditPage();
void PaintCreditPage(HDC hdc, HDC Bithdc);
