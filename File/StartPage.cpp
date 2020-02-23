#include "Resource.hpp"
#include "StartPage.hpp"

ClickButton::ClickButton(int S, int H, int Q) : StartClick(S), HelpClick(H), QuitClick(Q)
{	//생성자

}

const int ClickButton::GetStartClick() const {
	//StartClick 반환
	return StartClick;
}

const int ClickButton::GetHelpClick() const {
	//HelpClick 반환
	return HelpClick;
}

const int ClickButton::GetQuitClick() const {
	//QuitClick 반환
	return QuitClick;
}

const bool ClickButton::StartRange(const int y, const int x) const {
	//Start버튼의 범위에 들어있는지 확인
	if (y < 370 || y > 430 || x < 490 || x > 780)
		return false;
	return true;
}

const bool ClickButton::HelpRange(const int y, const int x) const {
	//Help버튼의 범위에 들어있는지 확인
	if (y < 520 || y > 580 || x < 525 || x > 750)
		return false;
	return true;
}

const bool ClickButton::QuitRange(const int y, const int x) const {
	//Quit버튼의 범위에 들어있는지 확인
	if (y < 670 || y > 730 || x < 525 || x > 730)
		return false;
	return true;
}

void ClickButton::ChangeStartButton(int Num) {
	//StartClick 버튼이 true면 false, flase면 true로 바꿔준다.
	StartClick = Num;
}

void ClickButton::ChangeHelpButton(int Num) {
	//HelpClick 버튼이 true면 false, flase면 true로 바꿔준다.
	HelpClick = Num;
}

void ClickButton::ChangeQuitButton(int Num) {
	//QuitClick 버튼이 true면 false, flase면 true로 바꿔준다.
	QuitClick = Num;
}

void CreateStartPage(ClickButton** Click) {
	if (*Click == NULL) {
		//Click 생성
		*Click = new ClickButton(0, 0, 0);
		//StartPage에서 사용될 폰트들 생성
		StartPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
		StartPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	}
}

void DeleteStartPage(ClickButton** Click) {
	//메모리 해제
	if (*Click != NULL) {
		//Click이 비어있지 않다면 작동한다.
		delete* Click;
		*Click = NULL;
		//사용한 폰트들 삭제
		DeleteObject(StartPageFont1);
		DeleteObject(StartPageFont2);
	}
}


void PaintStartPage(HDC hdc, const ClickButton* Click) {
	
	//StartPageFont1로 글 작성
	SelectObject(hdc, StartPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 140, 100, _T("Darkness Room"), 13);
	
	//StartPageFont2로 글 작성
	SelectObject(hdc, StartPageFont2);
	//3개 동일 Button이 클릭되어있는 상태라면 색을 다르게 표현해준다.
	if (Click->GetStartClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Click->GetStartClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 490, 350, _T("Start"), 5);

	if (Click->GetHelpClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Click->GetHelpClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 525, 500, _T("Help"), 4);

	if (Click->GetQuitClick() == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (Click->GetQuitClick() == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 525, 650, _T("Quit"), 4);
}

void StartClickCheck(ClickButton* Click, const int y, const int x) {
	//만약 Start버튼을 눌렀을 경우에 StartClick을 바꿔준다.
	if (Click->StartRange(y, x))
		Click->ChangeStartButton(1);
	//만약 Help버튼을 눌렀을 경우에 HelpClick을 바꿔준다.
	if (Click->HelpRange(y, x))
		Click->ChangeHelpButton(1);
	//만약 Quit버튼을 눌렀을 경우에 QuitClick을 바꿔준다.
	if (Click->QuitRange(y, x))
		Click->ChangeQuitButton(1);
}

const int ChangeStartPage(ClickButton* Click, const int y, const int x) {
	//만약 Start 또는 Help 또는 Quit가 TRUE인 상태에서 LBUTTON_UP일 경우 클릭 범위가 맞으면 StartPage를 다른 페이지(int형으로 반환)로 바꿔준다..

	if (Click->GetStartClick() == 1) {
		//StartClick이 1일 경우 0으로 바꿔준다.
		Click->ChangeStartButton(0);
		//그리고 Range도 같을 경우는 return값을 반환한다.
		if(Click->StartRange(y,x))
			return 3;
	}

	if (Click->GetHelpClick() == 1) {
		//HelpClick이 1일 경우 0으로 바꿔준다.
		Click->ChangeHelpButton(0);
		//Range범위를 계산해서 LBUTTON_UP이 되는 순간에도 그 범위 안에 있다면 2를 반환해준다.
		if(Click->HelpRange(y, x))
			return 2;
	}

	if (Click->GetQuitClick() == 1) {
		Click->ChangeQuitButton(0);
		if(Click->QuitRange(y, x))
			return 4;
	}

	return 1;
}

void MouseUpCheck(ClickButton* Click, const int y, const int x) {
	if (Click->GetStartClick() != 1) {
		//클릭 상태가 아니면 작동한다.
		if (Click->StartRange(y, x)) {
			//범위 안에 마우스가 있으면 StartClick을 2로 바꿔준다.
			Click->ChangeStartButton(2);
		}
		else {
			//범위 밖에 있으면 StartClick을 0으로 바꿔준다.
			Click->ChangeStartButton(0);
		}
	}
	
	if (Click->GetHelpClick() != 1) {
		//클릭 상태가 아니면 작동한다.
		if (Click->HelpRange(y, x)) {
			//범위 안에 마우스가 있으면 HelpClick을 2로 바꿔준다.
			Click->ChangeHelpButton(2);
		}
		else {
			//범위 밖에 있으면 HelpClick을 0으로 바꿔준다.
			Click->ChangeHelpButton(0);
		}
	}

	if (Click->GetQuitClick() != 1) {
		//클릭 상태가 아니면 작동한다.
		if (Click->QuitRange(y, x)) {
			//범위 안에 마우스가 있으면 QuitClick을 2로 바꿔준다.
			Click->ChangeQuitButton(2);
		}
		else {
			//범위 밖에 있으면 QuitClick을 0으로 바꿔준다.
			Click->ChangeQuitButton(0);
		}
	}
}
