#include "Resource.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


//�⺻ ���ʹ�

Enemy::Enemy(int X, int Y, bool C, int D) : XPos(X), YPos(Y), Charging(C), Delay(D) {

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

const int Enemy::GetDelay() const {
	//Delay���� ��ȯ�Ѵ�.
	return Delay;
}

void Enemy::ChangeCharging() {
	//Charging���� true�� �ٲ۴�.
	Charging = true;
}

void Enemy::SetCharging() {
	//���� ���� ������ ������ Charging���� false�� �ٲ۴�.
	Charging = false;
}


void Enemy::ChangeDelay() {

}




//������ ���ʹ�

LineEnemy::LineEnemy(int X, int Y, bool C, int D, int R) : Enemy(X, Y, C, D), Range(R) {

}

const int LineEnemy::GetRange() const {
	//Range ���� ��ȯ�Ѵ�.
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




//������ ���ʹ�

WideEnemy::WideEnemy(int X, int Y, bool C, int D, int Di) : Enemy(X, Y, C, D), Direction(Di) {

}

const int WideEnemy::GetDirection() const {
	//Direction���� ��ȯ�Ѵ�.
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




//��ź ���ʹ�

BombEnemy::BombEnemy(int X, int Y, bool C, int D, int DX, int DY) : Enemy(X, Y, C, D), DXPos(DX), DYPos(DY) {

}

const int BombEnemy::GetDXPos() const {
	//DXPos���� ��ȯ�Ѵ�.
	return DXPos;
}

const int BombEnemy::GetDYPos() const {
	//DYPos���� ��ȯ�Ѵ�.
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




//������ ���ʹ�

RectEnemy::RectEnemy(int X, int Y, bool C, int D, int DX, int DY, int Co) : BombEnemy(X, Y, C, D, DX, DY), Count(Co) {

}

const int RectEnemy::GetCount() const {
	//Count���� ��ȯ�Ѵ�.
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
			//Lenemy[i]�� NULL�̸� ����
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