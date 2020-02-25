#include "Resource.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


//�⺻ ���ʹ�

Enemy::Enemy(int X, int Y, int C, int D) : XPos(X), YPos(Y), Charging(C), Delay(D) {

}

const int Enemy::GetXPos() const {
	//XPos���� ��ȯ�Ѵ�.
	return XPos;
}

const int Enemy::GetYPos() const {
	//YPos���� ��ȯ�Ѵ�.
	return YPos;
}

const int Enemy::GetCharging() const {
	//Charging���� ��ȯ�Ѵ�.
	return Charging;
}

const int Enemy::GetDelay() const {
	//Delay���� ��ȯ�Ѵ�.
	return Delay;
}

void Enemy::SetCharging() {
	//Charging���� 15�� �����Ѵ�.
	Charging = 15;
}

void Enemy::ChangeCharging() {
	//Charging�� 0���� ũ�ٸ� 1�� ���ҽ�Ų��.
	if (Charging > 0) {
		Charging--;
		//���� Charging�� 0�� �ȴٸ� Delay�� 0���� ������ش�.
		if (Charging == 0)
			Delay = 0;
	}
}

void Enemy::SetDelay() {
	//11~21(������ 10~20)������ DelayŸ�� ���ӽð����� 1.0��~ 2.0�ʸ� ����.
	Delay = rand() % 11 + 11;
}

void Enemy::ChangeDelay() {
	//Delay�� 1���� ũ�ٸ� 1�� ���ҽ�Ų��.
	if (Delay > 1) {
		Delay--;
		//���� Delay�� 1�̶�� Charging�� �������ش�.
		if (Delay == 1)
			SetCharging();
	}
		
}




//������ ���ʹ�

LineEnemy::LineEnemy(int X, int Y, int C, int D, int R, int Di) : Enemy(X, Y, C, D), Range(R), Direction(Di){

}

const int LineEnemy::GetRange() const {
	//Range ���� ��ȯ�Ѵ�.
	return Range;
}

const int LineEnemy::GetDirection() const {
	//Direction���� ��ȯ�Ѵ�.
	return Direction;
}

void LineEnemy::SetRange() {
	if ((GetXPos() > LLEFTWALL&& GetXPos() < LRIGHTWALL) || (GetYPos() > LTOPWALL&& GetYPos() < LBOTTOMWALL)) {
		//�������� �߻� ������ �߰� ���� ��ĥ ���
		//������ 6~8���� �����Ѵ�.
		Range = rand() % 3 + 6;
	}
	else {
		//��ġ�� �ʴ� ���
		//������ 11~20���� �����Ѵ�
		Range = rand() % 10 + 11;
	}
}

const bool LineEnemy::HitPlayer(Player* player) const {
	if (GetXPos() - 10 < player->GetXPos() && GetXPos() + 10 > player->GetXPos() && GetYPos() + 10 > player->GetYPos())
		return true;
	return false;
}

void LineEnemy::PaintEnmey(HDC hdc) const {
	if (this->GetCharging()) {
		//�߻� ���̶��
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}
	else {
		//�߻� ���� �ƴ϶��
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush1);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}

	if (abs(Direction) == 1) {
		//���� ���ϰ�� , //�Ʒ��� ���ϰ��
		POINT Pos[4] = { {GetXPos() - 20,GetYPos() - 20 * Direction},{GetXPos() + 20,GetYPos() - 20 * Direction},{GetXPos() + 10,GetYPos() + 35 * Direction},{GetXPos() - 10,GetYPos() + 35 * Direction} };

		Ellipse(hdc, GetXPos() - 20, GetYPos() - 40 * Direction, GetXPos() + 20, GetYPos());
		Polygon(hdc, Pos, 4);
		RoundRect(hdc, GetXPos() - 13, GetYPos() + 32 * Direction, GetXPos() + 13, GetYPos() + 38 * Direction, 6, 6);
	
	}
	else {
		//���� ���ϰ��, //������ ���ϰ��
		POINT Pos[4] = { {GetXPos() - 20 * Direction / 2,GetYPos() - 20},{GetXPos() + 35 * Direction / 2,GetYPos() - 10},{GetXPos() + 35 * Direction / 2,GetYPos() + 10},{GetXPos() - 20 * Direction / 2,GetYPos() + 20} };

		Ellipse(hdc, GetXPos() - 40 * Direction / 2, GetYPos() - 20, GetXPos(), GetYPos() + 20);
		Polygon(hdc, Pos, 4);
		RoundRect(hdc, GetXPos() + 32 * Direction / 2, GetYPos() - 13, GetXPos() + 38 * Direction / 2, GetYPos() + 13, 6, 6);
	}

	SelectObject(hdc, OldEBrush);
	SelectObject(hdc, OldEPen);
}

