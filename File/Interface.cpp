#include "Resource.hpp"
#include "Interface.hpp"

Interface::Interface(int L, int P) : Level(L), Percent(P) {

}

const int Interface::GetLevel() const {
	//Level�� ��ȯ�Ѵ�.
	return Level;
}

const int Interface::GetPercent() const {
	//Percent�� ��ȯ�Ѵ�.
	return Percent;
}

void Interface::ChangeLevel() {

}

void Interface::ChangePercent() {

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
	//SelectObject(Bithdc, BackGroundBit3);
	//BitBlt(hdc, LEFTWALL, TOPWALL, RIGHTWALL - LEFTWALL, BOTTOMWALL - TOPWALL, Bithdc, 0, 0, SRCCOPY);

	//�߰� �� �׸���
	SelectObject(Bithdc, BackGroundBit[1]);
	BitBlt(hdc, LLEFTWALL, LTOPWALL, 240, 240, Bithdc, 0, 0, SRCCOPY);


	//�÷��̾� �������̽� �׸���
	SelectObject(Bithdc, BackGroundBit[3]);
	BitBlt(hdc, PLEFTWALL, PTOPWALL, PRIGHTWALL - PLEFTWALL, PBOTTOMWALL - PTOPWALL, Bithdc, 0, 0, SRCCOPY);


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

void CreateInterface(Interface** inter) {
	if (*inter == NULL) {
		*inter = new Interface(1, 0);

		//GameInterface�� ���� Brush�� Pen ����

		BackGroundPen1 = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));

		for (int i = 0; i < 4; i++) {
			wchar_t str[100];
			swprintf_s(str, L".\\BitMap\\Interface%d.bmp", i + 1);
			BackGroundBit[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}
	}
	

}

void DeleteInterface(Interface** inter) {
	if (*inter != NULL) {
		delete* inter;
		*inter = NULL;
		//�޸� ����
		DeleteObject(BackGroundPen1);
		for (int i = 0; i < 4; i++)
			DeleteObject(BackGroundBit[i]);
	}
}
