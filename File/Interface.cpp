#include "Resource.hpp"
#include "Interface.hpp"

void CreateInterface() {
	//GameInterface�� ���� Brush�� Pen ����

	BackGroundPen1 = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));

	BackGroundBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	BackGroundBit2 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	BackGroundBit3 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	BackGroundBit4 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface4.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void DeleteInterface() {
	//�޸� ����
	DeleteObject(BackGroundPen1);
	DeleteObject(BackGroundBit1);
	DeleteObject(BackGroundBit2);
	DeleteObject(BackGroundBit3);
	DeleteObject(BackGroundBit4);
}

void PaintBackGround(HDC hdc, HDC Bithdc) {

	//�� �׵θ� �׸��� (��ü��)
	SelectObject(Bithdc, BackGroundBit1);
	BitBlt(hdc, 0, 0, ALLMAPX, ALLMAPY, Bithdc, 0, 0, SRCCOPY);

	//��(ī�޶��) �׸���
	SelectObject(Bithdc, BackGroundBit2);
	BitBlt(hdc, CLEFTWALL, CTOPWALL, CRIGHTWALL - CLEFTWALL, CBOTTOMWALL - CTOPWALL, Bithdc, 0, 0, SRCCOPY);


	//�÷��� �� �׸���
	SelectObject(Bithdc, BackGroundBit3);
	BitBlt(hdc, LEFTWALL, TOPWALL, RIGHTWALL - LEFTWALL, BOTTOMWALL - TOPWALL, Bithdc, 0, 0, SRCCOPY);


	//�߰� �� �׸���
	SelectObject(Bithdc, BackGroundBit2);
	BitBlt(hdc, LLEFTWALL, LTOPWALL, 240, 240, Bithdc, 0, 0, SRCCOPY);
	
	
	//�÷��̾� �������̽� �׸���
	SelectObject(Bithdc, BackGroundBit4);
	BitBlt(hdc, PLEFTWALL, PTOPWALL, PRIGHTWALL - PLEFTWALL, PBOTTOMWALL - PTOPWALL, Bithdc, 0, 0, SRCCOPY);


	SelectObject(hdc, BackGroundPen1);

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