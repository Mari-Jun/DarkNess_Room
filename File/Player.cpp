#include "Resource.hpp"
#include "Player.hpp"
#include "Interface.hpp"
#include "Sound.hpp"

Player::Player(int X, int Y, int H, int Q, int W, int E, int HC) : XPos(X), YPos(Y), Health(H), SkillQ(Q), SkillW(W), SkillE(E){
	memset(HitCheck, HC, sizeof(HitCheck));
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

void Player::SetPoint(POINT* Pos, const double Num) const{
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

void Player::PaintPlayer(HDC hdc, HDC Bithdc) const {
	bool KeyUp = (GetAsyncKeyState(VK_UP) & 0x8000);
	bool KeyDown = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	bool KeyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	bool KeyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000);

	POINT Pos[5];

	static double Rad = 0.0;	

	//1은 0도부터 시작 2는 45도부터 시작 3은 45도부터 시작 4는 0도부터 시작 5는 90도부터 시작

	if (KeyUp && KeyLeft) {
		//위쪽+오른쪽
		SetPoint(Pos, 45.0);
		Rad = 45.0;
	}
	else if (KeyUp && KeyRight) {
		//위쪽+오른쪽
		SetPoint(Pos, 315.0);
		Rad = 315.0;
	}
	else if (KeyDown && KeyLeft) {
		//아래쪽+왼쪽
		SetPoint(Pos, 135.0);
		Rad = 135.0;
	}
	else if (KeyDown && KeyRight) {
		//아래쪽+오른쪽
		SetPoint(Pos, 225.0);
		Rad = 225.0;
	}
	else if (KeyUp && !KeyDown) {
		//위쪽
		SetPoint(Pos, 0.0);
		Rad = 0.0;
	}
	else if (KeyDown && !KeyUp) {
		//아래쪽
		SetPoint(Pos, 180.0);
		Rad = 180.0;
	}
	else if (KeyLeft && !KeyRight) {
		//왼쪽
		SetPoint(Pos, 90.0);
		Rad = 90.0;
	}
	else if (KeyRight && !KeyLeft) {
		//오른쪽
		SetPoint(Pos, 270.0);
		Rad = 270.0;
	}
	else {
		SetPoint(Pos, Rad);
	}

	OldPBrush = (HBRUSH)SelectObject(hdc, PlayerBrush1);
	OldPPen = (HPEN)SelectObject(hdc, PlayerPen1);

	Polygon(hdc, Pos, 5);

	if (GetSkillE() > 50) {
		//E스킬이 사용중이라면
		SelectObject(Bithdc, SkillEUseBit);

		TransparentBlt(hdc, XPos - 20, YPos - 20, 40, 40, Bithdc, 0, 0, 40, 40, RGB(255, 255, 255));
	}

	SelectObject(hdc, OldPBrush);
	SelectObject(hdc, OldPPen);
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

void Player::UseSkill(WPARAM wParam) {
	switch (wParam) {
	case 'q':
	case 'Q':
		if (GetSkillQ() == 0) {
			UseSkillQ();

			//SkillQ 사운드 재생
			PlaySkillQSound();
		}
		break;
	case 'w':
	case 'W':
		if (GetSkillW() == 0) {
			UseSkillW();

			//SkillW 사운드 재생
			PlaySkillWSound();
		}	
		break;
	case 'e':
	case 'E':
		if (GetSkillE() == 0) {
			UseSkillE();

			//SkillE 사운드 재생
			PlaySkillESound();
		}
	default:
		break;
	}
}

void Player::SkillCoolDown(HWND hwnd) {
	static int Count = 0;

	//0.1초(게임시간)당 1씩 증가
	Count++;

	if (Count == 10) {
		Count = 0;

		//SkillQ 쿨다운이 0보다 크면 1씩 감소
		if (SkillQ > 0)
			SkillQ--;
		
		//SkillW 쿨다운이 0보다 크면 1씩 감소
		if (SkillW > 0) {
			if (SkillW == 30) {
				//EnemyTimer 재설정
				SetTimer(hwnd, 10, 200, NULL);
			}
			if (SkillW == 25) {
				//EnemyTimer 재설정
				SetTimer(hwnd, 10, 100, NULL);
			}
			SkillW--;
		}
			

		//SkillE 쿨다운이 0보다 크면 1씩 감소
		if (SkillE > 0)
			SkillE--;
	}
}

void Player::UseSkillQ() {
	//SkillQ 쿨다운 초기화
	SkillQ = 20;

	//효과 발동
	Health += 10;
	if (Health > 100)
		Health = 100;
}

void Player::UseSkillW() {
	//SkillW 쿨다운 초기화
	SkillW = 30;
}

void Player::UseSkillE() {
	//SkillE 쿨다운 초기화
	SkillE = 60;
}

void Player::SetHitCheck(const int Left, const int Right, const int Top, const int Bottom, const bool OnOff) {
	for (int x = Left; x <= Right; x++)
		for (int y = Top; y <= Bottom; y++) {
			if (OnOff)
				//On일경우 HitCheck의 값을 1씩 증가시킨다.
				HitCheck[y][x]++;
			else
				//Off일경우 HitCheck의 값을 1씩 감소시킨다.
				HitCheck[y][x]--;
		}
}

void Player::CheckHitCheck(Interface* Inter) {
	 
	if (SkillE < 50) {
		//SkillE 무적 상태 게임시간 약(10초) 동안은 무적이다.

		//원활한 플레이를 위해서 피격 범위를 감소시킨다.
		//플레이어의 크기 (가로 20 세로 20) 이 아닌 (가로 18 세로 18)으로 지정한다.
		if (HitCheck[(YPos - TOPWALL - 9) / 60][(XPos - LEFTWALL - 9) / 60] > 0 ||
			HitCheck[(YPos - TOPWALL - 9) / 60][(XPos - LEFTWALL + 9) / 60] > 0 ||
			HitCheck[(YPos - TOPWALL + 9) / 60][(XPos - LEFTWALL - 9) / 60] > 0 ||
			HitCheck[(YPos - TOPWALL + 9) / 60][(XPos - LEFTWALL + 9) / 60] > 0) {

			//플레이어의 (순서대로) 왼쪽위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래 지점의 HitCheck가 1이상일 경우

			//Health를 감소시킨다.
			Health--;

			//ScoreUp값을 초기화한다.
			Inter->ResetScoreUp();
		}
	}
	
}

void Player::ResetHitCheck() {
	//HitCheck를 Reset해준다.
	memset(HitCheck, 0, sizeof(HitCheck));
}

const bool Player::PlayerDie() const {
	if (Health == 0)
		return TRUE;
	return FALSE;
}


void Player::PaintPlayerIF(HDC hdc, HDC Bithdc) const {

	//기본 텍스트들 출력
	SelectObject(hdc, PlayerIFFont1);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 45, PTOPWALL + 5, _T("HP"), 2);
	TextOut(hdc, 520, PTOPWALL + 5, _T("Q"), 1);
	TextOut(hdc, 630, PTOPWALL + 5, _T("W"), 1);
	TextOut(hdc, 740, PTOPWALL + 5, _T("E"), 1);

	//기본 비트맵 틀
	OldPBrush = (HBRUSH)SelectObject(hdc, PlayerIFBrush1);
	//체력바 틀
	Rectangle(hdc, 90, PTOPWALL + 5, 500, PBOTTOMWALL - 5);
	//체력바
	SelectObject(Bithdc, HealthBit);
	TransparentBlt(hdc, 95, PTOPWALL + 10, Health * 4, 40, Bithdc, 0, 0, 400, 40, RGB(255, 255, 255));

	//Q스킬
	Rectangle(hdc, 550, PTOPWALL + 5, 600, PBOTTOMWALL - 5);
	SelectObject(Bithdc, SKillQBit);
	TransparentBlt(hdc, 550, PTOPWALL + 5, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//W스킬
	Rectangle(hdc, 660, PTOPWALL + 5, 710, PBOTTOMWALL - 5);
	SelectObject(Bithdc, SKillWBit);
	TransparentBlt(hdc, 660, PTOPWALL + 5, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));
	//E스킬
	Rectangle(hdc, 770, PTOPWALL + 5, 820, PBOTTOMWALL - 5);
	SelectObject(Bithdc, SKillEBit);
	TransparentBlt(hdc, 770, PTOPWALL + 5, 50, 50, Bithdc, 0, 0, 50, 50, RGB(0, 0, 0));

	SelectObject(hdc, PlayerIFFont2);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

	//체력 표시
	wchar_t str1[10];
	swprintf_s(str1, L"%d%d%d / 100", Health / 100, Health / 10 % 10, Health % 10);
	TextOut(hdc, 240, PTOPWALL + 15, str1, 9);

	//Q스킬 쿨다운 표시
	wchar_t strQ[3];
	swprintf_s(strQ, L"%d%d", SkillQ / 10, SkillQ % 10);
	TextOut(hdc, 560, PTOPWALL + 15, strQ, 2);

	//W스킬 쿨다운 표시
	wchar_t strW[3];
	swprintf_s(strW, L"%d%d", SkillW / 10, SkillW % 10);
	TextOut(hdc, 670, PTOPWALL + 15, strW, 2);

	//E스킬 쿨다운 표시
	wchar_t strE[3];
	swprintf_s(strE, L"%d%d", SkillE / 10, SkillE % 10);
	TextOut(hdc, 780, PTOPWALL + 15, strE, 2);

	SelectObject(hdc, OldPBrush);
}


void CreatePlayer(Player** player, HINSTANCE hInst) {
	PlayerIFBrush1 = CreateSolidBrush(RGB(0, 0, 0));
	PlayerBrush1 = CreateSolidBrush(RGB(255, 216, 216));

	PlayerPen1 = CreatePen(PS_SOLID, 1, RGB(204, 61, 61));

	PlayerIFFont1 = CreateFontW(50, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
	PlayerIFFont2 = CreateFontW(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

	/*HealthBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Health.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SKillQBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\SkillQ.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SKillWBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\SkillW.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SKillEBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\SkillE.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	SkillEUseBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Shield.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/

	HealthBit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Health));

	SKillQBit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_SkillQ));
	SKillWBit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_SkillW));
	SKillEBit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_SkillE));


	SkillEUseBit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Shield));
	
	if (*player == NULL) {
		//*player가 NULL일 경우 생성한다.
		*player = new Player(640, 450, 100, 0, 0, 0, 0);
	}

}
void DeletePlayer(Player** player) {
	if (*player != NULL) {
		//*player가 NULL이 아닐경우 제거한다.
		delete* player;
		*player = NULL;
		DeleteObject(PlayerIFBrush1);
		DeleteObject(PlayerPen1);
		DeleteObject(PlayerIFFont1);
		DeleteObject(PlayerIFFont2);
	}
}