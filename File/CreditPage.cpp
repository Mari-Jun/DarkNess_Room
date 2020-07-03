#include "Resource.hpp"
#include "CreditPage.hpp"

//CreditPage ����

CreditPage::CreditPage(int B) : BackClick(B) {

}

const int CreditPage::GetBackClick() const{
	//BackClick���� ��ȯ�Ѵ�.
	return BackClick;
}

const bool CreditPage::BackRange(const int y, const int x) const {
	//Back��ư�� ���� �ȿ� �ִ��� Ȯ��
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

void CreditPage::ChangeBackClick(const int Num) {
	//BackClick ��ư�� Num���� �ٲ��ش�.
	//(Num : 0 �̼���, 1 ����, 2 ���� �÷�����)
	BackClick = Num;
}

void CreditPage::BackClickCheck(const int y, const int x) {
	//���� Main��ư�� ������ ��쿡 NextClick�� �ٲ��ش�.
	if (BackRange(y, x))
		ChangeBackClick(1);
}

const int CreditPage::ChangeCreditPage(const int y, const int x) {
	//Ŭ�� �� ���¶�� LBUTTON_UP�� �� BackClick�� �ٲ��ش�.
	//���� LBUTTON_UP�� �� Range�� Back��ư�� ������ ������ ��ȯ
	if (BackClick == 1) {
		//BackClick�� 1�ϰ�� 0���� �ٲ��ش�.
		ChangeBackClick(0);
		//Range������ ����ؼ� LBUTTON_UP�� �Ǵ� �������� �� ���� �ȿ� �ִٸ� 0�� ��ȯ���ش�.
		if (BackRange(y, x)) {
			//������ ������ HelpPage�� 2 ��ȯ
			return 2;
		}
	}
	//�ƴ϶�� CreditPage ��ȯ
	return 6;
}

void CreditPage::PaintCreditPage(HDC hdc) {
	//CreditPageFont1�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, CreditPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 150, 50, _T("Thanks For The Data"), 19);

	//CreditPageFont2�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, CreditPageFont2);
	if (BackClick == 2)
		//���콺 �÷����ִ� ���¶��
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (BackClick == 0)
		//�ƹ����µ� �ƴ϶��
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		//Ŭ�� ���¶��
		SetTextColor(hdc, RGB(255, 50, 50));

	TextOut(hdc, 1000, 710, _T("Back"), 4);

	//CreditPageFont3�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, CreditPageFont3);
	SetTextColor(hdc, RGB(222, 100, 30));

	TextOut(hdc, 50, 250, _T("Help Page Health Image : Icon made by Smashicons from www.flaticon.com"), 70);
	TextOut(hdc, 50, 313, _T("Skill Q Image : Icon made by Freepik from www.flaticon.com"), 58);
	TextOut(hdc, 50, 376, _T("SKill W Image : Icon made by Flat Icons from www.flaticon.com"), 61);
	TextOut(hdc, 50, 439, _T("SKill E Image : Icon made by Freepik from www.flaticon.com"), 58);
	TextOut(hdc, 50, 500, _T("Lightning Sound : soundbible.com/2015-Thunder-Strike-1.html/ Mike Koenig"), 72);
	TextOut(hdc, 200, 600, _T("Thank you to the producers for providing the materials "), 54);
	TextOut(hdc, 190, 650, _T("except those listed above with a Public Domain 0 license."), 57);
}

void CreditPage::MouseUpCheck(const int y, const int x) {
	if (BackClick != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (BackRange(y, x)) {
			//���� �ȿ� ���콺�� ������ StartClick�� 2�� �ٲ��ش�.
			ChangeBackClick(2);
		}
		else {
			//���� �ۿ� ������ StartClick�� 0���� �ٲ��ش�.
			ChangeBackClick(0);
		}
	}
}

void CreateCreditPage(CreditPage** Credit) {
	if (*Credit == NULL) {
		//*Credit�� NULL�̶��
		*Credit = new CreditPage(0);
	}

	CreditPageFont1 = CreateFontW(180, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	CreditPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	CreditPageFont3 = CreateFontW(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
}

void DeleteCreditPage(CreditPage** Credit) {
	if (*Credit != NULL) {
		//*Credit�� NULL�� �ƴ϶��
		delete* Credit;
		*Credit = NULL;
	}

	DeleteObject(CreditPageFont1);
	DeleteObject(CreditPageFont2);
	DeleteObject(CreditPageFont3);
}