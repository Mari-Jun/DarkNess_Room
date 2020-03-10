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

	void MainClickCheck(const int y, const int x);							//LBUTTON_DOWN�� �� ȣ���ϴ� MainRange()�� üũ�ϴ� �Լ�
	const int ChangeRankPage(const int y, const int x);						//LBUTTON_UP�� �� ȣ���ϴ� Page�� �ٲ��ִ� �Լ�
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�

	void PaintRankPage(HDC hdc);

	void CreateRank(Interface* Inter);

private:
	int MainClick;
	int Rank[10];
};

void CreateRankPage(RankPage** Rank);
void DeleteRankPage(RankPage** Rank);