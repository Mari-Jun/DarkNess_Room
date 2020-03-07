#include "Resource.hpp"
#include "HelpPage.hpp"

HelpPage::HelpPage(int P, int N, int C) : Page(P), NextClick(N), CreditClick(C) {
	//������
}

const int HelpPage::GetPage() const {
	//Page���� ��ȯ�Ѵ�.
	return Page;
}

const int HelpPage::GetNextClick() const {
	//NextClick�� ��ȯ�Ѵ�.
	return NextClick;
}

const int HelpPage::GetCreditClick() const {
	//CreditClick�� ��ȯ�Ѵ�.
	return CreditClick;
}

const bool HelpPage::NextRange(const int y, const int x) const {
	//Next��ư�� ���� �ȿ� �ִ��� Ȯ��
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

const bool HelpPage::CreditRange(const int y, const int x) const {
	//Credit��ư�� ���� �ȿ� �ִ��� Ȯ��
	if (y < 730 || y > 790 || x < 30 || x > 350)
		return false;
	return true;
}

void HelpPage::ChangePage(const int Num) {
	//Page�� Num������ �����Ѵ�.
	Page = Num;
}

void HelpPage::ChangeNextButton(const int Num) {
	//NextClick ��ư�� Num���� �ٲ��ش�.
	//(Num : 0 �̼���, 1 ����, 2 ���� �÷�����)
	NextClick = Num;
}

void HelpPage::ChangeCreditButton(const int Num) {
	//CreditClick ��ư�� Num���� �ٲ��ش�.
	CreditClick = Num;
}

void HelpPage::PaintHelpPage(HDC hdc, HDC Bithdc) const {

	//HelpPageFont1�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, HelpPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 470, 50, _T("Help"), 4);

	//HelpPageFont2�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, HelpPageFont2);
	if (NextClick == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (NextClick == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	if(Page == 0)
		TextOut(hdc, 1000, 710, _T("Next"), 4);
	else
		TextOut(hdc, 1000, 710, _T("Main"), 4);

	//Credit Ŭ�� ��ư�� �ۼ��Ѵ�.
	if (CreditClick == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (CreditClick == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 30, 710, _T("CREDIT"), 6);


	//HelpPageFont3�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, HelpPageFont3);
	SetTextColor(hdc, RGB(222, 100, 30));
	//Help ���� ���� �ۼ��Ѵ�.

	if (Page == 0) {
		TextOut(hdc, 450, 300, _T("Move : �� , �� , �� , ��"), 21);
		TextOut(hdc, 450, 380, _T("Health :"), 8);
		TextOut(hdc, 710, 380, _T("X 100"), 5);
		TextOut(hdc, 260, 460, _T("Skill1 : Q"), 10);
		TextOut(hdc, 600, 460, _T("[Healing Your HP20]"), 19);
		TextOut(hdc, 260, 540, _T("Skill2 : W"), 10);
		TextOut(hdc, 600, 540, _T("[Delay The Time]"), 16);
		TextOut(hdc, 260, 620, _T("Skill3 : E"), 10);
		TextOut(hdc, 600, 620, _T("[No Damage]"), 11);

		//��Ʈ�� �̹��� �ۼ�

		//Item1 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, ItemBit1);
		TransparentBlt(hdc, 525, 460, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
		//Item2 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, ItemBit2);
		TransparentBlt(hdc, 520, 540, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
		//Item3 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, ItemBit3);
		TransparentBlt(hdc, 520, 620, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
		//HP ��Ʈ�� �ۼ�
		SelectObject(Bithdc, HealtBit);
		TransparentBlt(hdc, 630, 380, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	}
	else if(Page==1) {
		TextOut(hdc, 200, 290, _T("Enemy1 : "), 9);
		TextOut(hdc, 500, 290, _T("Straight Gun [Range 1*5~20]"), 27);
		TextOut(hdc, 200, 400, _T("Enemy2 : "), 9);
		TextOut(hdc, 500, 400, _T("Broad Area Gun [Range 10*10]"), 28);
		TextOut(hdc, 200, 510, _T("Enemy3 : "), 9);
		TextOut(hdc, 500, 510, _T("Random Bomb [Range 5*5]"), 23);
		TextOut(hdc, 200, 620, _T("Enemy4 : "), 9);
		TextOut(hdc, 500, 620, _T("Guided Missile [Range 3*3]"), 26);

		//��Ʈ�� �̹��� �ۼ�

		//Enemy1 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, EBit[0]);
		TransparentBlt(hdc, 420, 290, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		//Enemy2 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, EBit[1]);
		TransparentBlt(hdc, 420, 400, 60, 60, Bithdc, 0, 0, 60, 60, RGB(0, 0, 0));
		//Enemy3 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, EBit[2]);
		TransparentBlt(hdc, 420, 510, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		//Enemy4 ��Ʈ�� �ۼ�
		SelectObject(Bithdc, EBit[3]);
		TransparentBlt(hdc, 420, 620, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
	}
}

void  HelpPage::HelpClickCheck(const int y, const int x) {
	//���� Next��ư�� ������ ��쿡 NextClick�� �ٲ��ش�.
	if (NextRange(y, x))
		ChangeNextButton(1);
	//Credit��ư�� ������ ��쿡 Credit��ư�� 1�� �ٲ��ش�.
	if (CreditRange(y, x))
		ChangeCreditButton(1);
}

const int HelpPage::ChangeHelpPage(const int y, const int x) {
	//Ŭ�� �� ���¶�� LBUTTON_UP�� �� NextClick�� �ٲ��ش�.
	//���� LBUTTON_UP�� �� Range�� Next��ư�� ������ ������ ��ȯ
	if (GetNextClick() == 1) {
		ChangeNextButton(0);
		if (NextRange(y, x)) {
			if (Page == 1) {
				//�ٽ� StartPage�� ���ư���.
				return 1;
			}
			else {
				//���� Help�������� �ѱ��.
				ChangePage(Page + 1);
			}
		}
	}

	if (GetCreditClick() == 1) {
		ChangeCreditButton(0);
		if (CreditRange(y, x))
			//Credit�������� �Ѿ��.
			return 5;
	}

	//Help������ �״�� �ִ´�.
	return 2;
}

void HelpPage::MouseUpCheck(const int y, const int x) {
	if (GetNextClick() != 1) {
		//Ŭ�� �� ���¶�� �������� �ʴ´�.
		if (NextRange(y, x)) {
			//���� �ȿ� ���콺�� ������ NextClick�� 2�� �ٲ��ش�.
			ChangeNextButton(2);
		}
		else {
			//���� �ۿ� ������ NextClick�� 0���� �ٲ��ش�.
			ChangeNextButton(0);
		}
	}

	if (GetCreditClick() != 1) {
		if (CreditRange(y, x) && GetCreditClick() != 1) {
			//���� �ȿ� ���콺�� ������ CreditClick�� 2�� �ٲ��ش�.
			ChangeCreditButton(2);
		}
		else {
			//���� �ۿ� ������ CreditClick�� 0���� �ٲ��ش�.
			ChangeCreditButton(0);
		}
	}
}

void CreateHelpPage(HelpPage** Help) {

	//HelpPage�� ���� ��Ʈ���� �������ش�.
	HelpPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	HelpPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	HelpPageFont3 = CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

	//HelpPage�� ���� ��Ʈ�� �̹������� �����Ѵ�.
	ItemBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\SkillQ.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ItemBit2 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\SkillW.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ItemBit3 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\SkillE.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HealtBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Health1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	for (int i = 0; i < 4; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\Enemy%d.bmp", i + 1);
		EBit[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	if (*Help == NULL) {
		//Help ����
		*Help = new HelpPage(0, 0, 0);
	}
}

void DeleteHelpPage(HelpPage** Help) {
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

