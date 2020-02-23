#include "Resource.hpp"
#include "Enemy.hpp"


//기본 에너미

Enemy::Enemy(int X, int Y, bool C) : XPos(X), YPos(Y), Charging(C) {

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

void Enemy::ChangeCharging() {
	//Charging값을 true로 바꾼다.
	Charging = true;
}

void Enemy::SetCharging() {
	//공격 턴이 끝났기 때문에 Charging값을 false로 바꾼다.
	Charging = false;
}





//직선포 에너미

LineEnemy::LineEnemy(int X, int Y, int C, int R) : Enemy(X, Y, C), Range(R) {

}

const int LineEnemy::GetRange() const {
	//Range 값을 반환한다.
	return Range;
}

void LineEnemy::SetRange() {

}

void LineEnemy::PaintLEnmey(HDC hdc) const {

}

void LineEnemy::PaintLShot(HDC hdc) const {

}




//광역포 에너미

WideEnemy::WideEnemy(int X, int Y, int C, int D) : Enemy(X, Y, C), Direction(D) {

}

const int WideEnemy::GetDirection() const {
	//Direction값을 반환한다.
	return  Direction;
}

void WideEnemy::PaintWEnmey(HDC hdc) const {

}

void WideEnemy::PaintWShot(HDC hdc) const {

}




//폭탄 에너미

BombEnemy::BombEnemy(int X, int Y, int C, int DX, int DY) : Enemy(X, Y, C), DXPos(DX), DYPos(DY) {

}

const int BombEnemy::GetDXPos() const {
	//DXPos값을 반환한다.
	return DXPos;
}

const int BombEnemy::GetDYPos() const {
	//DYPos값을 반환한다.
	return DYPos;
}

void BombEnemy::SetDropPos() {

}

void BombEnemy::PaintBEnmey(HDC hdc) const {

}

void BombEnemy::PaintBShot(HDC hdc) const {

}




//범위포 에너미

RectEnemy::RectEnemy(int X, int Y, int C, int DX, int DY, int Co) : BombEnemy(X, Y, C, DX, DY), Count(Co) {

}

const int RectEnemy::GetCount() const {
	//Count값을 반환한다.
	return Count;
}

void RectEnemy::SetCount() {

}

void RectEnemy::PaintREnmey(HDC hdc) const {

}

void RectEnemy::PaintRShot(HDC hdc) const {

}


