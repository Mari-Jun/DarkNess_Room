#pragma once
#include <windows.h>

//MainPage에서 사용되는 것들HelpPage
static HFONT MainPageFont1;
static HFONT MainPageFont2;

//MainPage 버튼 클래스
class MainPage	{							//버튼 클래스
public:
	explicit MainPage(int S, int H, int Q);

	inline const int GetStartClick() const;
	inline const int GetHelpClick() const;
	inline const int GetQuitClick() const;

	const bool StartRange(const int y, const int x) const;					//클릭 범위 확인 함수
	const bool HelpRange(const int y, const int x) const;					//클릭 범위 확인 함수
	const bool QuitRange(const int y, const int x) const;					//클릭 범위 확인 함수

	void ChangeStartButton(const int Num);									//StartClick 변경
	void ChangeHelpButton(const int Num);									//HelpClick 변경
	void ChangeQuitButton(const int Num);									//QuitClick 변경

	void PaintMainPage(HDC hdc);											//MainPage를 그려준다.
	void MainClickCheck(const int y, const int x);							//LBUTTON_DOWN일 때 호출한다.
	const int ChangeMainPage(const int y, const int x);						//LBUTTON_UP일 떄 호출 되는 함수.
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE일 때 호출하는 버튼 위에 있는지를 확인하는 함수

private:
	int StartClick;
	int HelpClick;
	int QuitClick;
};

void CreateMainPage(MainPage** Click);									//MainPage를 만들기 위한 객체들 생성
void DeleteMainPage(MainPage** Click);									//MainPage를 위해 만들어진 객체 삭제

