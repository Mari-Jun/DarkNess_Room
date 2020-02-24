#include "Resource.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


//기본 에너미

Enemy::Enemy(int X, int Y, bool C, int D) : XPos(X), YPos(Y), Charging(C), Delay(D) {

}

const int Enemy::GetXPos() const {
	//XPos값을 반환한다.
	return XPos;
}

const int Enemy::GetYPos() const {
	//YPos값을 반환한다.
	return YPos;
}

const bool Enemy::GetCharging() const {
	//Charging값을 반환한다.
	return Charging;
}

const int Enemy::GetDelay() const {
	//Delay값을 반환한다.
	return Delay;
}

void Enemy::ChangeCharging() {
	//Charging값을 true로 바꾼다.
	Charging = true;
}

void Enemy::SetCharging() {
	//공격 턴이 끝났기 때문에 Charging값을 false로 바꾼다.
	Charging = false;
}


void Enemy::ChangeDelay() {

}




//직선포 에너미

LineEnemy::LineEnemy(int X, int Y, bool C, int D, int R) : Enemy(X, Y, C, D), Range(R) {

}

const int LineEnemy::GetRange() const {
	//Range 값을 반환한다.
	return Range;
}

void LineEnemy::SetRange() {

}

const bool LineEnemy::HitPlayer(Player* player) const {
	return false;
}

void LineEnemy::PaintEnmey(HDC hdc) const {
	Rectangle(hdc, GetXPos() - 25, GetYPos() - 35, GetXPos() + 25, GetYPos() + 35);
}

void LineEnemy::PaintShot(HDC hdc) const {

}




//광역포 에너미

WideEnemy::WideEnemy(int X, int Y, bool C, int D, int Di) : Enemy(X, Y, C, D), Direction(Di) {

}

const int WideEnemy::GetDirection() const {
	//Direction값을 반환한다.
	return  Direction;
}

void WideEnemy::SetDirection() {

}

const bool WideEnemy::HitPlayer(Player* player) const {
	return false;
}

void WideEnemy::PaintEnmey(HDC hdc) const {

}

void WideEnemy::PaintShot(HDC hdc) const {

}




//폭탄 에너미

BombEnemy::BombEnemy(int X, int Y, bool C, int D, int DX, int DY) : Enemy(X, Y, C, D), DXPos(DX), DYPos(DY) {

}

const int BombEnemy::GetDXPos() const {
	//DXPos값을 반환한다.
	return DXPos;
}

const int BombEnemy::GetDYPos() const {
	//DYPos값을 반환한다.
	return DYPos;
}

const bool BombEnemy::HitPlayer(Player* player) const {
	return false;
}

void BombEnemy::SetDropPos() {

}

void BombEnemy::PaintEnmey(HDC hdc) const {

}

void BombEnemy::PaintShot(HDC hdc) const {

}




//범위포 에너미

RectEnemy::RectEnemy(int X, int Y, bool C, int D, int DX, int DY, int Co) : BombEnemy(X, Y, C, D, DX, DY), Count(Co) {

}

const int RectEnemy::GetCount() const {
	//Count값을 반환한다.
	return Count;
}

void RectEnemy::SetCount() {

}

const bool RectEnemy::HitPlayer(Player* player) const {
	return false;
}

void RectEnemy::PaintEnmey(HDC hdc) const {

}

void RectEnemy::PaintShot(HDC hdc) const {

}


void CreateLEnemy(LineEnemy** Lenemy) {
	for (int i = 0; i < 20; i++) {
		if (Lenemy[i] == NULL) {
			//Lenemy[i]가 NULL이면 생성
			Lenemy[i] = new LineEnemy(150 + 60 * i, 75, true, 10, 10);
		}
		
	}
}

void CreateWEnemy(WideEnemy** Wenemy) {

}

void CreateBEnemy(BombEnemy** Benemy) {

}

void CreateREnemy(RectEnemy** Renemy) {

}