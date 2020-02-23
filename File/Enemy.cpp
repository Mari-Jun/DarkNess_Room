#include "Resource.hpp"
#include "Enemy.hpp"


//�⺻ ���ʹ�

Enemy::Enemy(int X, int Y, bool C) : XPos(X), YPos(Y), Charging(C) {

}

const int Enemy::GetXPos() const {
	//XPos���� ��ȯ�Ѵ�.
	return XPos;
}

const int Enemy::GetYPos() const {
	//YPos���� ��ȯ�Ѵ�.
	return YPos;
}

const bool Enemy::GetCharging() const {
	//Charging���� ��ȯ�Ѵ�.
	return Charging;
}

void Enemy::ChangeCharging() {
	//Charging���� true�� �ٲ۴�.
	Charging = true;
}

void Enemy::SetCharging() {
	//���� ���� ������ ������ Charging���� false�� �ٲ۴�.
	Charging = false;
}





//������ ���ʹ�

LineEnemy::LineEnemy(int X, int Y, int C, int R) : Enemy(X, Y, C), Range(R) {

}

const int LineEnemy::GetRange() const {
	//Range ���� ��ȯ�Ѵ�.
	return Range;
}

void LineEnemy::SetRange() {

}

void LineEnemy::PaintLEnmey(HDC hdc) const {

}

void LineEnemy::PaintLShot(HDC hdc) const {

}




//������ ���ʹ�

WideEnemy::WideEnemy(int X, int Y, int C, int D) : Enemy(X, Y, C), Direction(D) {

}

const int WideEnemy::GetDirection() const {
	//Direction���� ��ȯ�Ѵ�.
	return  Direction;
}

void WideEnemy::PaintWEnmey(HDC hdc) const {

}

void WideEnemy::PaintWShot(HDC hdc) const {

}




//��ź ���ʹ�

BombEnemy::BombEnemy(int X, int Y, int C, int DX, int DY) : Enemy(X, Y, C), DXPos(DX), DYPos(DY) {

}

const int BombEnemy::GetDXPos() const {
	//DXPos���� ��ȯ�Ѵ�.
	return DXPos;
}

const int BombEnemy::GetDYPos() const {
	//DYPos���� ��ȯ�Ѵ�.
	return DYPos;
}

void BombEnemy::SetDropPos() {

}

void BombEnemy::PaintBEnmey(HDC hdc) const {

}

void BombEnemy::PaintBShot(HDC hdc) const {

}




//������ ���ʹ�

RectEnemy::RectEnemy(int X, int Y, int C, int DX, int DY, int Co) : BombEnemy(X, Y, C, DX, DY), Count(Co) {

}

const int RectEnemy::GetCount() const {
	//Count���� ��ȯ�Ѵ�.
	return Count;
}

void RectEnemy::SetCount() {

}

void RectEnemy::PaintREnmey(HDC hdc) const {

}

void RectEnemy::PaintRShot(HDC hdc) const {

}


