#include "Resource.hpp"
#include "RankPage.hpp"
#include "Interface.hpp"


RankPage::RankPage(int M, TCHAR N, int R) : MainClick(M), Name{ N, }, Rank{ R, } {

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

void RankPage::ChangeName(const int Num, const wchar_t N[]) {
	//Name�� �����Ѵ�.
	_tcscpy_s(Name[Num], N);
}

void RankPage::SetName(const int Num, WPARAM wParam) {
	//Name�� �Է¹޽��ϴ�.

	int Len = static_cast<int>(_tcslen(Name[Num]));

	if (Len > 9)
		return;

	if (wParam == VK_BACK) {
		//BackSpace������ ���
		Name[Num][Len - 1] = NULL;
		Len--;
	}
	else {
		Name[Num][Len] = static_cast<TCHAR>(wParam);
		Name[Num][Len + 1] = NULL;
	}
}

void RankPage::ChangeRank(const int Num, const int Score) {
	//Rank�� �����Ѵ�.
	Rank[Num] = Score;
}

int RankPage::CreateRank(Interface* Inter) {
	int ret = Inter->GetLevel() * 10000000 + Inter->GetScore();

	for (int S = 9; S >= 0; S--) {
		//���� �Ʒ��������� �˻��Ѵ�.
		if (ret < Rank[S] && S < 9) {
			//���� ���ھ ����� ���ھ�� ���ٸ�
			for (int M = 9; M > S + 1; M--) {
				//���� �б�
				Rank[M] = Rank[M - 1];
				_tcscpy_s(Name[M], Name[M - 1]);
			}
			//���� ����
			Rank[S + 1] = ret;

			//Name �ʱ�ȭ
			_tcscpy_s(Name[S + 1], _T(""));

			//��ŷ ���� ��ȯ
			return S + 1;
		}
	}
	//��ŷ�� ���� ���Ѵٸ� 10�� ��ȯ
	return 10;
}

void RankPage::PaintRankPage(HDC hdc, int Ranking) {
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

	TextOut(hdc, 250, 250, _T("RANK"), 4);
	TextOut(hdc, 470, 250, _T("NAME"), 4);
	TextOut(hdc, 700, 250, _T("LEVEL"), 5);
	TextOut(hdc, 950, 250, _T("Score"), 5);

	for (int i = 0; i < 10; i++) {
		//Rank���
		wchar_t str1[3];
		swprintf_s(str1, L"%d%d", (i + 1) / 10, (i + 1) % 10);
		TextOut(hdc, 280, 300 + 40 * i, str1, 2);

		//Name���
		TextOut(hdc, 470, 300 + 40 * i, Name[i], static_cast<int>(_tcslen(Name[i])));
		if (Ranking == i) {
			//ĳ�� ���
			SIZE size;
			GetTextExtentPoint(hdc, Name[Ranking], static_cast<int>(_tcslen(Name[Ranking])), &size);
			SetCaretPos(470 + size.cx, 300 + 40 * Ranking);
		}

		//Level���
		wchar_t str2[3];
		swprintf_s(str2, L"%d%d", Rank[i] / 100000000, Rank[i] / 10000000 % 10);
		TextOut(hdc, 740, 300 + 40 * i, str2, 2);

		//Score���
		wchar_t str3[10];
		swprintf_s(str3, L"%d%d%d%d%d%d%d", Rank[i] / 1000000 % 10, Rank[i] / 100000 % 10, Rank[i] / 10000 % 10, Rank[i] / 1000 % 10, Rank[i] / 100 % 10, Rank[i] / 10 % 10, Rank[i] % 10);
		TextOut(hdc, 920, 300 + 40 * i, str3, 7);
	}
		
}


void CreateRankPage(RankPage** Rank) {
	if (*Rank == NULL) {
		//*Rank�� NULL�϶��� �۵�
		*Rank = new RankPage(0, NULL, 0);
		RankSet(*Rank);
	}
	RankFont1 = CreateFontW(180, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
	RankFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	RankFont3 = CreateFontW(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
}

void DeleteRankPage(RankPage** Rank){

	//RankPage�� �ѹ� ����Ǹ� ��� �־���Ѵ�. �׷��� Font�����͸� ��������
	/*if (*Rank != NULL) {
		//*Rank�� NULL�� �ƴҶ� �۵�
		delete* Rank;
		*Rank = NULL;
	}*/
	DeleteObject(RankFont1);
	DeleteObject(RankFont2);
	DeleteObject(RankFont3);
}

void RankSet(RankPage* Rank) {
	//ó�� RankPage�� �����Ǿ����� Rank���� �������ش�.
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
	Rank->ChangeName(1, L"������");
	Rank->ChangeName(2, L"Master");
	Rank->ChangeName(3, L"KPU");
	Rank->ChangeName(4, L"Takahashi");
	Rank->ChangeName(5, L"Hell");
	Rank->ChangeName(6, L"Game");
	Rank->ChangeName(7, L"Taki");
	Rank->ChangeName(8, L"�ʺ�");
	Rank->ChangeName(9, L"Beginner");
}