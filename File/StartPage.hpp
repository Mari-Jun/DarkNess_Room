#pragma once
#include <windows.h>

//StartPage���� ���Ǵ� �͵�
static HFONT StartPageFont1;
static HFONT StartPageFont2;

//StartPage ��ư Ŭ����
class ClickButton {							//��ư Ŭ����
public:
	ClickButton(int S, int H, int Q);
	inline const int GetStartClick() const;
	inline const int GetHelpClick() const;
	inline const int GetQuitClick() const;
	const bool StartRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	const bool HelpRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	const bool QuitRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	void ChangeStartButton(int Num);										//StartClick ����
	void ChangeHelpButton(int Num);											//HelpClick ����
	void ChangeQuitButton(int Num);											//QuitClick ����

private:
	int StartClick;
	int HelpClick;
	int QuitClick;
};

void CreateStartPage(ClickButton** Click);									//StartPage�� ����� ���� ��ü�� ����
void DeleteStartPage(ClickButton** Click);									//StartPage�� ���� ������� ��ü ����
void PaintStartPage(HDC hdc, const ClickButton* Click);						//StartPage�� �׷��ش�.
void StartClickCheck(ClickButton* Click, const int y, const int x);			//LBUTTON_DOWN�� �� ȣ���Ѵ�.
const int ChangeStartPage(ClickButton* Click, const int y, const int x);	//LBUTTON_UP�� �� ȣ�� �Ǵ� �Լ�.
void MouseUpCheck(ClickButton* Click, const int y, const int x);				//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�
