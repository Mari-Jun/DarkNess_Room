#include "Resource.hpp"
#include "Interface.hpp"

Interface::Interface(int L, int S, int U) : Level(L), Score(S), ScoreUp(U) {

}

const int Interface::GetLevel() const {
	//Level�� ��ȯ�Ѵ�.
	return Level;
}

const int Interface::GetScore() const {
	//Percent�� ��ȯ�Ѵ�.
	return Score;
}

void Interface::ChangeLevel() {
	//Level�� 1�ø���.
	Level++;
}

void Interface::ChangeScore() {
	//ScoreUp�� 10�� ���������ְ�
	//Score�� ScoreUp�� ���Ѵ�.

	ScoreUp += Level;
	Score += ScoreUp;
}

void Interface::ResetScoreUp() {
	//Player�� ü���� �������� ScoreUp�� Reset���ش�.
	ScoreUp /= 2;
}

void Interface::PaintInterface(HDC hdc) {
	//Level�� Score�� �׷��ش�.

	SelectObject(hdc, InterfaceFont1);

	TextOut(hdc, 840, PTOPWALL + 5, _T("LEVEL"), 5);

	//Level ���
	wchar_t str1[10];
	swprintf_s(str1, L"%d%d", Level / 10, Level % 10);
	TextOut(hdc, 940, PTOPWALL + 5, str1, 3);

	TextOut(hdc, 1000, PTOPWALL + 5, _T("SCORE"), 5);

	//Score ���
	wchar_t str2[10];
	swprintf_s(str2, L"%d%d%d%d%d%d%d", Score / 1000000, Score / 100000 % 10, Score / 10000 % 10, Score / 1000 % 10, Score / 100 % 10, Score / 10 % 10, Score % 10);
	TextOut(hdc, 1110, PTOPWALL + 5, str2, 7);
}

void Interface::PaintBackGround(HDC hdc, HDC Bithdc) {

	//�� �׵θ� �׸��� (��ü��)
	SelectObject(Bithdc, BackGroundBit[0]);
	//����
	BitBlt(hdc, 0, 0, ALLMAPX, CTOPWALL, Bithdc, 0, 0, SRCCOPY);
	//����
	BitBlt(hdc, 0, 30, CLEFTWALL, ALLMAPY - 30, Bithdc, 0, 0, SRCCOPY);
	//������
	BitBlt(hdc, CRIGHTWALL, 30, 30, ALLMAPY - 30, Bithdc, CRIGHTWALL, 0, SRCCOPY);
	//�������̽� ����
	BitBlt(hdc, 30, CBOTTOMWALL, ALLMAPX - 60, 30, Bithdc, 0, CBOTTOMWALL, SRCCOPY);
	//�������̽� �Ʒ���
	BitBlt(hdc, 30, PBOTTOMWALL, ALLMAPX - 60, 30, Bithdc, 0, PBOTTOMWALL, SRCCOPY);


	//��(ī�޶��) �׸���
	SelectObject(Bithdc, BackGroundBit[1]);
	//���� ��
	BitBlt(hdc, CLEFTWALL, CTOPWALL, CRIGHTWALL - CLEFTWALL, TOPWALL - CTOPWALL, Bithdc, 0, 0, SRCCOPY);
	//���� ��
	BitBlt(hdc, CLEFTWALL, CTOPWALL + 90, LEFTWALL - CLEFTWALL, CBOTTOMWALL - CTOPWALL - 90, Bithdc, 0, 0, SRCCOPY);
	//�Ʒ��� ��
	BitBlt(hdc, CLEFTWALL + 90, BOTTOMWALL, CRIGHTWALL - CLEFTWALL - 90, CBOTTOMWALL - BOTTOMWALL, Bithdc, 0, 0, SRCCOPY);
	//������ ��
	BitBlt(hdc, RIGHTWALL, CTOPWALL + 90, CRIGHTWALL - RIGHTWALL, CBOTTOMWALL - CTOPWALL - 180, Bithdc, 0, 0, SRCCOPY);


	//�÷��� �� �׸���
	SelectObject(Bithdc, BackGroundBit[2]);
	BitBlt(hdc, LEFTWALL, TOPWALL, RIGHTWALL - LEFTWALL, BOTTOMWALL - TOPWALL, Bithdc, 0, 0, SRCCOPY);

	//�߰� �� �׸���
	SelectObject(Bithdc, BackGroundBit[1]);
	BitBlt(hdc, LLEFTWALL, LTOPWALL, 240, 240, Bithdc, 0, 0, SRCCOPY);


	//�÷��̾� �������̽� �׸���
	SelectObject(Bithdc, BackGroundBit[3]);
	BitBlt(hdc, PLEFTWALL, PTOPWALL, PRIGHTWALL - PLEFTWALL, PBOTTOMWALL - PTOPWALL, Bithdc, 0, 0, SRCCOPY);	
}

void Interface::PaintBackGroundLine(HDC hdc) {

	OldBackGroundPen = (HPEN)SelectObject(hdc, BackGroundPen1);
	
	//�� �׸���
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

	//GameInterface�� ���� ��ü�� ����

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
	//�޸� ����
	DeleteObject(BackGroundPen1);
	DeleteObject(InterfaceFont1);
	for (int i = 0; i < 4; i++)
		DeleteObject(BackGroundBit[i]);

}
