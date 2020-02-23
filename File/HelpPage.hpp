#pragma once
#include <windows.h>

//HelpPage���� ���Ǵ� �͵�
static HFONT HelpPageFont1;
static HFONT HelpPageFont2;
static HFONT HelpPageFont3;

static HBITMAP ItemBit1, ItemBit2, ItemBit3, OldItemBit;
static HBITMAP HealtBit;


//HelpPage ��ư Ŭ����

class HelpButton {
public:
	HelpButton(int B, int C);		

	inline const int GetBackClick() const;									//BackClick�� ���� ��´�.
	inline const int GetCreditClick() const;								//Credit�� ���� ��´�.

	const bool BackRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�
	const bool CreditRange(const int y, const int x) const;					//Credit ���� Ȯ�� �Լ�

	void ChangeBackButton(const int Num);									//BackClick ����
	void ChangeCreditButton(const int Num);									//CreditClick ����

private:
	int BackClick;															//0 : �̼���, 1 : ����, 2 : �̼���/���� �÷�����
	int CreditClick;
};

void CreateHelpPage(HelpButton** Help);										//HelpPage�� ����� ���� ��ü�� ����
void DeleteHelpPage(HelpButton** Help);										//HelpPage�� ���� ������� ��ü�� ����
void PaintHelpPage(HDC hdc, HDC Bithdc, const HelpButton* Help);			//HelpPage�� �׷��ش�.
void HelpClickCheck(HelpButton* Help, const int y, const int x);			//LBUTTON_DOWN�� �� ȣ���ϴ� BackRange()�� üũ�ϴ� �Լ�
const int ChangeHelpPage(HelpButton* Help, const int y, const int x);		//LBUTTON_UP�� �� ȣ���ϴ� Page�� �ٲ��ִ� �Լ�
void MouseUpCheck(HelpButton* Help, const int y, const int x);				//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