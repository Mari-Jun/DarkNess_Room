#pragma once
#include <windows.h>

//HelpPage에서 사용되는 것들
static HFONT HelpPageFont1;
static HFONT HelpPageFont2;
static HFONT HelpPageFont3;

static HBITMAP ItemBit1, ItemBit2, ItemBit3, OldItemBit;
static HBITMAP HealtBit;


//HelpPage 버튼 클래스

class HelpButton {
public:
	HelpButton(int B, int C);		

	inline const int GetBackClick() const;									//BackClick의 값을 얻는다.
	inline const int GetCreditClick() const;								//Credit의 값을 얻는다.

	const bool BackRange(const int y, const int x) const;					//클릭 범위 확인 함수
	const bool CreditRange(const int y, const int x) const;					//Credit 범위 확인 함수

	void ChangeBackButton(const int Num);									//BackClick 변경
	void ChangeCreditButton(const int Num);									//CreditClick 변경

private:
	int BackClick;															//0 : 미선택, 1 : 선택, 2 : 미선택/위에 올려놓음
	int CreditClick;
};

void CreateHelpPage(HelpButton** Help);										//HelpPage를 만들기 위한 객체들 생성
void DeleteHelpPage(HelpButton** Help);										//HelpPage를 위해 만들어진 객체들 삭제
void PaintHelpPage(HDC hdc, HDC Bithdc, const HelpButton* Help);			//HelpPage를 그려준다.
void HelpClickCheck(HelpButton* Help, const int y, const int x);			//LBUTTON_DOWN일 때 호출하는 BackRange()를 체크하는 함수
const int ChangeHelpPage(HelpButton* Help, const int y, const int x);		//LBUTTON_UP일 때 호출하는 Page를 바꿔주는 함수
void MouseUpCheck(HelpButton* Help, const int y, const int x);				//MOUSEMOVE일 때 호출하는 버튼 위에 있는지를 확인하는 함수