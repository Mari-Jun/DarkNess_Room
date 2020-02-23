#pragma once
#include <windows.h>

//StartPage에서 사용되는 것들
static HFONT StartPageFont1;
static HFONT StartPageFont2;

//StartPage 버튼 클래스
class ClickButton {							//버튼 클래스
public:
	ClickButton(int S, int H, int Q);
	inline const int GetStartClick() const;
	inline const int GetHelpClick() const;
	inline const int GetQuitClick() const;
	const bool StartRange(const int y, const int x) const;					//클릭 범위 확인 함수
	const bool HelpRange(const int y, const int x) const;					//클릭 범위 확인 함수
	const bool QuitRange(const int y, const int x) const;					//클릭 범위 확인 함수
	void ChangeStartButton(int Num);										//StartClick 변경
	void ChangeHelpButton(int Num);											//HelpClick 변경
	void ChangeQuitButton(int Num);											//QuitClick 변경

private:
	int StartClick;
	int HelpClick;
	int QuitClick;
};

void CreateStartPage(ClickButton** Click);									//StartPage를 만들기 위한 객체들 생성
void DeleteStartPage(ClickButton** Click);									//StartPage를 위해 만들어진 객체 삭제
void PaintStartPage(HDC hdc, const ClickButton* Click);						//StartPage를 그려준다.
void StartClickCheck(ClickButton* Click, const int y, const int x);			//LBUTTON_DOWN일 때 호출한다.
const int ChangeStartPage(ClickButton* Click, const int y, const int x);	//LBUTTON_UP일 떄 호출 되는 함수.
void MouseUpCheck(ClickButton* Click, const int y, const int x);				//MOUSEMOVE일 때 호출하는 버튼 위에 있는지를 확인하는 함수
