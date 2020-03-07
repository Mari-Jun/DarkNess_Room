#include "Resource.hpp"
#include "StartPage.hpp"

MainPage::MainPage(int S, int H, int Q) : StartClick(S), HelpClick(H), QuitClick(Q)
{	//������

}

const int MainPage::GetStartClick() const {
	//StartClick ��ȯ
	return StartClick;
}

const int MainPage::GetHelpClick() const {
	//HelpClick ��ȯ
	return HelpClick;
}

const int MainPage::GetQuitClick() const {
	//QuitClick ��ȯ
	return QuitClick;
}

const bool MainPage::StartRange(const int y, const int x) const {
	//Main��ư�� ������ ����ִ��� Ȯ��
	if (y < 370 || y > 430 || x < 490 || x > 780)
		return false;
	return true;
}

const bool MainPage::HelpRange(const int y, const int x) const {
	//Help��ư�� ������ ����ִ��� Ȯ��
	if (y < 520 || y > 580 || x < 525 || x > 750)
		return false;
	return true;
}

const bool MainPage::QuitRange(const int y, const int x) const {
	//Quit��ư�� ������ ����ִ��� Ȯ��
	if (y < 670 || y > 730 || x < 525 || x > 730)
		return false;
	return true;
}

void MainPage::ChangeStartButton(const int Num) {
	//StartClick ��ư�� true�� false, flase�� true�� �ٲ��ش�.
	StartClick = Num;
}

void MainPage::ChangeHelpButton(const int Num) {
	//HelpClick ��ư�� true�� false, flase�� true�� �ٲ��ش�.
	HelpClick = Num;
}

void MainPage::ChangeQuitButton(const int Num) {
	//QuitClick ��ư�� true�� false, flase�� true�� �ٲ��ش�.
	QuitClick = Num;
}

void MainPage::PaintMainPage(HDC hdc) {
	
	//MainPageFont1�� �� �ۼ�
	SelectObject(hdc, MainPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 140, 100, _T("Darkness Room"), 13);
	
	//MainPageFont2�� �� �ۼ�
	SelectObject(hdc, MainPageFont2);
	//3�� ���� Button�� Ŭ���Ǿ��ִ� ���¶�� ���� �ٸ��� ǥ�����ش�.
	if (StartClick == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (StartClick == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 490, 350, _T("Start"), 5);

	if (HelpClick == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (HelpClick == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 525, 500, _T("Help"), 4);

	if (QuitClick == 2)
		SetTextColor(hdc, RGB(152, 50, 50));
	else if (QuitClick == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(255, 50, 50));
	TextOut(hdc, 525, 650, _T("Quit"), 4);
}

void MainPage::MainClickCheck(const int y, const int x) {
	//���� Main��ư�� ������ ��쿡 StartClick�� �ٲ��ش�.
	if (StartRange(y, x))
		ChangeStartButton(1);
	//���� Help��ư�� ������ ��쿡 HelpClick�� �ٲ��ش�.
	if (HelpRange(y, x))
		ChangeHelpButton(1);
	//���� Quit��ư�� ������ ��쿡 QuitClick�� �ٲ��ش�.
	if (QuitRange(y, x))
		ChangeQuitButton(1);
}

const int MainPage::ChangeMainPage(const int y, const int x) {
	//���� Main �Ǵ� Help �Ǵ� Quit�� TRUE�� ���¿��� LBUTTON_UP�� ��� Ŭ�� ������ ������ MainPage�� �ٸ� ������(int������ ��ȯ)�� �ٲ��ش�..

	if (StartClick == 1) {
		//StartClick�� 1�� ��� 0���� �ٲ��ش�.
		ChangeStartButton(0);
		//�׸��� Range�� ���� ���� return���� ��ȯ�Ѵ�.
		if(StartRange(y,x))
			return 3;
	}

	if (HelpClick == 1) {
		//HelpClick�� 1�� ��� 0���� �ٲ��ش�.
		ChangeHelpButton(0);
		//Range������ ����ؼ� LBUTTON_UP�� �Ǵ� �������� �� ���� �ȿ� �ִٸ� 2�� ��ȯ���ش�.
		if(HelpRange(y, x))
			return 2;
	}

	if (QuitClick == 1) {
		ChangeQuitButton(0);
		if(QuitRange(y, x))
			return 4;
	}

	return 1;
}

void MainPage::MouseUpCheck(const int y, const int x) {
	if (StartClick != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (StartRange(y, x)) {
			//���� �ȿ� ���콺�� ������ StartClick�� 2�� �ٲ��ش�.
			ChangeStartButton(2);
		}
		else {
			//���� �ۿ� ������ StartClick�� 0���� �ٲ��ش�.
			ChangeStartButton(0);
		}
	}
	
	if (HelpClick != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (HelpRange(y, x)) {
			//���� �ȿ� ���콺�� ������ HelpClick�� 2�� �ٲ��ش�.
			ChangeHelpButton(2);
		}
		else {
			//���� �ۿ� ������ HelpClick�� 0���� �ٲ��ش�.
			ChangeHelpButton(0);
		}
	}

	if (QuitClick != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (QuitRange(y, x)) {
			//���� �ȿ� ���콺�� ������ QuitClick�� 2�� �ٲ��ش�.
			ChangeQuitButton(2);
		}
		else {
			//���� �ۿ� ������ QuitClick�� 0���� �ٲ��ش�.
			ChangeQuitButton(0);
		}
	}
}

void CreateMainPage(MainPage** Click) {
	if (*Click == NULL) {
		//Click ����
		*Click = new MainPage(0, 0, 0);
		//MainPage���� ���� ��Ʈ�� ����
		MainPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
		MainPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	}
}

void DeleteMainPage(MainPage** Click) {
	//�޸� ����
	if (*Click != NULL) {
		//Click�� ������� �ʴٸ� �۵��Ѵ�.
		delete* Click;
		*Click = NULL;
		//����� ��Ʈ�� ����
		DeleteObject(MainPageFont1);
		DeleteObject(MainPageFont2);
	}
}