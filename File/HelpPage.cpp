#include "Resource.hpp"
#include "HelpPage.hpp"

HelpPage::HelpPage(int P, int N, int C) : Page(P), NextClick(N), CreditClick(C) {
	//생성자
}

const int HelpPage::GetPage() const {
	//Page값을 반환한다.
	return Page;
}

const int HelpPage::GetNextClick() const {
	//NextClick을 반환한다.
	return NextClick;
}

const int HelpPage::GetCreditClick() const {
	//CreditClick을 반환한다.
	return CreditClick;
}

const bool HelpPage::NextRange(const int y, const int x) const {
	//Next버튼의 범위 안에 있는지 확인
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

const bool HelpPage::CreditRange(const int y, const int x) const {
	//Credit버튼의 범위 안에 있는지 확인
	if (y < 730 || y > 790 || x < 30 || x > 350)
		return false;
	return true;
}

void HelpPage::ChangePage(const int Num) {
	//Page를 Num값으로 변경한다.
	Page = Num;
}

void HelpPage::ChangeNextButton(const int Num) {
	//NextClick 버튼을 Num으로 바꿔준다.
	//(Num : 0 미선택, 1 선택, 2 위에 올려놓음)
	NextClick = Num;
}

void HelpPage::ChangeCreditButton(const int Num) {
	//CreditClick 버튼을 Num으로 바꿔준다.
	CreditClick = Num;
}

void HelpPage::PaintHelpPage(HDC hdc, HDC Bithdc) const {

	//HelpPageFont1를 사용해서 글을 작성한다.
	SelectObject(hdc, HelpPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 470, 50, _T("Help"), 4);

	//HelpPageFont2를 사용해서 글을 작성한다.
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

	//Credit 클릭 버튼을 작성한다.
	if (CreditClick == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (CreditClick == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 30, 710, _T("CREDIT"), 6);


	//HelpPageFont3를 사용해서 글을 작성한다.
	SelectObject(hdc, HelpPageFont3);
	SetTextColor(hdc, RGB(222, 100, 30));
	//Help 관련 글을 작성한다.

	if (Page == 0) {
		TextOut(hdc, 450, 300, _T("Move : ← , ↑ , → , ↓"), 21);
		TextOut(hdc, 450, 380, _T("Health :"), 8);
		TextOut(hdc, 710, 380, _T("X 100"), 5);
		TextOut(hdc, 260, 460, _T("Skill1 : Q"), 10);
		TextOut(hdc, 600, 460, _T("[Healing Your HP20]"), 19);
		TextOut(hdc, 260, 540, _T("Skill2 : W"), 10);
		TextOut(hdc, 600, 540, _T("[Delay The Time]"), 16);
		TextOut(hdc, 260, 620, _T("Skill3 : E"), 10);
		TextOut(hdc, 600, 620, _T("[No Damage]"), 11);

		//비트맵 이미지 작성

		//Item1 비트맵 작성
		SelectObject(Bithdc, ItemBit1);
		TransparentBlt(hdc, 525, 460, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
		//Item2 비트맵 작성
		SelectObject(Bithdc, ItemBit2);
		TransparentBlt(hdc, 520, 540, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
		//Item3 비트맵 작성
		SelectObject(Bithdc, ItemBit3);
		TransparentBlt(hdc, 520, 620, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
		//HP 비트맵 작성
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

		//비트맵 이미지 작성

		//Enemy1 비트맵 작성
		SelectObject(Bithdc, EBit[0]);
		TransparentBlt(hdc, 420, 290, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		//Enemy2 비트맵 작성
		SelectObject(Bithdc, EBit[1]);
		TransparentBlt(hdc, 420, 400, 60, 60, Bithdc, 0, 0, 60, 60, RGB(0, 0, 0));
		//Enemy3 비트맵 작성
		SelectObject(Bithdc, EBit[2]);
		TransparentBlt(hdc, 420, 510, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		//Enemy4 비트맵 작성
		SelectObject(Bithdc, EBit[3]);
		TransparentBlt(hdc, 420, 620, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
	}
}

void  HelpPage::HelpClickCheck(const int y, const int x) {
	//만약 Next버튼을 눌렀을 경우에 NextClick을 바꿔준다.
	if (NextRange(y, x))
		ChangeNextButton(1);
	//Credit버튼을 눌렀을 경우에 Credit버튼을 1로 바꿔준다.
	if (CreditRange(y, x))
		ChangeCreditButton(1);
}

const int HelpPage::ChangeHelpPage(const int y, const int x) {
	//클릭 된 상태라면 LBUTTON_UP일 때 NextClick을 바꿔준다.
	//만약 LBUTTON_UP일 때 Range가 Next버튼에 있으면 페이지 반환
	if (GetNextClick() == 1) {
		ChangeNextButton(0);
		if (NextRange(y, x)) {
			if (Page == 1) {
				//다시 StartPage로 돌아간다.
				return 1;
			}
			else {
				//다음 Help페이지로 넘긴다.
				ChangePage(Page + 1);
			}
		}
	}

	if (GetCreditClick() == 1) {
		ChangeCreditButton(0);
		if (CreditRange(y, x))
			//Credit페이지로 넘어간다.
			return 5;
	}

	//Help페이지 그대로 있는다.
	return 2;
}

void HelpPage::MouseUpCheck(const int y, const int x) {
	if (GetNextClick() != 1) {
		//클릭 된 상태라면 실행하지 않는다.
		if (NextRange(y, x)) {
			//범위 안에 마우스가 있으면 NextClick을 2로 바꿔준다.
			ChangeNextButton(2);
		}
		else {
			//범위 밖에 있으면 NextClick을 0으로 바꿔준다.
			ChangeNextButton(0);
		}
	}

	if (GetCreditClick() != 1) {
		if (CreditRange(y, x) && GetCreditClick() != 1) {
			//범위 안에 마우스가 있으면 CreditClick을 2로 바꿔준다.
			ChangeCreditButton(2);
		}
		else {
			//범위 밖에 있으면 CreditClick을 0으로 바꿔준다.
			ChangeCreditButton(0);
		}
	}
}

void CreateHelpPage(HelpPage** Help) {

	//HelpPage에 사용될 폰트들을 생성해준다.
	HelpPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	HelpPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	HelpPageFont3 = CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

	//HelpPage에 사용될 비트맵 이미지들을 생성한다.
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
		//Help 생성
		*Help = new HelpPage(0, 0, 0);
	}
}

void DeleteHelpPage(HelpPage** Help) {
	if (*Help != NULL) {
		//Help가 NULL이 아닐 경우에만 작동한다.
		delete* Help;
		*Help = NULL;

		//사용된 객체들을 삭제시킨다.
		DeleteObject(HelpPageFont1);
		DeleteObject(HelpPageFont2);
		DeleteObject(HelpPageFont3);
	}
}

