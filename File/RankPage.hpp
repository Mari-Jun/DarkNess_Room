#pragma once
#include <windows.h>

class Interface;

static HFONT RankFont1;
static HFONT RankFont2;
static HFONT RankFont3;

static HANDLE File;

class RankPage {
public:
	explicit RankPage(int M, int R);

	const int GetMainClick() const;

	const bool MainRange(const int y, const int x) const;

	void ChangeMainClick(const int Num);

	void MainClickCheck(const int y, const int x);							//LBUTTON_DOWN일 때 호출하는 MainRange()를 체크하는 함수
	const int ChangeRankPage(const int y, const int x);						//LBUTTON_UP일 때 호출하는 Page를 바꿔주는 함수
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE일 때 호출하는 버튼 위에 있는지를 확인하는 함수

	void PaintRankPage(HDC hdc);

	void CreateRank(Interface* Inter);

private:
	int MainClick;
	int Rank[10];
};

void CreateRankPage(RankPage** Rank);
void DeleteRankPage(RankPage** Rank);