#include "Resourec.h"
#include "HelpPage.h"

HelpButton::HelpButton(int B, int C) : BackClick(B), CreditClick(C) {
	//������
}

const int HelpButton::GetBackClick() const {
	//BackClick�� ��ȯ�Ѵ�.
	return BackClick;
}

const int HelpButton::GetCreditClick() const {
	//CreditClick�� ��ȯ�Ѵ�.
	return CreditClick;
}

const bool HelpButton::BackRange(const int y, const int x) const {
	//Back��ư�� ���� �ȿ� �ִ��� Ȯ��
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

const bool HelpButton::CreditRange(const int y, const int x) const {
	//Credit��ư�� ���� �ȿ� �ִ��� Ȯ��
	if (y < 730 || y > 790 || x < 30 || x > 350)
		return false;
	return true;
}

void HelpButton::ChangeBackButton(const int Num) {
	//BackClick ��ư�� Num���� �ٲ��ش�.
	//(Num : 0 �̼���, 1 ����, 2 ���� �÷�����)
	BackClick = Num;
}

void HelpButton::ChangeCreditButton(const int Num) {
	//CreditClick ��ư�� Num���� �ٲ��ش�.
	CreditClick = Num;
}

void CreateHelpPage(HelpButton** Help) {
	if (*Help == NULL) {
		//Help ����
		*Help = new HelpButton(0, 0);

		//HelpPage�� ���� ��Ʈ���� �������ش�.
		HelpPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
		HelpPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
		HelpPageFont3 = CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

		//HelpPage�� ���� ��Ʈ�� �̹������� �����Ѵ�.
		ItemBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		ItemBit2 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		ItemBit3 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		HealtBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Health1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	}
}

void DeleteHelpPage(HelpButton** Help) {
	if (*Help != NULL) {
		//Help�� NULL�� �ƴ� ��쿡�� �۵��Ѵ�.
		delete* Help;
		*Help = NULL;

		//���� ��ü���� ������Ų��.
		DeleteObject(HelpPageFont1);
		DeleteObject(HelpPageFont2);
		DeleteObject(HelpPageFont3);
	}
}

void PaintHelpPage(HDC hdc, HDC Bithdc, const HelpButton* Help) {

	//HelpPageFont1�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, HelpPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 470, 50, _T("Help"), 4);

	//HelpPageFont2�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, HelpPageFont2);
	if (Help->GetBackClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Help->GetBackClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 1000, 710, _T("BACK"), 4);

	//Credit Ŭ�� ��ư�� �ۼ��Ѵ�.
	if (Help->GetCreditClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Help->GetCreditClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 30, 710, _T("CREDIT"), 6);



	//HelpPageFont3�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, HelpPageFont3);
	SetTextColor(hdc, RGB(222, 100, 30));
	//Help ���� ���� �ۼ��Ѵ�.
	TextOut(hdc, 450, 300, _T("Move : �� , �� , �� , ��"), 21);
	TextOut(hdc, 470, 380, _T("Health :"), 8);
	TextOut(hdc, 730, 380, _T("X 5"), 3);
	TextOut(hdc, 270, 460, _T("Item1 : Q"), 9);
	TextOut(hdc, 600, 460, _T("[Healing Your HP1]"), 18);
	TextOut(hdc, 270, 540, _T("Item2 : W"), 9);
	TextOut(hdc, 600, 540, _T("[One Way Defense]"), 17);
	TextOut(hdc, 270, 620, _T("Item3 : E"), 9);
	TextOut(hdc, 600, 620, _T("[No Damage]"), 11);


	//��Ʈ�� �̹��� �ۼ�

	//Item1 ��Ʈ�� �ۼ�
	OldItemBit = (HBITMAP)SelectObject(Bithdc, ItemBit1);
	TransparentBlt(hdc, 525, 460, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//Item2 ��Ʈ�� �ۼ�
	SelectObject(Bithdc, ItemBit2);
	TransparentBlt(hdc, 520, 540, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//Item3 ��Ʈ�� �ۼ�
	SelectObject(Bithdc, ItemBit3);
	TransparentBlt(hdc, 520, 620, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//HP ��Ʈ�� �ۼ�
	SelectObject(Bithdc, HealtBit);
	TransparentBlt(hdc, 650, 380, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));

	SelectObject(Bithdc, OldItemBit);


}

void  HelpClickCheck(HelpButton* Help, const int y, const int x) {
	//���� Back��ư�� ������ ��쿡 BackClick�� �ٲ��ش�.
	if (Help->BackRange(y, x))
		Help->ChangeBackButton(1);
	//Credit��ư�� ������ ��쿡 Credit��ư�� 1�� �ٲ��ش�.
	if (Help->CreditRange(y, x))
		Help->ChangeCreditButton(1);
}

const int ChangeHelpPage(HelpButton* Help, const int y, const int x) {
	//Ŭ�� �� ���¶�� LBUTTON_UP�� �� BackClick�� �ٲ��ش�.
	//���� LBUTTON_UP�� �� Range�� Back��ư�� ������ ������ ��ȯ
	if (Help->GetBackClick() == 1) {
		Help->ChangeBackButton(0);
		if (Help->BackRange(y, x))
			//�ٽ� StartPage�� ���ư���.
			return 1;
	}

	if (Help->GetCreditClick() == 1) {
		Help->ChangeCreditButton(0);
		if (Help->CreditRange(y, x))
			//Credit�������� �Ѿ��.
			return 5;
	}

	//Help������ �״�� �ִ´�.
	return 2;
}

void MouseUpCheck(HelpButton* Help, const int y, const int x) {
	if (Help->GetBackClick() != 1) {
		//Ŭ�� �� ���¶�� �������� �ʴ´�.
		if (Help->BackRange(y, x)) {
			//���� �ȿ� ���콺�� ������ BackClick�� 2�� �ٲ��ش�.
			Help->ChangeBackButton(2);
		}
		else {
			//���� �ۿ� ������ BackClick�� 0���� �ٲ��ش�.
			Help->ChangeBackButton(0);
		}
	}

	if (Help->GetCreditClick() != 1) {
		if (Help->CreditRange(y, x) && Help->GetCreditClick() != 1) {
			//���� �ȿ� ���콺�� ������ CreditClick�� 2�� �ٲ��ش�.
			Help->ChangeCreditButton(2);
		}
		else {
			//���� �ۿ� ������ CreditClick�� 0���� �ٲ��ش�.
			Help->ChangeCreditButton(0);
		}
	}
}