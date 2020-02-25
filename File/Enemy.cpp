#include "Resource.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


//기본 에너미

Enemy::Enemy(int X, int Y, int C, int D) : XPos(X), YPos(Y), Charging(C), Delay(D) {

}

const int Enemy::GetXPos() const {
	//XPos값을 반환한다.
	return XPos;
}

const int Enemy::GetYPos() const {
	//YPos값을 반환한다.
	return YPos;
}

const int Enemy::GetCharging() const {
	//Charging값을 반환한다.
	return Charging;
}

const int Enemy::GetDelay() const {
	//Delay값을 반환한다.
	return Delay;
}

void Enemy::SetCharging() {
	//Charging값을 15로 지정한다.
	Charging = 15;
}

void Enemy::ChangeCharging() {
	//Charging이 0보다 크다면 1씩 감소시킨다.
	if (Charging > 0) {
		Charging--;
		//만약 Charging이 0이 된다면 Delay를 0으로 만들어준다.
		if (Charging == 0)
			Delay = 0;
	}
}

void Enemy::SetDelay() {
	//11~21(실제는 10~20)까지의 Delay타임 게임시간으로 1.0초~ 2.0초를 뜻함.
	Delay = rand() % 11 + 11;
}

void Enemy::ChangeDelay() {
	//Delay가 1보다 크다면 1씩 감소시킨다.
	if (Delay > 1) {
		Delay--;
		//만약 Delay가 1이라면 Charging을 세팅해준다.
		if (Delay == 1)
			SetCharging();
	}
		
}




//직선포 에너미

LineEnemy::LineEnemy(int X, int Y, int C, int D, int R, int Di) : Enemy(X, Y, C, D), Range(R), Direction(Di){

}

const int LineEnemy::GetRange() const {
	//Range 값을 반환한다.
	return Range;
}

const int LineEnemy::GetDirection() const {
	//Direction값을 반환한다.
	return Direction;
}

void LineEnemy::SetRange() {
	if ((GetXPos() > LLEFTWALL&& GetXPos() < LRIGHTWALL) || (GetYPos() > LTOPWALL&& GetYPos() < LBOTTOMWALL)) {
		//직선포의 발사 범위가 중간 섬에 겹칠 경우
		//범위를 6~8으로 설정한다.
		Range = rand() % 3 + 6;
	}
	else {
		//겹치지 않는 경우
		//범위를 11~20으로 설정한다
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
		//발사 중이라면
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}
	else {
		//발사 중이 아니라면
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush1);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}

	if (abs(Direction) == 1) {
		//위쪽 포일경우 , //아래쪽 포일경우
		POINT Pos[4] = { {GetXPos() - 20,GetYPos() - 20 * Direction},{GetXPos() + 20,GetYPos() - 20 * Direction},{GetXPos() + 10,GetYPos() + 35 * Direction},{GetXPos() - 10,GetYPos() + 35 * Direction} };

		Ellipse(hdc, GetXPos() - 20, GetYPos() - 40 * Direction, GetXPos() + 20, GetYPos());
		Polygon(hdc, Pos, 4);
		RoundRect(hdc, GetXPos() - 13, GetYPos() + 32 * Direction, GetXPos() + 13, GetYPos() + 38 * Direction, 6, 6);
	
	}
	else {
		//왼쪽 포일경우, //오른쪽 포일경우
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
		//발사 딜레이 0이 아닐때 
		if (this->GetCharging() != 0) {
			//발사 중일때 
			//즉 Delay가 1이고 Charging도 1이상일때
			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
			OldEPen = (HPEN)SelectObject(hdc, LPen1);
		}
		else {
			//발사 대기중일때 
			//즉 Delay가 1이상이고 Charging은 0일때
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
				//Lenemy[i]가 NULL이면 위쪽 포 생성
				Lenemy[i] = new LineEnemy(150 + 60 * i, CTOPWALL + 45, 0, 0, 0, 1);
		}
		else if (i >= 20 && i < 40) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 왼쪽 포 생성
				Lenemy[i] = new LineEnemy(CLEFTWALL + 45, 150 + 60 * (i - 20), 0, 0, 0, 2);
		}
		else if (i >= 40 && i < 60) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 오른쪽 포 생성
				Lenemy[i] = new LineEnemy(CRIGHTWALL - 45, 150 + 60 * (i - 40), 0, 0, 0, -2);
		}
		else {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 아래쪽 포 생성
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
	//LineEnemy인 0~79중 1개를 선택한다.
	while (1) {
		int Num = rand() % 80;
		if (Lenemy[Num]->GetDelay() == 0) {
			//Delay가 0일경우만 실행한다.
			//0이 아니면 이미 선택된 녀석이라 다시 선택하면 안되기 때문에

			//Delay를 지정한다.
			Lenemy[Num]->SetDelay();
			//Range를 지정한다.
			Lenemy[Num]->SetRange();

			return;
		}
	}
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

BombEnemy::BombEnemy(int X, int Y, int C, int D, int DX, int DY) : Enemy(X, Y, C, D), DXPos(DX), DYPos(DY) {

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

RectEnemy::RectEnemy(int X, int Y, int C, int D, int DX, int DY, int Co) : BombEnemy(X, Y, C, D, DX, DY), Count(Co) {

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



void CreateWEnemy(WideEnemy** Wenemy) {

}

void CreateBEnemy(BombEnemy** Benemy) {

}

void CreateREnemy(RectEnemy** Renemy) {

}