#include "Resourec.h"
#include "LoadingPage.h"

void CreateLoadingPage() {
	LoadingPageFont1 = CreateFontW(20, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	LoadingPageBrush1 = CreateSolidBrush(RGB(140, 140, 140));
	LoadingPageBrush2 = CreateSolidBrush(RGB(204, 61, 61));
	LoadingPagePen1 = CreatePen(PS_SOLID, 1, RGB(140, 140, 140));
}

void DeleteLoadingPage() {
	DeleteObject(LoadingPagePen1);
	DeleteObject(LoadingPageBrush1);
	DeleteObject(LoadingPageBrush2);
	DeleteObject(LoadingPageFont1);
}

void PaintLoadingPage(HDC hdc, const int p) {
	//로딩 페이지 구현

	SelectObject(hdc, LoadingPageBrush1);
	SelectObject(hdc, LoadingPagePen1);
	Rectangle(hdc, WindowX / 2 - 200, WindowY / 2 - 25, WindowX / 2 + 200, WindowY / 2 + 25);

	SelectObject(hdc, LoadingPageBrush2);
	Rectangle(hdc, WindowX / 2 - 200, WindowY / 2 - 25, (WindowX / 2 - 200) + p * 2, WindowY / 2 + 25);

	SelectObject(hdc, LoadingPageFont1);
	SetBkColor(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	wchar_t str[15];
	swprintf_s(str, L"Loading...%d%d%d%%", p / 200, p / 20 % 10, p / 2 % 10);
	TextOut(hdc, WindowX / 2 - 200, WindowY / 2 - 50, str, sizeof(str) / sizeof(wchar_t));
}
