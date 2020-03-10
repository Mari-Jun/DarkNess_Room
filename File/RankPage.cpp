#include "Resource.hpp"
#include "RankPage.hpp"
#include "Interface.hpp"


RankPage::RankPage(int M, int R) : MainClick(M), Rank{ R,R,R,R,R,R,R,R,R,R } {

}

const int RankPage::GetMainClick() const {
	//MainClick을 반환한다.
	return MainClick;
}

const bool RankPage::MainRange(const int y, const int x) const {
	//Main버튼의 범위 안에 있는지 확인
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

void RankPage::ChangeMainClick(const int Num) {
	//MainClick 버튼을 Num으로 바꿔준다.
	//(Num : 0 미선택, 1 선택, 2 위에 올려놓음)
	MainClick = Num;
}

void RankPage::MainClickCheck(const int y, const int x) {
	//만약 Main버튼을 눌렀을 경우에 NextClick을 바꿔준다.
	if (MainRange(y, x))
		ChangeMainClick(1);
}

const int RankPage::ChangeRankPage(const int y, const int x) {
	//클릭 된 상태라면 LBUTTON_UP일 때 MainClick을 바꿔준다.
	//만약 LBUTTON_UP일 때 Range가 Main버튼에 있으면 페이지 반환
	if (MainClick == 1) {
		//MainClick이 1일경우 0으로 바꿔준다.
		ChangeMainClick(0);
		//Range범위를 계산해서 LBUTTON_UP이 되는 순간에도 그 범위 안에 있다면 0을 반환해준다.
		if (MainRange(y, x)) {
			//범위에 있을시 LoadingPage인 0 반환
			return 0;
		}
	}
	//아니라면 RankPage 반환
	return 5;
}

void RankPage::MouseUpCheck(const int y, const int x) {
	if (MainClick != 1) {
		//클릭 상태가 아니면 작동한다.
		if (MainRange(y, x)) {
			//범위 안에 마우스가 있으면 StartClick을 2로 바꿔준다.
			ChangeMainClick(2);
		}
		else {
			//범위 밖에 있으면 StartClick을 0으로 바꿔준다.
			ChangeMainClick(0);
		}
	}
}

void RankPage::PaintRankPage(HDC hdc) {
	//RankFont1를 사용해서 글을 작성한다.
	SelectObject(hdc, RankFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 330, 50, _T("Ranking Score"), 13);

	//RankFont2를 사용해서 글을 작성한다.
	SelectObject(hdc, RankFont2);
	if (MainClick == 2)
		//마우스 올려져있는 상태라면
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (MainClick == 0)
		//아무상태도 아니라면
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		//클릭 상태라면
		SetTextColor(hdc, RGB(255, 50, 50));
	
	TextOut(hdc, 1000, 710, _T("Main"), 4);


	SelectObject(hdc, RankFont3);
	SetTextColor(hdc, RGB(255, 255, 255));

	TextOut(hdc, 300, 250, _T("RANK"), 4);
	TextOut(hdc, 600, 250, _T("LEVEL"), 5);
	TextOut(hdc, 900, 250, _T("Score"), 5);

	for (int i = 0; i < 10; i++) {
		wchar_t str[3];
		swprintf_s(str, L"%d%d", (i + 1) / 10, (i + 1) % 10);
		TextOut(hdc, 300, 300 + 40 * i, str, 2);
	}

	for (int i = 0; i < 10; i++) {
		//wchar_t str[3];
		TextOut(hdc, 600, 300 + 40 * i, _T("01"), 2);
	}

	for (int i = 0; i < 10; i++) {
		//wchar_t str[10];
		TextOut(hdc, 870, 300 + 40 * i, _T("1234567"), 7);
	}
		
}

void RankPage::CreateRank(Interface* inter) {

}


void CreateRankPage(RankPage** Rank) {
	if (*Rank == NULL) {
		//*Rank가 NULL일때만 작동
		*Rank = new RankPage(0, 0);
	}
	RankFont1 = CreateFontW(180, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	RankFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	RankFont3 = CreateFontW(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

	File = CreateFile( _T("C:\\Users\\Rank.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
}

void DeleteRankPage(RankPage** Rank){
	if (*Rank != NULL) {
		//*Rank가 NULL이 아닐때 작동
		delete* Rank;
		*Rank = NULL;
	}
	DeleteObject(RankFont1);
	DeleteObject(RankFont2);
	DeleteObject(RankFont3);
	CloseHandle(File);
}