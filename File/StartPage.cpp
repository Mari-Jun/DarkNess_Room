#include "Resource.hpp"
#include "StartPage.hpp"

ClickButton::ClickButton(int S, int H, int Q) : StartClick(S), HelpClick(H), QuitClick(Q)
{	//������

}

const int ClickButton::GetStartClick() const {
	//StartClick ��ȯ
	return StartClick;
}

const int ClickButton::GetHelpClick() const {
	//HelpClick ��ȯ
	return HelpClick;
}

const int ClickButton::GetQuitClick() const {
	//QuitClick ��ȯ
	return QuitClick;
}

const bool ClickButton::StartRange(const int y, const int x) const {
	//Start��ư�� ������ ����ִ��� Ȯ��
	if (y < 370 || y > 430 || x < 490 || x > 780)
		return false;
	return true;
}

const bool ClickButton::HelpRange(const int y, const int x) const {
	//Help��ư�� ������ ����ִ��� Ȯ��
	if (y < 520 || y > 580 || x < 525 || x > 750)
		return false;
	return true;
}

const bool ClickButton::QuitRange(const int y, const int x) const {
	//Quit��ư�� ������ ����ִ��� Ȯ��
	if (y < 670 || y > 730 || x < 525 || x > 730)
		return false;
	return true;
}

void ClickButton::ChangeStartButton(int Num) {
	//StartClick ��ư�� true�� false, flase�� true�� �ٲ��ش�.
	StartClick = Num;
}

void ClickButton::ChangeHelpButton(int Num) {
	//HelpClick ��ư�� true�� false, flase�� true�� �ٲ��ش�.
	HelpClick = Num;
}

void ClickButton::ChangeQuitButton(int Num) {
	//QuitClick ��ư�� true�� false, flase�� true�� �ٲ��ش�.
	QuitClick = Num;
}

void CreateStartPage(ClickButton** Click) {
	if (*Click == NULL) {
		//Click ����
		*Click = new ClickButton(0, 0, 0);
		//StartPage���� ���� ��Ʈ�� ����
		StartPageFont1 = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));
		StartPageFont2 = CreateFontW(100, 50, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	}
}

void DeleteStartPage(ClickButton** Click) {
	//�޸� ����
	if (*Click != NULL) {
		//Click�� ������� �ʴٸ� �۵��Ѵ�.
		delete* Click;
		*Click = NULL;
		//����� ��Ʈ�� ����
		DeleteObject(StartPageFont1);
		DeleteObject(StartPageFont2);
	}
}


void PaintStartPage(HDC hdc, const ClickButton* Click) {
	
	//StartPageFont1�� �� �ۼ�
	SelectObject(hdc, StartPageFont1);
	SetTextColor(hdc, RGB(122, 0, 0));
	TextOut(hdc, 140, 100, _T("Darkness Room"), 13);
	
	//StartPageFont2�� �� �ۼ�
	SelectObject(hdc, StartPageFont2);
	//3�� ���� Button�� Ŭ���Ǿ��ִ� ���¶�� ���� �ٸ��� ǥ�����ش�.
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
	//���� Start��ư�� ������ ��쿡 StartClick�� �ٲ��ش�.
	if (Click->StartRange(y, x))
		Click->ChangeStartButton(1);
	//���� Help��ư�� ������ ��쿡 HelpClick�� �ٲ��ش�.
	if (Click->HelpRange(y, x))
		Click->ChangeHelpButton(1);
	//���� Quit��ư�� ������ ��쿡 QuitClick�� �ٲ��ش�.
	if (Click->QuitRange(y, x))
		Click->ChangeQuitButton(1);
}

const int ChangeStartPage(ClickButton* Click, const int y, const int x) {
	//���� Start �Ǵ� Help �Ǵ� Quit�� TRUE�� ���¿��� LBUTTON_UP�� ��� Ŭ�� ������ ������ StartPage�� �ٸ� ������(int������ ��ȯ)�� �ٲ��ش�..

	if (Click->GetStartClick() == 1) {
		//StartClick�� 1�� ��� 0���� �ٲ��ش�.
		Click->ChangeStartButton(0);
		//�׸��� Range�� ���� ���� return���� ��ȯ�Ѵ�.
		if(Click->StartRange(y,x))
			return 3;
	}

	if (Click->GetHelpClick() == 1) {
		//HelpClick�� 1�� ��� 0���� �ٲ��ش�.
		Click->ChangeHelpButton(0);
		//Range������ ����ؼ� LBUTTON_UP�� �Ǵ� �������� �� ���� �ȿ� �ִٸ� 2�� ��ȯ���ش�.
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
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (Click->StartRange(y, x)) {
			//���� �ȿ� ���콺�� ������ StartClick�� 2�� �ٲ��ش�.
			Click->ChangeStartButton(2);
		}
		else {
			//���� �ۿ� ������ StartClick�� 0���� �ٲ��ش�.
			Click->ChangeStartButton(0);
		}
	}
	
	if (Click->GetHelpClick() != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (Click->HelpRange(y, x)) {
			//���� �ȿ� ���콺�� ������ HelpClick�� 2�� �ٲ��ش�.
			Click->ChangeHelpButton(2);
		}
		else {
			//���� �ۿ� ������ HelpClick�� 0���� �ٲ��ش�.
			Click->ChangeHelpButton(0);
		}
	}

	if (Click->GetQuitClick() != 1) {
		//Ŭ�� ���°� �ƴϸ� �۵��Ѵ�.
		if (Click->QuitRange(y, x)) {
			//���� �ȿ� ���콺�� ������ QuitClick�� 2�� �ٲ��ش�.
			Click->ChangeQuitButton(2);
		}
		else {
			//���� �ۿ� ������ QuitClick�� 0���� �ٲ��ش�.
			Click->ChangeQuitButton(0);
		}
	}
}
