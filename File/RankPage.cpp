#include "Resource.hpp"
#include "RankPage.hpp"
#include "Interface.hpp"


RankPage::RankPage(int M, TCHAR N, int R) : MainClick(M), Name{ N, }, Rank{ R, } {

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

void RankPage::ChangeName(const int Num, const wchar_t N[]) {
	//Name을 변경한다.
	_tcscpy_s(Name[Num], N);
}

void RankPage::SetName(const int Num, WPARAM wParam) {
	//Name을 입력받습니다.

	int Len = static_cast<int>(_tcslen(Name[Num]));

	if (Len > 9)
		return;

	if (wParam == VK_BACK) {
		//BackSpace눌렀을 경우
		Name[Num][Len - 1] = NULL;
		Len--;
	}
	else {
		Name[Num][Len] = static_cast<TCHAR>(wParam);
		Name[Num][Len + 1] = NULL;
	}
}

void RankPage::ChangeRank(const int Num, const int Score) {
	//Rank를 변경한다.
	Rank[Num] = Score;
}

int RankPage::CreateRank(Interface* Inter) {
	int ret = Inter->GetLevel() * 10000000 + Inter->GetScore();

	for (int S = 9; S >= 0; S--) {
		//제일 아래순위부터 검사한다.
		if (ret < Rank[S] && S < 9) {
			//현재 스코어가 저장된 스코어보다 적다면
			for (int M = 9; M > S + 1; M--) {
				//순위 밀기
				Rank[M] = Rank[M - 1];
				_tcscpy_s(Name[M], Name[M - 1]);
			}
			//순위 저장
			Rank[S + 1] = ret;

			//Name 초기화
			_tcscpy_s(Name[S + 1], _T(""));

			//랭킹 값을 반환
			return S + 1;
		}
	}
	//랭킹에 들지 못한다면 10을 반환
	return 10;
}

void RankPage::PaintRankPage(HDC hdc, int Ranking) {
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

	TextOut(hdc, 250, 250, _T("RANK"), 4);
	TextOut(hdc, 470, 250, _T("NAME"), 4);
	TextOut(hdc, 700, 250, _T("LEVEL"), 5);
	TextOut(hdc, 950, 250, _T("Score"), 5);

	for (int i = 0; i < 10; i++) {
		//Rank출력
		wchar_t str1[3];
		swprintf_s(str1, L"%d%d", (i + 1) / 10, (i + 1) % 10);
		TextOut(hdc, 280, 300 + 40 * i, str1, 2);

		//Name출력
		TextOut(hdc, 470, 300 + 40 * i, Name[i], static_cast<int>(_tcslen(Name[i])));
		if (Ranking == i) {
			//캐럿 출력
			SIZE size;
			GetTextExtentPoint(hdc, Name[Ranking], static_cast<int>(_tcslen(Name[Ranking])), &size);
			SetCaretPos(470 + size.cx, 300 + 40 * Ranking);
		}

		//Level출력
		wchar_t str2[3];
		swprintf_s(str2, L"%d%d", Rank[i] / 100000000, Rank[i] / 10000000 % 10);
		TextOut(hdc, 740, 300 + 40 * i, str2, 2);

		//Score출력
		wchar_t str3[10];
		swprintf_s(str3, L"%d%d%d%d%d%d%d", Rank[i] / 1000000 % 10, Rank[i] / 100000 % 10, Rank[i] / 10000 % 10, Rank[i] / 1000 % 10, Rank[i] / 100 % 10, Rank[i] / 10 % 10, Rank[i] % 10);
		TextOut(hdc, 920, 300 + 40 * i, str3, 7);
	}
		
}


void CreateRankPage(RankPage** Rank) {
	if (*Rank == NULL) {
		//*Rank가 NULL일때만 작동
		*Rank = new RankPage(0, NULL, 0);
		RankSet(*Rank);
	}
	RankFont1 = CreateFontW(180, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	RankFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	RankFont3 = CreateFontW(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
}

void DeleteRankPage(RankPage** Rank){

	//RankPage는 한번 실행되면 계속 있어야한다. 그래서 Font같은것만 삭제하자
	/*if (*Rank != NULL) {
		//*Rank가 NULL이 아닐때 작동
		delete* Rank;
		*Rank = NULL;
	}*/
	DeleteObject(RankFont1);
	DeleteObject(RankFont2);
	DeleteObject(RankFont3);
}

void RankSet(RankPage* Rank) {
	//처음 RankPage가 생성되었을때 Rank들을 세팅해준다.
	Rank->ChangeRank(0, 109999999);
	Rank->ChangeRank(1, 100456123);
	Rank->ChangeRank(2, 90264553);
	Rank->ChangeRank(3, 90213564);
	Rank->ChangeRank(4, 80200000);
	Rank->ChangeRank(5, 60195321);
	Rank->ChangeRank(6, 50153232);
	Rank->ChangeRank(7, 40098325);
	Rank->ChangeRank(8, 10001111);
	Rank->ChangeRank(9, 0);

	Rank->ChangeName(0, L"NekoMari");
	Rank->ChangeName(1, L"정복자");
	Rank->ChangeName(2, L"Master");
	Rank->ChangeName(3, L"KPU");
	Rank->ChangeName(4, L"Takahashi");
	Rank->ChangeName(5, L"Hell");
	Rank->ChangeName(6, L"Game");
	Rank->ChangeName(7, L"Taki");
	Rank->ChangeName(8, L"초보");
	Rank->ChangeName(9, L"Beginner");
}