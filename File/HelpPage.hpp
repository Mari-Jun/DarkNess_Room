#pragma once
#include <windows.h>

//HelpPage���� ���Ǵ� �͵�
static HFONT HelpPageFont1;
static HFONT HelpPageFont2;
static HFONT HelpPageFont3;

static HBITMAP ItemBit1, ItemBit2, ItemBit3;
static HBITMAP HealtBit;
static HBITMAP EBit[4];


//HelpPage ��ư Ŭ����

class HelpPage {
public:
	explicit HelpPage(int P, int N, int C);		

	inline const int GetPage() const;										//Page�� ���� ��´�.
	inline const int GetNextClick() const;									//NextClick�� ���� ��´�.
	inline const int GetCreditClick() const;								//Credit�� ���� ��´�.

	const bool NextRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	const bool CreditRange(const int y, const int x) const;					//Credit ���� Ȯ�� �Լ�

	void ChangePage(const int Num);											//Page ����
	void ChangeNextButton(const int Num);									//NextClick ����
	void ChangeCreditButton(const int Num);									//CreditClick ����

	void PaintHelpPage(HDC hdc, HDC Bithdc) const;								//HelpPage�� �׷��ش�.
	void HelpClickCheck(const int y, const int x);							//LBUTTON_DOWN�� �� ȣ���ϴ� BackRange()�� üũ�ϴ� �Լ�
	const int ChangeHelpPage(const int y, const int x);						//LBUTTON_UP�� �� ȣ���ϴ� Page�� �ٲ��ִ� �Լ�
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�

private:
	int Page;																//Help������
	int NextClick;															//0 : �̼���, 1 : ����, 2 : �̼���/���� �÷�����
	int CreditClick;
};

void CreateHelpPage(HelpPage** Help, HINSTANCE hInst);						//HelpPage�� ����� ���� ��ü�� ����
void DeleteHelpPage(HelpPage** Help);										//HelpPage�� ���� ������� ��ü�� ����

