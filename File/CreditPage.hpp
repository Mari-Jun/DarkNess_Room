#pragma once
#include <windows.h>

//CreditPage에서 사용되는 것들

static HFONT CreditPageFont1;
static HFONT CreditPageFont2;
static HFONT CreditPageFont3;

class CreditPage {
public:
	explicit CreditPage(int B);

	const int GetBackClick() const;											//BackClick값을 얻는다.

	const bool BackRange(const int y, const int x) const;					//클릭 범위 확인 함수

	void ChangeBackClick(const int Num);									//BackClick 변경

	void BackClickCheck(const int y, const int x);							//LBUTTON_DOWN일 때 호출하는 MainRange()를 체크하는 함수
	const int ChangeCreditPage(const int y, const int x);						//LBUTTON_UP일 때 호출하는 Page를 바꿔주는 함수
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE일 때 호출하는 버튼 위에 있는지를 확인하는 함수

	void PaintCreditPage(HDC hdc);

private:
	int BackClick;
};

void CreateCreditPage(CreditPage** Credit);
void DeleteCreditPage(CreditPage** Credit);

