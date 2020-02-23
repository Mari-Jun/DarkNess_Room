#include "Resource.hpp"
#include "Player.hpp"

Player::Player(int X, int Y) : XPos(X), YPos(Y) {

}

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

void Player::PaintPlayer(HDC hdc) const {


	Rectangle(hdc, XPos - 10, YPos - 10, XPos + 10, YPos + 10);

}

void CreatePlayer(Player** player) {
	if (*player == NULL) {
		//*player가 NULL일 경우 생성한다.
		*player = new Player(640, 450);
	}

}
void DeletePlayer(Player** player) {
	if (*player != NULL) {
		//*player가 NULL이 아닐경우 제거한다.
		delete* player;
		*player = NULL;
	}
}