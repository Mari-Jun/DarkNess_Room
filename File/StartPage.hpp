#pragma once
#include <windows.h>

//MainPage���� ���Ǵ� �͵�HelpPage
static HFONT MainPageFont1;
static HFONT MainPageFont2;

//MainPage ��ư Ŭ����
class MainPage	{							//��ư Ŭ����
public:
	explicit MainPage(int S, int H, int Q);

	inline const int GetStartClick() const;
	inline const int GetHelpClick() const;
	inline const int GetQuitClick() const;

	const bool StartRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	const bool HelpRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	const bool QuitRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�

	void ChangeStartButton(const int Num);									//StartClick ����
	void ChangeHelpButton(const int Num);									//HelpClick ����
	void ChangeQuitButton(const int Num);									//QuitClick ����

	void PaintMainPage(HDC hdc);											//MainPage�� �׷��ش�.
	void MainClickCheck(const int y, const int x);							//LBUTTON_DOWN�� �� ȣ���Ѵ�.
	const int ChangeMainPage(const int y, const int x);						//LBUTTON_UP�� �� ȣ�� �Ǵ� �Լ�.
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�

private:
	int StartClick;
	int HelpClick;
	int QuitClick;
};

void CreateMainPage(MainPage** Click);									//MainPage�� ����� ���� ��ü�� ����
void DeleteMainPage(MainPage** Click);									//MainPage�� ���� ������� ��ü ����

