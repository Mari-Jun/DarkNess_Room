#include "Resource.hpp"
#include "Player.hpp"

Player::Player(int X, int Y, int H, int Q, int W, int E, int HC) : XPos(X), YPos(Y), Health(H), SkillQ(Q), SkillW(W), SkillE(E){
	memset(HitCheck, HC, sizeof(HitCheck));
}

//�÷��̾� ����

const int Player::GetXPos() const {
	//�÷��̾��� X��ǥ�� ��ȯ
	return XPos;
}

const int Player::GetYPos() const {
	//�÷��̾��� Y��ǥ�� ��ȯ
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
	//�÷��̾� �̵� ���� üũ �Լ�

	//�׵θ� ��
	if (XPos < LEFTWALL + 10 || XPos > RIGHTWALL - 10 || YPos < TOPWALL + 10 || YPos > BOTTOMWALL - 10)
		return false;

	//�߰� ��
	if (XPos > LLEFTWALL - 10 && XPos < LRIGHTWALL + 10 && YPos > LTOPWALL - 10 && YPos < LBOTTOMWALL + 10)
		return false;
	
	return true;
}

void Player::MoveLeft() {
	//�÷��̾ �������� �̵���Ų��.
	XPos -= 10;
	if(!MoveRangeCheck())
		XPos += 10;
}

void Player::MoveRight() {
	//�÷��̾ ���������� �̵���Ų��.
	XPos += 10;
	if (!MoveRangeCheck())
		XPos -= 10;
}

void Player::MoveTop() {
	//�÷��̾ �������� �̵���Ų��.
	YPos -= 10;
	if (!MoveRangeCheck())
		YPos += 10;
}

void Player::MoveBottom() {
	//�÷��̾ �Ʒ������� �̵���Ų��.
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

	//1�� 0������ ���� 2�� 45������ ���� 3�� 45������ ���� 4�� 0������ ���� 5�� 90������ ����

	if (KeyUp && KeyLeft) {
		//����+������
		SetPoint(Pos, 45.0);
		Rad = 45.0;
	}
	else if (KeyUp && KeyRight) {
		//����+������
		SetPoint(Pos, 315.0);
		Rad = 315.0;
	}
	else if (KeyDown && KeyLeft) {
		//�Ʒ���+����
		SetPoint(Pos, 135.0);
		Rad = 135.0;
	}
	else if (KeyDown && KeyRight) {
		//�Ʒ���+������
		SetPoint(Pos, 225.0);
		Rad = 225.0;
	}
	else if (KeyUp && !KeyDown) {
		//����
		SetPoint(Pos, 0.0);
		Rad = 0.0;
	}
	else if (KeyDown && !KeyUp) {
		//�Ʒ���
		SetPoint(Pos, 180.0);
		Rad = 180.0;
	}
	else if (KeyLeft && !KeyRight) {
		//����
		SetPoint(Pos, 90.0);
		Rad = 90.0;
	}
	else if (KeyRight && !KeyLeft) {
		//������
		SetPoint(Pos, 270.0);
		Rad = 270.0;
	}
	else {
		SetPoint(Pos, Rad);
	}

	OldPPen = (HPEN)SelectObject(hdc, PlayerPen1);

	Polygon(hdc, Pos, 5);

	SelectObject(hdc, OldPPen);
}





//�������̽� ����

const int Player::GetHealth() const {
	//Health���� ��ȯ�Ѵ�.
	return Health;
}

const int Player::GetSkillQ() const {
	//SkillQ���� ��ȯ�Ѵ�.
	return SkillQ;
}

const int Player::GetSkillW() const {
	//SkillW���� ��ȯ�Ѵ�.
	return SkillW;
}

const int Player::GetSkillE() const {
	//SkillE���� ��ȯ�Ѵ�.
	return SkillE;
}

void Player::UseSkill(WPARAM wParam) {
	switch (wParam) {
	case 'q':
		if (GetSkillQ() == 0)
			UseSkillQ();
		break;
	default:
		break;
	}
}

void Player::SkillCoolDown() {
	static int Count = 0;

	//0.1��(���ӽð�)�� 1�� ����
	Count++;

	if (Count == 10) {
		Count = 0;

		//SkillQ ��ٿ��� 0���� ũ�� 1�� ����
		if (SkillQ > 0)
			SkillQ--;
		
		//SkillW ��ٿ��� 0���� ũ�� 1�� ����
		if (SkillW > 0)
			SkillW--;

		//SkillE ��ٿ��� 0���� ũ�� 1�� ����
		if (SkillE > 0)
			SkillE--;
	}
}

void Player::UseSkillQ() {
	//SkillQ ��ٿ� �ʱ�ȭ
	SkillQ = 20;

	//ȿ�� �ߵ�
	Health += 10;
	if (Health > 100)
		Health = 100;
}

void Player::UseSkillW() {

}

void Player::UseSkillE() {

}