void LineEnemy::PaintShot(HDC hdc) const{

	if (this->GetDelay() != 0) {
		//�߻� ������ 0�� �ƴҶ� 
		if (this->GetCharging() != 0) {
			//�߻� ���϶� 
			//�� Delay�� 1�̰� Charging�� 1�̻��϶�
			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
			OldEPen = (HPEN)SelectObject(hdc, LPen1);
		}
		else {
			//�߻� ������϶� 
			//�� Delay�� 1�̻��̰� Charging�� 0�϶�
			SetBkMode(hdc, TRANSPARENT);
			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush3);
			OldEPen = (HPEN)SelectObject(hdc, LPen1);
		}
		if (abs(Direction) == 1) {
			Rectangle(hdc, GetXPos() - 30, GetYPos() + 45 * Direction, GetXPos() + 30, GetYPos() + (45 + Range * 60) * Direction);
		}
		else {
			Rectangle(hdc, GetXPos() + 45 * Direction / 2, GetYPos() - 30, GetXPos() + (45 + Range * 60) * Direction / 2, GetYPos() + 30);
		}
		SelectObject(hdc, OldEBrush);
		SelectObject(hdc, OldEPen);
	}
}

void CreateLEnemy(LineEnemy** Lenemy) {

	LBrush1 = CreateSolidBrush(RGB(10, 10, 10));
	LBrush2 = CreateSolidBrush(RGB(150, 0, 0));
	LBrush3 = CreateHatchBrush(HS_FDIAGONAL, RGB(150, 0, 0));
	LPen1 = CreatePen(PS_SOLID, 1, RGB(50, 0, 0));
	LPen2 = CreatePen(PS_SOLID, 1, RGB(50, 0, 0));
	
	for (int i = 0; i < 80; i++) {
		if (i >= 0 && i < 20) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� ���� �� ����
				Lenemy[i] = new LineEnemy(150 + 60 * i, CTOPWALL + 45, 0, 0, 0, 1);
		}
		else if (i >= 20 && i < 40) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� ���� �� ����
				Lenemy[i] = new LineEnemy(CLEFTWALL + 45, 150 + 60 * (i - 20), 0, 0, 0, 2);
		}
		else if (i >= 40 && i < 60) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� ������ �� ����
				Lenemy[i] = new LineEnemy(CRIGHTWALL - 45, 150 + 60 * (i - 40), 0, 0, 0, -2);
		}
		else {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� �Ʒ��� �� ����
				Lenemy[i] = new LineEnemy(150 + 60 * (i - 60), CBOTTOMWALL - 45, 0, 0, 0, -1);
		}
	}
}

void DeleteLEnemy(LineEnemy** Lenemy) {
	DeleteObject(LBrush1);
	DeleteObject(LBrush2);
	DeleteObject(LPen1);
	DeleteObject(LPen2);

	for (int i = 0; i < 80; i++) {
		if (Lenemy[i] != NULL) {
			delete Lenemy[i];
			Lenemy[i] = NULL;
		}
	}
}

void SelectLShot(LineEnemy** Lenemy) {
	//LineEnemy�� 0~79�� 1���� �����Ѵ�.
	while (1) {
		int Num = rand() % 80;
		if (Lenemy[Num]->GetDelay() == 0) {
			//Delay�� 0�ϰ�츸 �����Ѵ�.
			//0�� �ƴϸ� �̹� ���õ� �༮�̶� �ٽ� �����ϸ� �ȵǱ� ������

			//Delay�� �����Ѵ�.
			Lenemy[Num]->SetDelay();
			//Range�� �����Ѵ�.
			Lenemy[Num]->SetRange();

			return;
		}
	}
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

BombEnemy::BombEnemy(int X, int Y, int C, int D, int DX, int DY) : Enemy(X, Y, C, D), DXPos(DX), DYPos(DY) {

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

RectEnemy::RectEnemy(int X, int Y, int C, int D, int DX, int DY, int Co) : BombEnemy(X, Y, C, D, DX, DY), Count(Co) {

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



void CreateWEnemy(WideEnemy** Wenemy) {

}

void CreateBEnemy(BombEnemy** Benemy) {

}

void CreateREnemy(RectEnemy** Renemy) {

}