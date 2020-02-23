#include "Resource.hpp"
#include "Player.hpp"

Player::Player(int X, int Y) : XPos(X), YPos(Y) {

}

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

void Player::PaintPlayer(HDC hdc) const {


	Rectangle(hdc, XPos - 10, YPos - 10, XPos + 10, YPos + 10);

}

void CreatePlayer(Player** player) {
	if (*player == NULL) {
		//*player�� NULL�� ��� �����Ѵ�.
		*player = new Player(640, 450);
	}

}
void DeletePlayer(Player** player) {
	if (*player != NULL) {
		//*player�� NULL�� �ƴҰ�� �����Ѵ�.
		delete* player;
		*player = NULL;
	}
}