void Player::SetHitCheck(int Left, int Right, int Top, int Bottom, bool OnOff) {
	for (int x = Left; x <= Right; x++)
		for (int y = Top; y <= Bottom; y++) {
			if (OnOff)
				//On�ϰ�� HitCheck�� ���� 1�� ������Ų��.
				HitCheck[y][x]++;
			else
				//Off�ϰ�� HitCheck�� ���� 1�� ���ҽ�Ų��.
				HitCheck[y][x]--;
		}
}

void Player::CheckHitCheck() {
	 
	if (HitCheck[(YPos - 130) / 60][(XPos - 130) / 60] > 0 ||
		HitCheck[(YPos - 130) / 60][(XPos - 110) / 60] > 0 ||
		HitCheck[(YPos - 110) / 60][(XPos - 130) / 60] > 0 ||
		HitCheck[(YPos - 110) / 60][(XPos - 110) / 60] > 0) {
		
		//�÷��̾��� (�������) ������, ������ ��, ���� �Ʒ�, ������ �Ʒ� ������ HitCheck�� 1�̻��� ���

		//Health�� ���ҽ�Ų��.
		Health--;
	}
}


void Player::PaintPlayerIF(HDC hdc, HDC Bithdc) const {

	//�⺻ �ؽ�Ʈ�� ���
	SelectObject(hdc, PlayerIFFont1);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 45, PTOPWALL + 5, _T("HP"), 2);
	TextOut(hdc, 520, PTOPWALL + 5, _T("Q"), 1);
	TextOut(hdc, 630, PTOPWALL + 5, _T("W"), 1);
	TextOut(hdc, 740, PTOPWALL + 5, _T("E"), 1);


	//������ʹ� ���� �������̽� Ŭ���� ���� �����Ѵ�. �ϴ��� �ӽ÷� ����ٰ� ����س��°���
	TextOut(hdc, 860, PTOPWALL + 5, _T("LEVEL"), 5);
	//Level ���
	TextOut(hdc, 960, PTOPWALL + 5, _T("10"), 2);
	TextOut(hdc, 1020, PTOPWALL + 5, _T("TIME"), 4);
	TextOut(hdc, 1110, PTOPWALL + 5, _T("00:00:00"), 8);

	//�⺻ ��Ʈ�� Ʋ
	OldPBrush = (HBRUSH)SelectObject(hdc, PlayerIFBrush1);
	//ü�¹� Ʋ
	Rectangle(hdc, 90, PTOPWALL + 5, 500, PBOTTOMWALL - 5);
	//ü�¹�
	SelectObject(Bithdc, HealthBit);
	TransparentBlt(hdc, 95, PTOPWALL + 10, Health * 4, 40, Bithdc, 0, 0, 400, 40, RGB(255, 255, 255));

	//Q��ų
	Rectangle(hdc, 550, PTOPWALL + 5, 600, PBOTTOMWALL - 5);
	//W��ų
	Rectangle(hdc, 660, PTOPWALL + 5, 710, PBOTTOMWALL - 5);
	//E��ų
	Rectangle(hdc, 770, PTOPWALL + 5, 820, PBOTTOMWALL - 5);

	SelectObject(hdc, PlayerIFFont2);
	SetTextColor(hdc, RGB(200, 200, 200));
	SetBkMode(hdc, TRANSPARENT);

	//ü�� ǥ��
	wchar_t str1[10];
	swprintf_s(str1, L"%d%d%d / 100", Health / 100, Health / 10 % 10, Health % 10);
	TextOut(hdc, 240, PTOPWALL + 15, str1, 9);

	//Q��ų ��ٿ� ǥ��
	wchar_t str2[3];
	swprintf_s(str2, L"%d%d", SkillQ / 10, SkillQ % 10);
	TextOut(hdc, 560, PTOPWALL + 15, str2, 2);

	TextOut(hdc, 670, PTOPWALL + 15, _T("40"), 2);
	TextOut(hdc, 780, PTOPWALL + 15, _T("60"), 2);

	SelectObject(hdc, OldPBrush);
}


void CreatePlayer(Player** player) {
	if (*player == NULL) {
		//*player�� NULL�� ��� �����Ѵ�.
		*player = new Player(640, 450, 100, 0, 0, 0, 0);

		PlayerIFBrush1 = CreateSolidBrush(RGB(0, 0, 0));

		PlayerPen1 = CreatePen(PS_SOLID, 1, RGB(204, 61, 61));

		PlayerIFFont1 = CreateFontW(50, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
		PlayerIFFont2 = CreateFontW(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));

		HealthBit = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Health.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

}
void DeletePlayer(Player** player) {
	if (*player != NULL) {
		//*player�� NULL�� �ƴҰ�� �����Ѵ�.
		delete* player;
		*player = NULL;
		DeleteObject(PlayerIFBrush1);
		DeleteObject(PlayerPen1);
		DeleteObject(PlayerIFFont1);
		DeleteObject(PlayerIFFont2);
	}
}