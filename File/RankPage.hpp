#pragma once
#include <windows.h>

class Interface;

static HFONT RankFont1;
static HFONT RankFont2;
static HFONT RankFont3;

class RankPage {
public:
	explicit RankPage(int M, TCHAR N, int R);

	const int GetMainClick() const;											//MainClick���� ��´�.

	const bool MainRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�

	void ChangeMainClick(const int Num);									//MainClick ����

	void MainClickCheck(const int y, const int x);							//LBUTTON_DOWN�� �� ȣ���ϴ� MainRange()�� üũ�ϴ� �Լ�
	const int ChangeRankPage(const int y, const int x);						//LBUTTON_UP�� �� ȣ���ϴ� Page�� �ٲ��ִ� �Լ�
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�

	void ChangeName(const int Num, const wchar_t N[]) ;						//�̸� ����
	void SetName(const int Num, WPARAM wParam);								//Name�� wParam���� Set�Ѵ�.

	void ChangeRank(const int Num, const int Score);						//Rank�� ����
	int CreateRank(Interface* Inter);										//Interface���� Rank���� �����Ѵ�.  (���� �����.)

	void PaintRankPage(HDC hdc);

private:
	int MainClick;
	TCHAR Name[10][11];
	int Rank[10];
};

void CreateRankPage(RankPage** Rank);
void DeleteRankPage(RankPage** Rank);
void RankSet(RankPage* Rank);