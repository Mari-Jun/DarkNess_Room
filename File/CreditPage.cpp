#include "Resource.hpp"
#include "CreditPage.hpp"

//CreditPage 정의

CreditPage::CreditPage(int B) : BackClick(B) {

}

const int CreditPage::GetBackClick() const{
	//BackClick값을 반환한다.
	return BackClick;
}

const bool CreditPage::BackRange(const int y, const int x) const {
	//Back버튼의 범위 안에 있는지 확인
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

void CreditPage::ChangeBackClick(const int Num) {
	//BackClick 버튼을 Num으로 바꿔준다.
	//(Num : 0 미선택, 1 선택, 2 위에 올려놓음)
	BackClick = Num;
}

void CreditPage::BackClickCheck(const int y, const int x) {
	//만약 Main버튼을 눌렀을 경우에 NextClick을 바꿔준다.
	if (BackRange(y, x))
		ChangeBackClick(1);
}

const int CreditPage::ChangeCreditPage(const int y, const int x) {
	//클릭 된 상태라면 LBUTTON_UP일 때 BackClick을 바꿔준다.
	//만약 LBUTTON_UP일 때 Range가 Back버튼에 있으면 페이지 반환
	if (BackClick == 1) {
		//BackClick이 1일경우 0으로 바꿔준다.
		ChangeBackClick(0);
		//Range범위를 계산해서 LBUTTON_UP이 되는 순간에도 그 범위 안에 있다면 0을 반환해준다.
		if (BackRange(y, x)) {
			//범위에 있을시 HelpPage인 2 반환
			return 2;
		}
	}
	//아니라면 CreditPage 반환
	return 6;
}

void CreditPage::PaintCreditPage(HDC hdc) {
	//CreditPageFont1를 사용해서 글을 작성한다.
	SelectObject(hdc, CreditPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 150, 50, _T("Thanks For The Data"), 19);

	//CreditPageFont2를 사용해서 글을 작성한다.
	SelectObject(hdc, CreditPageFont2);
	if (BackClick == 2)
		//마우스 올려져있는 상태라면
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (BackClick == 0)
		//아무상태도 아니라면
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		//클릭 상태라면
		SetTextColor(hdc, RGB(255, 50, 50));

	TextOut(hdc, 1000, 710, _T("Back"), 4);

	//CreditPageFont3를 사용해서 글을 작성한다.
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
		//클릭 상태가 아니면 작동한다.
		if (BackRange(y, x)) {
			//범위 안에 마우스가 있으면 StartClick을 2로 바꿔준다.
			ChangeBackClick(2);
		}
		else {
			//범위 밖에 있으면 StartClick을 0으로 바꿔준다.
			ChangeBackClick(0);
		}
	}
}

void CreateCreditPage(CreditPage** Credit) {
	if (*Credit == NULL) {
		//*Credit이 NULL이라면
		*Credit = new CreditPage(0);
	}

	CreditPageFont1 = CreateFontW(180, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	CreditPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	CreditPageFont3 = CreateFontW(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
}

void DeleteCreditPage(CreditPage** Credit) {
	if (*Credit != NULL) {
		//*Credit이 NULL이 아니라면
		delete* Credit;
		*Credit = NULL;
	}

	DeleteObject(CreditPageFont1);
	DeleteObject(CreditPageFont2);
	DeleteObject(CreditPageFont3);
}