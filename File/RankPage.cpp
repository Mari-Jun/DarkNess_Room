#include "Resource.hpp"
#include "RankPage.hpp"
#include "Interface.hpp"


RankPage::RankPage(int M, int R) : MainClick(M), Rank{ R,R,R,R,R,R,R,R,R,R } {

}

const int RankPage::GetMainClick() const {
	//MainClick�� ��ȯ�Ѵ�.
	return MainClick;
}

const bool RankPage::MainRange(const int y, const int x) const {
	//Main��ư�� ���� �ȿ� �ִ��� Ȯ��
	if (y < 730 || y > 790 || x < 1000 || x > 1250)
		return false;
	return true;
}

void RankPage::ChangeMainClick(const int Num) {
	//MainClick ��ư�� Num���� �ٲ��ش�.
	//(Num : 0 �̼���, 1 ����, 2 ���� �÷�����)
	MainClick = Num;
}

void RankPage::MainClickCheck(const int y, const int x) {
	//���� Main��ư�� ������ ��쿡 NextClick�� �ٲ��ش�.
	if (MainRange(y, x))
		ChangeMainClick(1);
}

const int RankPage::ChangeRankPage(const int y, const int x) {
	//Ŭ�� �� ���¶�� LBUTTON_UP�� �� MainClick�� �ٲ��ش�.
	//���� LBUTTON_UP�� �� Range�� Main��ư�� ������ ������ ��ȯ
	if (MainClick == 1) {
		//MainClick�� 1�ϰ�� 0���� �ٲ��ش�.
		ChangeMainClick(0);
		//Range������ ����ؼ� LBUTTON_UP�� �Ǵ� �������� �� ���� �ȿ� �ִٸ� 0�� ��ȯ���ش�.
		if (MainRange(y, x)) {
			//������ ������ LoadingPage�� 0 ��ȯ
			return 0;
		}
	}
	//�ƴ϶�� RankPage ��ȯ
	return 5;
}

void RankPage::MouseUpCheck(const int y, const int x) {
	if (MainClick != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (MainRange(y, x)) {
			//���� �ȿ� ���콺�� ������ StartClick�� 2�� �ٲ��ش�.
			ChangeMainClick(2);
		}
		else {
			//���� �ۿ� ������ StartClick�� 0���� �ٲ��ش�.
			ChangeMainClick(0);
		}
	}
}

void RankPage::PaintRankPage(HDC hdc) {
	//RankFont1�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, RankFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 330, 50, _T("Ranking Score"), 13);

	//RankFont2�� ����ؼ� ���� �ۼ��Ѵ�.
	SelectObject(hdc, RankFont2);
	if (MainClick == 2)
		//���콺 �÷����ִ� ���¶��
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (MainClick == 0)
		//�ƹ����µ� �ƴ϶��
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		//Ŭ�� ���¶��
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
		//*Rank�� NULL�϶��� �۵�
		*Rank = new RankPage(0, 0);
	}
	RankFont1 = CreateFontW(180, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	RankFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	RankFont3 = CreateFontW(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

	File = CreateFile( _T("C:\\Users\\Rank.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
}

void DeleteRankPage(RankPage** Rank){
	if (*Rank != NULL) {
		//*Rank�� NULL�� �ƴҶ� �۵�
		delete* Rank;
		*Rank = NULL;
	}
	DeleteObject(RankFont1);
	DeleteObject(RankFont2);
	DeleteObject(RankFont3);
	CloseHandle(File);
}