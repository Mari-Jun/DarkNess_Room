#include "Resourec.h"
#include "HelpPage.h"

HelpButton::HelpButton(int B, int C) : BackClick(B), CreditClick(C) {
	//생성자
}

const int HelpButton::GetBackClick() const {
	//BackClick을 반환한다.
	return BackClick;
}

const int HelpButton::GetCreditClick() const {
	//CreditClick을 반환한다.
	return CreditClick;
}

const bool HelpButton::BackRange(const int y, const int x) const {
	//Back버튼의 범위 안에 있는지 확인
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

const bool HelpButton::CreditRange(const int y, const int x) const {
	//Credit버튼의 범위 안에 있는지 확인
	if (y < 730 || y > 790 || x < 30 || x > 350)
		return false;
	return true;
}

void HelpButton::ChangeBackButton(const int Num) {
	//BackClick 버튼을 Num으로 바꿔준다.
	//(Num : 0 미선택, 1 선택, 2 위에 올려놓음)
	BackClick = Num;
}

void HelpButton::ChangeCreditButton(const int Num) {
	//CreditClick 버튼을 Num으로 바꿔준다.
	CreditClick = Num;
}

void CreateHelpPage(HelpButton** Help) {
	if (*Help == NULL) {
		//Help 생성
		*Help = new HelpButton(0, 0);

		//HelpPage에 사용될 폰트들을 생성해준다.
		HelpPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
		HelpPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
		HelpPageFont3 = CreateFontW(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

		//HelpPage에 사용될 비트맵 이미지들을 생성한다.
		ItemBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		ItemBit2 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		ItemBit3 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		HealtBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Health1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	}
}

void DeleteHelpPage(HelpButton** Help) {
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

void PaintHelpPage(HDC hdc, HDC Bithdc, const HelpButton* Help) {

	//HelpPageFont1를 사용해서 글을 작성한다.
	SelectObject(hdc, HelpPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 470, 50, _T("Help"), 4);

	//HelpPageFont2를 사용해서 글을 작성한다.
	SelectObject(hdc, HelpPageFont2);
	if (Help->GetBackClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Help->GetBackClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 1000, 710, _T("BACK"), 4);

	//Credit 클릭 버튼을 작성한다.
	if (Help->GetCreditClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Help->GetCreditClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 30, 710, _T("CREDIT"), 6);



	//HelpPageFont3를 사용해서 글을 작성한다.
	SelectObject(hdc, HelpPageFont3);
	SetTextColor(hdc, RGB(222, 100, 30));
	//Help 관련 글을 작성한다.
	TextOut(hdc, 450, 300, _T("Move : ← , ↑ , → , ↓"), 21);
	TextOut(hdc, 470, 380, _T("Health :"), 8);
	TextOut(hdc, 730, 380, _T("X 5"), 3);
	TextOut(hdc, 270, 460, _T("Item1 : Q"), 9);
	TextOut(hdc, 600, 460, _T("[Healing Your HP1]"), 18);
	TextOut(hdc, 270, 540, _T("Item2 : W"), 9);
	TextOut(hdc, 600, 540, _T("[One Way Defense]"), 17);
	TextOut(hdc, 270, 620, _T("Item3 : E"), 9);
	TextOut(hdc, 600, 620, _T("[No Damage]"), 11);


	//비트맵 이미지 작성

	//Item1 비트맵 작성
	OldItemBit = (HBITMAP)SelectObject(Bithdc, ItemBit1);
	TransparentBlt(hdc, 525, 460, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//Item2 비트맵 작성
	SelectObject(Bithdc, ItemBit2);
	TransparentBlt(hdc, 520, 540, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//Item3 비트맵 작성
	SelectObject(Bithdc, ItemBit3);
	TransparentBlt(hdc, 520, 620, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//HP 비트맵 작성
	SelectObject(Bithdc, HealtBit);
	TransparentBlt(hdc, 650, 380, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));

	SelectObject(Bithdc, OldItemBit);


}

void  HelpClickCheck(HelpButton* Help, const int y, const int x) {
	//만약 Back버튼을 눌렀을 경우에 BackClick을 바꿔준다.
	if (Help->BackRange(y, x))
		Help->ChangeBackButton(1);
	//Credit버튼을 눌렀을 경우에 Credit버튼을 1로 바꿔준다.
	if (Help->CreditRange(y, x))
		Help->ChangeCreditButton(1);
}

const int ChangeHelpPage(HelpButton* Help, const int y, const int x) {
	//클릭 된 상태라면 LBUTTON_UP일 때 BackClick을 바꿔준다.
	//만약 LBUTTON_UP일 때 Range가 Back버튼에 있으면 페이지 반환
	if (Help->GetBackClick() == 1) {
		Help->ChangeBackButton(0);
		if (Help->BackRange(y, x))
			//다시 StartPage로 돌아간다.
			return 1;
	}

	if (Help->GetCreditClick() == 1) {
		Help->ChangeCreditButton(0);
		if (Help->CreditRange(y, x))
			//Credit페이지로 넘어간다.
			return 5;
	}

	//Help페이지 그대로 있는다.
	return 2;
}

void MouseUpCheck(HelpButton* Help, const int y, const int x) {
	if (Help->GetBackClick() != 1) {
		//클릭 된 상태라면 실행하지 않는다.
		if (Help->BackRange(y, x)) {
			//범위 안에 마우스가 있으면 BackClick을 2로 바꿔준다.
			Help->ChangeBackButton(2);
		}
		else {
			//범위 밖에 있으면 BackClick을 0으로 바꿔준다.
			Help->ChangeBackButton(0);
		}
	}

	if (Help->GetCreditClick() != 1) {
		if (Help->CreditRange(y, x) && Help->GetCreditClick() != 1) {
			//범위 안에 마우스가 있으면 CreditClick을 2로 바꿔준다.
			Help->ChangeCreditButton(2);
		}
		else {
			//범위 밖에 있으면 CreditClick을 0으로 바꿔준다.
			Help->ChangeCreditButton(0);
		}
	}
}