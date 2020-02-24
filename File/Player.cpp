#include "Resource.hpp"
#include "Player.hpp"

Player::Player(int X, int Y, int H, int Q, int W, int E) : XPos(X), YPos(Y), Health(H), SkillQ(Q), SkillW(W), SkillE(E) {

}

//플레이어 관련

const int Player::GetXPos() const {
	//플레이어의 X좌표값 반환
	return XPos;
}

const int Player::GetYPos() const {
	//플레이어의 Y좌표값 반환
	return YPos;
}

void Player::MoveBasic() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		MoveLeft();
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		MoveRight();
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		MoveTop();
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		MoveBottom();
}

const bool Player::MoveRangeCheck() const {
	//플레이어 이동 범위 체크 함수

	//테두리 벽
	if (XPos < LEFTWALL + 10 || XPos > RIGHTWALL - 10 || YPos < TOPWALL + 10 || YPos > BOTTOMWALL - 10)
		return false;

	//중간 섬
	if (XPos > LLEFTWALL - 10 && XPos < LRIGHTWALL + 10 && YPos > LTOPWALL - 10 && YPos < LBOTTOMWALL + 10)
		return false;
	
	return true;
}

void Player::MoveLeft() {
	//플레이어를 왼쪽으로 이동시킨다.
	XPos -= 10;
	if(!MoveRangeCheck())
		XPos += 10;
}

void Player::MoveRight() {
	//플레이어를 오른쪽으로 이동시킨다.
	XPos += 10;
	if (!MoveRangeCheck())
		XPos -= 10;
}

void Player::MoveTop() {
	//플레이어를 위쪽으로 이동시킨다.
	YPos -= 10;
	if (!MoveRangeCheck())
		YPos += 10;
}

void Player::MoveBottom() {
	//플레이어를 아래쪽으로 이동시킨다.
	YPos += 10;
	if (!MoveRangeCheck())
		YPos -= 10;
}

void Player::SetPoint(POINT* Pos, double Num) const{
	double Rad1 = Num * (PI / 180);
	double Rad2 = (Num + 45.00) * (PI / 180);
	double Rad3 = (Num + 135.00) * (PI / 180);
	double Rad4 = (Num + 180.00) * (PI / 180);
	double Rad5 = (Num + 270.00) * (PI / 180);

	Pos[0] = { (LONG)(-10 * cos(Rad1)),(LONG)(10 * sin(Rad1)) };
	Pos[1] = { (LONG)((-10 * sqrt(2) - 0.5) * cos(Rad2)),(LONG)((10 * sqrt(2) + 0.5) * sin(Rad2)) };
	Pos[2] = { (LONG)((-10 * sqrt(2) - 0.5) * cos(Rad3)),(LONG)((10 * sqrt(2) + 0.5) * sin(Rad3)) };
	Pos[3] = { (LONG)(-10 * cos(Rad4)),(LONG)(10 * sin(Rad4)) };
	Pos[4] = { (LONG)(-10 * cos(Rad5)),(LONG)(10 * sin(Rad5)) };

	for (int i = 0; i < 5; i++) {
		Pos[i].x += XPos;
		Pos[i].y += YPos;
	}
}

