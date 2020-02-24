#include "Resource.hpp"
#include "Player.hpp"

Player::Player(int X, int Y, int H, int Q, int W, int E) : XPos(X), YPos(Y), Health(H), SkillQ(Q), SkillW(W), SkillE(E) {

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
		this->SetPoint(Pos, 45.0);
		Rad = 45.0;
	}
	else if (KeyUp && KeyRight) {
		//����+������
		this->SetPoint(Pos, 315.0);
		Rad = 315.0;
	}
	else if (KeyDown && KeyLeft) {
		//�Ʒ���+����
		this->SetPoint(Pos, 135.0);
		Rad = 135.0;
	}
	else if (KeyDown && KeyRight) {
		//�Ʒ���+������
		this->SetPoint(Pos, 225.0);
		Rad = 225.0;
	}
	else if (KeyUp && !KeyDown) {
		//����
		this->SetPoint(Pos, 0.0);
		Rad = 0.0;
	}
	else if (KeyDown && !KeyUp) {
		//�Ʒ���
		this->SetPoint(Pos, 180.0);
		Rad = 180.0;
	}
	else if (KeyLeft && !KeyRight) {
		//����
		this->SetPoint(Pos, 90.0);
		Rad = 90.0;
	}
	else if (KeyRight && !KeyLeft) {
		//������
		this->SetPoint(Pos, 270.0);
		Rad = 270.0;
	}
	else {
		this->SetPoint(Pos, Rad);
	}

	Polygon(hdc, Pos, 5);
	
	//XPoint += float(-Speed * cos(M_PI / 180 * 45)), YPoint += float(Speed * sin(M_PI / 180 * 45)), Roll = -1;
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

void Player::PaintPlayerIF(HDC hdc) const {

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
		//*player�� NULL�� ��� �����Ѵ�.
		*player = new Player(640, 450, 100, 0, 0, 0);

		PlayerIFBrush1 = CreateSolidBrush(RGB(0, 0, 0));

		PlayerIFFont1 = CreateFontW(50, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Algerian"));
		PlayerIFFont2 = CreateFontW(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	}

}
void DeletePlayer(Player** player) {
	if (*player != NULL) {
		//*player�� NULL�� �ƴҰ�� �����Ѵ�.
		delete* player;
		*player = NULL;
		DeleteObject(PlayerIFBrush1);
		DeleteObject(PlayerIFFont1);
		DeleteObject(PlayerIFFont2);
	}
}