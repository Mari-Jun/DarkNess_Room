#include "Resourec.h"
#include "Interface.h"

void CreateInterface() {
	//GameInterface�� ���� Brush�� Pen ����
	BackGroundBrush1 = CreateSolidBrush(RGB(50, 50, 50));
	BackGroundBrush2 = CreateSolidBrush(RGB(153, 56, 0));
	BackGroundBrush3 = CreateSolidBrush(RGB(0, 0, 0));

	BackGroundPen1 = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));
	BackGroundPen2 = CreatePen(PS_SOLID, 1, RGB(153, 56, 0));
	BackGroundPen3 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}

void DeleteInterface() {
	//�޸� ����
	DeleteObject(BackGroundBrush1);
	DeleteObject(BackGroundBrush2);
	DeleteObject(BackGroundPen1);
	DeleteObject(BackGroundPen2);
}

void PaintBackGround(HDC hdc) {

	//�� �׵θ� �׸��� (��ü��)
	OldBackGroundBrush = (HBRUSH)SelectObject(hdc, BackGroundBrush1);
	SelectObject(hdc, BackGroundPen1);

	Rectangle(hdc, 0, 0, ALLMAPX, ALLMAPY);

	//��(ī�޶��) �׸���
	SelectObject(hdc, BackGroundBrush2);
	SelectObject(hdc, BackGroundPen2);

	Rectangle(hdc, CLEFTWALL, CTOPWALL, CRIGHTWALL, CBOTTOMWALL);

	//�÷��� �� �׸���
	SelectObject(hdc, BackGroundBrush3);
	SelectObject(hdc, BackGroundPen3);

	Rectangle(hdc, LEFTWALL, TOPWALL, RIGHTWALL, BOTTOMWALL);
	
	//�÷��̾� �������̽� �׸���

	Rectangle(hdc, PLEFTWALL, PTOPWALL, PRIGHTWALL, PBOTTOMWALL);

	SelectObject(hdc, OldBackGroundBrush);


	//�⺻���� �� �׸���
	//SelectObject(hdc, BackGroundBrush1);
	SelectObject(hdc, BackGroundPen1);
	/*
	//���� �簢�� �����
	Rectangle(hdc, 0, 0, 1280, 20);
	Rectangle(hdc, 0, 0, 50, 80);
	Rectangle(hdc, 1230, 0, 1280, 80);

	//ū �簢�� �����
	Rectangle(hdc, 0, UPWALL - 100, 1280, UPWALL);
	Rectangle(hdc, LEFTWALL - 100, 80, LEFTWALL, 820);
	Rectangle(hdc, 0, DOWNWALL, 1280, DOWNWALL + 100);
	Rectangle(hdc, RIGHTWALL, 80, RIGHTWALL + 100, 820);*/

	//�� �׸���
	for (int x = LEFTWALL + 60; x < RIGHTWALL; x += 60) {
		MoveToEx(hdc, x, TOPWALL, NULL);
		LineTo(hdc, x, BOTTOMWALL);		
	}
	for (int y = TOPWALL + 60; y < BOTTOMWALL; y += 60) {
		MoveToEx(hdc, LEFTWALL, y, NULL);
		LineTo(hdc, RIGHTWALL, y);
	}

}