void Player::PaintPlayer(HDC hdc) const {
	bool KeyUp = (GetAsyncKeyState(VK_UP) & 0x8000);
	bool KeyDown = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	bool KeyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	bool KeyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000);

	POINT Pos[5];

	static double Rad = 0.0;	

	//1은 0도부터 시작 2는 45도부터 시작 3은 45도부터 시작 4는 0도부터 시작 5는 90도부터 시작

	if (KeyUp && KeyLeft) {
		//위쪽+오른쪽
		this->SetPoint(Pos, 45.0);
		Rad = 45.0;
	}
	else if (KeyUp && KeyRight) {
		//위쪽+오른쪽
		this->SetPoint(Pos, 315.0);
		Rad = 315.0;
	}
	else if (KeyDown && KeyLeft) {
		//아래쪽+왼쪽
		this->SetPoint(Pos, 135.0);
		Rad = 135.0;
	}
	else if (KeyDown && KeyRight) {
		//아래쪽+오른쪽
		this->SetPoint(Pos, 225.0);
		Rad = 225.0;
	}
	else if (KeyUp && !KeyDown) {
		//위쪽
		this->SetPoint(Pos, 0.0);
		Rad = 0.0;
	}
	else if (KeyDown && !KeyUp) {
		//아래쪽
		this->SetPoint(Pos, 180.0);
		Rad = 180.0;
	}
	else if (KeyLeft && !KeyRight) {
		//왼쪽
		this->SetPoint(Pos, 90.0);
		Rad = 90.0;
	}
	else if (KeyRight && !KeyLeft) {
		//오른쪽
		this->SetPoint(Pos, 270.0);
		Rad = 270.0;
	}
	else {
		this->SetPoint(Pos, Rad);
	}

	Polygon(hdc, Pos, 5);
	
	//XPoint += float(-Speed * cos(M_PI / 180 * 45)), YPoint += float(Speed * sin(M_PI / 180 * 45)), Roll = -1;
}





//인터페이스 관련

const int Player::GetHealth() const {
	//Health값을 반환한다.
	return Health;
}

const int Player::GetSkillQ() const {
	//SkillQ값을 반환한다.
	return SkillQ;
}

const int Player::GetSkillW() const {
	//SkillW값을 반환한다.
	return SkillW;
}

const int Player::GetSkillE() const {
	//SkillE값을 반환한다.
	return SkillE;
}

void Player::PaintPlayerIF(HDC hdc) const {

	//기본 텍스트들 출력
	SelectObject(hdc, PlayerIFFont1);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 45, PTOPWALL + 5, _T("HP"), 2);
	TextOut(hdc, 520, PTOPWALL + 5, _T("Q"), 1);
	TextOut(hdc, 630, PTOPWALL + 5, _T("W"), 1);
	TextOut(hdc, 740, PTOPWALL + 5, _T("E"), 1);


	//여기부터는 따로 인터페이스 클래스 만들어서 관리한다. 일단은 임시로 여기다가 출력해놓는거임
	TextOut(hdc, 860, PTOPWALL + 5, _T("LEVEL"), 5);
	//Level 출력
	TextOut(hdc, 960, PTOPWALL + 5, _T("10"), 2);
	TextOut(hdc, 1020, PTOPWALL + 5, _T("TIME"), 4);
	TextOut(hdc, 1110, PTOPWALL + 5, _T("00:00:00"), 8);

	//기본 비트맵 틀
	SelectObject(hdc, PlayerIFBrush1);
	Rectangle(hdc, 90, PTOPWALL + 5, 490, PBOTTOMWALL - 5);
	Rectangle(hdc, 550, PTOPWALL + 5, 600, PBOTTOMWALL - 5);
	Rectangle(hdc, 660, PTOPWALL + 5, 710, PBOTTOMWALL - 5);
	Rectangle(hdc, 770, PTOPWALL + 5, 820, PBOTTOMWALL - 5);

	SelectObject(hdc, PlayerIFFont2);
	SetTextColor(hdc, RGB(200, 200, 200));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 240, PTOPWALL + 15, _T("100 / 100"), 9);
	TextOut(hdc, 560, PTOPWALL + 15, _T("20"), 2);
	TextOut(hdc, 670, PTOPWALL + 15, _T("40"), 2);
	TextOut(hdc, 780, PTOPWALL + 15, _T("60"), 2);
}



void CreatePlayer(Player** player) {
	if (*player == NULL) {
		//*player가 NULL일 경우 생성한다.
		*player = new Player(640, 450, 100, 0, 0, 0);

		PlayerIFBrush1 = CreateSolidBrush(RGB(0, 0, 0));

		PlayerIFFont1 = CreateFontW(50, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
		PlayerIFFont2 = CreateFontW(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	}

}
void DeletePlayer(Player** player) {
	if (*player != NULL) {
		//*player가 NULL이 아닐경우 제거한다.
		delete* player;
		*player = NULL;
		DeleteObject(PlayerIFBrush1);
		DeleteObject(PlayerIFFont1);
		DeleteObject(PlayerIFFont2);
	}
}