#pragma once
#include <windows.h>

//CreditPage���� ���Ǵ� �͵�

static HFONT CreditPageFont1;

void CreateCreditPage();
void DeleteCreditPage();
void PaintCreditPage(HDC hdc, HDC Bithdc);
