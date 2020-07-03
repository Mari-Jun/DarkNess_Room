#include "Resource.hpp"
#include "Interface.hpp"

Interface::Interface(int L, int S, int U) : Level(L), Score(S), ScoreUp(U) {

}

const int Interface::GetLevel() const {
	//Level을 반환한다.
	return Level;
}

const int Interface::GetScore() const {
	//Percent를 반환한다.
	return Score;
}

void Interface::ChangeLevel() {
	//Level을 1올린다.
	Level++;
}

void Interface::ChangeScore() {
	//ScoreUp을 10씩 증가시켜주고
	//Score에 ScoreUp을 더한다.

	ScoreUp += Level;
	Score += ScoreUp;
}

void Interface::ResetScoreUp() {
	//Player의 체력이 깎였음으로 ScoreUp을 Reset해준다.
	ScoreUp /= 2;
}

void Interface::PaintInterface(HDC hdc) {
	//Level과 Score를 그려준다.

	SelectObject(hdc, InterfaceFont1);

	TextOut(hdc, 840, PTOPWALL + 5, _T("LEVEL"), 5);

	//Level 출력
	wchar_t str1[10];
	swprintf_s(str1, L"%d%d", Level / 10, Level % 10);
	TextOut(hdc, 940, PTOPWALL + 5, str1, 3);

	TextOut(hdc, 1000, PTOPWALL + 5, _T("SCORE"), 5);

	//Score 출력
	wchar_t str2[10];
	swprintf_s(str2, L"%d%d%d%d%d%d%d", Score / 1000000, Score / 100000 % 10, Score / 10000 % 10, Score / 1000 % 10, Score / 100 % 10, Score / 10 % 10, Score % 10);
	TextOut(hdc, 1110, PTOPWALL + 5, str2, 7);
}

void Interface::PaintBackGround(HDC hdc, HDC Bithdc) {

	//겉 테두리 그리기 (전체맵)
	SelectObject(Bithdc, BackGroundBit[0]);
	//위쪽
	BitBlt(hdc, 0, 0, ALLMAPX, CTOPWALL, Bithdc, 0, 0, SRCCOPY);
	//왼쪽
	BitBlt(hdc, 0, 30, CLEFTWALL, ALLMAPY - 30, Bithdc, 0, 0, SRCCOPY);
	//오른쪽
	BitBlt(hdc, CRIGHTWALL, 30, 30, ALLMAPY - 30, Bithdc, CRIGHTWALL, 0, SRCCOPY);
	//인터페이스 위쪽
	BitBlt(hdc, 30, CBOTTOMWALL, ALLMAPX - 60, 30, Bithdc, 0, CBOTTOMWALL, SRCCOPY);
	//인터페이스 아래쪽
	BitBlt(hdc, 30, PBOTTOMWALL, ALLMAPX - 60, 30, Bithdc, 0, PBOTTOMWALL, SRCCOPY);


	//벽(카메라맵) 그리기
	SelectObject(Bithdc, BackGroundBit[1]);
	//위쪽 벽
	BitBlt(hdc, CLEFTWALL, CTOPWALL, CRIGHTWALL - CLEFTWALL, TOPWALL - CTOPWALL, Bithdc, 0, 0, SRCCOPY);
	//왼쪽 벽
	BitBlt(hdc, CLEFTWALL, CTOPWALL + 90, LEFTWALL - CLEFTWALL, CBOTTOMWALL - CTOPWALL - 90, Bithdc, 0, 0, SRCCOPY);
	//아래쪽 벽
	BitBlt(hdc, CLEFTWALL + 90, BOTTOMWALL, CRIGHTWALL - CLEFTWALL - 90, CBOTTOMWALL - BOTTOMWALL, Bithdc, 0, 0, SRCCOPY);
	//오른쪽 벽
	BitBlt(hdc, RIGHTWALL, CTOPWALL + 90, CRIGHTWALL - RIGHTWALL, CBOTTOMWALL - CTOPWALL - 180, Bithdc, 0, 0, SRCCOPY);


	//플레이 맵 그리기
	SelectObject(Bithdc, BackGroundBit[2]);
	BitBlt(hdc, LEFTWALL, TOPWALL, RIGHTWALL - LEFTWALL, BOTTOMWALL - TOPWALL, Bithdc, 0, 0, SRCCOPY);

	//중간 섬 그리기
	SelectObject(Bithdc, BackGroundBit[1]);
	BitBlt(hdc, LLEFTWALL, LTOPWALL, 240, 240, Bithdc, 0, 0, SRCCOPY);


	//플레이어 인터페이스 그리기
	SelectObject(Bithdc, BackGroundBit[3]);
	BitBlt(hdc, PLEFTWALL, PTOPWALL, PRIGHTWALL - PLEFTWALL, PBOTTOMWALL - PTOPWALL, Bithdc, 0, 0, SRCCOPY);	
}

void Interface::PaintBackGroundLine(HDC hdc) {

	OldBackGroundPen = (HPEN)SelectObject(hdc, BackGroundPen1);
	
	//선 그리기
	for (int x = LEFTWALL + 60; x < RIGHTWALL; x += 60) {
		MoveToEx(hdc, x, TOPWALL, NULL);
		LineTo(hdc, x, BOTTOMWALL);
	}
	for (int y = TOPWALL + 60; y < BOTTOMWALL; y += 60) {
		MoveToEx(hdc, LEFTWALL, y, NULL);
		LineTo(hdc, RIGHTWALL, y);
	}

	SelectObject(hdc, OldBackGroundPen);
}

void CreateInterface(Interface** inter, HINSTANCE hInst) {
	if (*inter == NULL) {
		*inter = new Interface(1, 0 ,0);
	}

	//GameInterface에 사용될 객체들 생성

	BackGroundPen1 = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));

	for (int i = 0; i < 4; i++) {
		/*wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\Interface%d.bmp", i + 1);
		BackGroundBit[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/
		BackGroundBit[i] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Interface1 + i));
	}

	InterfaceFont1 = CreateFontW(50, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
}

void DeleteInterface(Interface** inter) {
	if (*inter != NULL) {
		delete* inter;
		*inter = NULL;
	}
	//메모리 해제
	DeleteObject(BackGroundPen1);
	DeleteObject(InterfaceFont1);
	for (int i = 0; i < 4; i++)
		DeleteObject(BackGroundBit[i]);

}
