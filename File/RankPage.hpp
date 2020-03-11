#pragma once
#include <windows.h>

class Interface;

static HFONT RankFont1;
static HFONT RankFont2;
static HFONT RankFont3;

class RankPage {
public:
	explicit RankPage(int M, TCHAR N, int R);

	const int GetMainClick() const;											//MainClick값을 얻는다.

	const bool MainRange(const int y, const int x) const;					//클릭 범위 확인 함수

	void ChangeMainClick(const int Num);									//MainClick 변경

	void MainClickCheck(const int y, const int x);							//LBUTTON_DOWN일 때 호출하는 MainRange()를 체크하는 함수
	const int ChangeRankPage(const int y, const int x);						//LBUTTON_UP일 때 호출하는 Page를 바꿔주는 함수
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE일 때 호출하는 버튼 위에 있는지를 확인하는 함수

	void ChangeName(const int Num, const wchar_t N[]) ;						//이름 변경
	void SetName(const int Num, WPARAM wParam);								//Name을 wParam으로 Set한다.

	void ChangeRank(const int Num, const int Score);						//Rank값 변경
	int CreateRank(Interface* Inter);										//Interface에서 Rank값을 변경한다.  (새로 만든다.)

	void PaintRankPage(HDC hdc);

private:
	int MainClick;
	TCHAR Name[10][11];
	int Rank[10];
};

void CreateRankPage(RankPage** Rank);
void DeleteRankPage(RankPage** Rank);
void RankSet(RankPage* Rank);