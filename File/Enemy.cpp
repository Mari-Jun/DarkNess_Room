#include "Resource.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


//기본 에너미

Enemy::Enemy(int C, int D) : Charging(C), Delay(D) {

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
	//Charging값을 10으로 지정한다.
	Charging = 11;
}

bool Enemy::ChangeCharging() {
	//Charging이 0보다 크다면 1씩 감소시킨다.
	if (Charging > 0) {
		
		Charging--;

		if (Charging == 0) {
			//만약 Charging이 0이 된다면 Delay를 0으로 만들어준다.
			Delay = 0;
			//발사 시간이 끝난 상태임으로 true를 반환
			return true;
		}
		return false;
	}
	//아직 발사시간임으로 false를 반환
	return false;

}

void Enemy::SetDelay(int D) {
	//적의 종류마다 Delay가 달라야함으로 변수 D를 입력시킨다.
	Delay = D;
}

bool Enemy::ChangeDelay() {
	//Delay가 1보다 크다면 1씩 감소시킨다.
	if (Delay > 1) {
		Delay--;
		//만약 Delay가 1이라면 Charging을 세팅해준다.
		if (Delay == 1) {
			SetCharging();
		}
		return true;
	}
	else if (Delay == 1)
		//Delay가 1이면 발사중이기 때문에
		return true;
	return false;
}

//고정 에너미

FixEnemy::FixEnemy(int C, int D, int X, int Y) : Enemy(C, D), XPos(X), YPos(Y) {

}

const int FixEnemy::GetXPos() const {
	//XPos값을 반환한다.
	return XPos;
}

const int FixEnemy::GetYPos() const {
	//YPos값을 반환한다.
	return YPos;
}


//이동 에너미

MoveEnemy::MoveEnemy(int C, int D, int X, int Y) : Enemy(C, D), XPos(X), YPos(Y) {

}

const int MoveEnemy::GetXPos() const {
	//XPos값을 반환한다.
	return XPos;
}

const int MoveEnemy::GetYPos() const {
	//YPos값을 반환한다.
	return YPos;
}

void MoveEnemy::ChangeXPos(int X) {
	//XPos값을 변경한다.
	XPos = X;
}

void MoveEnemy::ChangeYPos(int Y) {
	//YPos값을 변경한다.
	YPos = Y;
}



//직선포 에너미

LineEnemy::LineEnemy(int C, int D, int X, int Y, int R, int Di) : FixEnemy(C, D, X, Y), Range(R), Direction(Di){

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
		//범위를 5~8으로 설정한다.
		Range = rand() % 4 + 5;
	}
	else {
		//겹치지 않는 경우
		//범위를 11~20으로 설정한다
		Range = rand() % 10 + 11;
	}
}

void LineEnemy::SetHitCheck(Player* player, const bool OnOff) const {
	//HitCheck를 설정한다.

	//HitCheck를 변경할 범위를 설정한다.
	int Left, Right, Top, Bottom;
	if (abs(Direction) == 1) {
		//위 아래 직선포일경우
		Left = (GetXPos() - 150) / 60;
		Right = (GetXPos() - 150) / 60;
		if (Direction == 1) {
			Top = 0;
			Bottom = Range - 1;
		}
		else {
			Top = 19 - Range + 1;
			Bottom = 19;
		}
	}
	else {
		//왼쪽 오른쪽 직선포일경우
		if (Direction == 2) {
			Left = 0;
			Right = Range - 1;
		}
		else {
			Left = 19 - Range + 1;
			Right = 19;
		}
		Top = (GetYPos() - 150) / 60;
		Bottom = (GetYPos() - 150) / 60;
	}

	//player의 SetHitCheck를 불러온다.
	player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
}


void LineEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {

	if (GetDelay() > 0 && GetDelay() < 12) {
		if (abs(Direction) == 1) {
			if (Direction == 1)
				SelectObject(Bithdc, LBitMap[0]);
			else
				SelectObject(Bithdc, LBitMap[3]);
			TransparentBlt(hdc, GetXPos() - 30, GetYPos() - 40, 60, 80, Bithdc, 0, 0, 60, 80, RGB(255, 255, 255));
		}

		if (abs(Direction) == 2) {
			if (Direction == 2)
				SelectObject(Bithdc, LBitMap[1]);
			else
				SelectObject(Bithdc, LBitMap[2]);
			TransparentBlt(hdc, GetXPos() - 40, GetYPos() - 30, 80, 60, Bithdc, 0, 0, 80, 60, RGB(255, 255, 255));
		}
	}
}

void LineEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {

	if (GetDelay() > 0 && GetDelay() < 12) {
		//발사 시작 시간이 0이 아닐때 
		if (GetCharging() != 0) {
			//발사 중일때 
			//즉 Delay가 1이고 Charging도 1이상일때

			if (abs(Direction) == 1) {
				//상하 발사 비트맵을 불러온다.
				SelectObject(Bithdc, LSBitMap[22 - GetCharging()]);
				if (Direction == 1) {
					//Range * 61인 이유는 *60을 하면 끝처리가 이상하게 나오기 때문이다.
					//600사이즈를 Range*60만큼의 사이즈로 늘려준다.
					StretchBlt(Bithdc2, 0, 0, 60, Range * 61, Bithdc, 0, 600, 60, -600, SRCCOPY);

					//배경색을 지워서 발사포를 출력해준다.
					TransparentBlt(hdc, GetXPos() - 30, GetYPos() + 45, 60, Range * 60, Bithdc2, 0, 0, 60, Range * 60, RGB(255, 255, 255));
				}
				else {
					StretchBlt(Bithdc2, 0, 0, 60, Range * 60, Bithdc, 0, 0, 60, 600, SRCCOPY);
					TransparentBlt(hdc, GetXPos() - 30, GetYPos() - 45 - (Range * 60), 60, Range * 60, Bithdc2, 0, 0, 60, Range * 60, RGB(255, 255, 255));
				}
			}
			else if (abs(Direction) == 2) {
				SelectObject(Bithdc, LSBitMap[11 - GetCharging()]);
				if (Direction == 2) {
					StretchBlt(Bithdc2, 0, 0, Range * 61, 60, Bithdc, 600, 0, -600, 60, SRCCOPY);
					TransparentBlt(hdc, GetXPos() + 45, GetYPos() - 30, Range * 60, 60, Bithdc2, 0, 0, Range * 60, 60, RGB(255, 255, 255));
				}
				else {
					StretchBlt(Bithdc2, 0, 0, Range * 60, 60, Bithdc, 0, 0, 600, 60, SRCCOPY);
					TransparentBlt(hdc, GetXPos() - 45 - (Range * 60), GetYPos() - 30, Range * 60, 60, Bithdc2, 0, 0, Range * 60, 60, RGB(255, 255, 255));
				}
			}
		}
		else {
			//발사 대기중일때 
			//즉 Delay가 1이상이고 Charging은 0일때

			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush);
			OldEPen = (HPEN)SelectObject(hdc, LPen);

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
}

void CreateLEnemy(LineEnemy** Lenemy) {

	for (int i = 0; i < 4; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\LineEnemy%d.bmp", i + 1);
		LBitMap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int i = 0; i < 22; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\LineShot%d.bmp", i + 1);
		LSBitMap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	LBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(100, 0, 0));
	LPen = CreatePen(PS_SOLID, 1, RGB(150, 0, 0));
	
	for (int i = 0; i < LENEMYMAX; i++) {
		if (i >= 0 && i < 20) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 위쪽 포 생성
				Lenemy[i] = new LineEnemy(0, 0, 150 + 60 * i, CTOPWALL + 45, 0, 1);
		}
		else if (i >= 20 && i < 40) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 왼쪽 포 생성
				Lenemy[i] = new LineEnemy(0, 0, CLEFTWALL + 45, 150 + 60 * (i - 20), 0, 2);
		}
		else if (i >= 40 && i < 60) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 오른쪽 포 생성
				Lenemy[i] = new LineEnemy(0, 0, CRIGHTWALL - 45, 150 + 60 * (i - 40), 0, -2);
		}
		else {
			if (Lenemy[i] == NULL)
				//Lenemy[i]가 NULL이면 아래쪽 포 생성
				Lenemy[i] = new LineEnemy(0, 0, 150 + 60 * (i - 60), CBOTTOMWALL - 45, 0, -1);
		}
	}
}

void DeleteLEnemy(LineEnemy** Lenemy) {
	DeleteObject(LBrush);
	DeleteObject(LPen);
	DeleteObject(LBitMap);

	for (int i = 0; i < LENEMYMAX; i++) {
		if (Lenemy[i] != NULL) {
			delete Lenemy[i];
			Lenemy[i] = NULL;
		}
	}
}

void SelectLShot(LineEnemy** Lenemy, const int WaitTime) {
	//LineEnemy인 0~79중 1개를 선택한다.
	while (1) {
		int Num = rand() % LENEMYMAX;
		if (Lenemy[Num]->GetDelay() == 0) {
			//Delay가 0일경우만 실행한다.
			//0이 아니면 이미 선택된 녀석이라 다시 선택하면 안되기 때문에

			//Delay를 11으로 지정한다.
			Lenemy[Num]->SetDelay(rand() % WaitTime + 11);
			//Range를 지정한다.
			Lenemy[Num]->SetRange();

			return;
		}
	}
}

int ChangeLInfo(LineEnemy** Lenemy, Player* player) {
	//Lenemy들을 검사해서 Delay값이 0이 아닌 녀석들 한해서 실행시킨다.

	int Count = 0;

	for (int i = 0; i < LENEMYMAX; i++) {
		if (Lenemy[i]->ChangeDelay()) {
			//ChangeDelay함수가 정상적으로 실행되었을 경우에만 실행한다.

			//발사 대기중이거나 발사중임으로 Count를 1증가 시킨다.
			Count++;

			if (Lenemy[i]->GetCharging() == 11) {
				//방금 충전이 됬을 경우
				//SetHitCheck를 호출한다.
				Lenemy[i]->SetHitCheck(player, true);
			}

			if (Lenemy[i]->ChangeCharging()) {
				//ChangeCharging()이 true(발사 종료)를 반환했을 경우에만 실행한다.

				//발사종료임으로 Count를 1감소 시킨다.
				Count--;

				//발사가 종료됬음으로
				//SetHitCheck를 호출한다.
				Lenemy[i]->SetHitCheck(player, false);
			}
		}
	}
	//Count값 (현재 실행되고 있는 LEnemy의 수)을 반환하여 LShot에게 적용시켜준다. 
	return Count;
}




//광역포 에너미

WideEnemy::WideEnemy(int C, int D, int X, int Y, int Di) : FixEnemy(C, D, X, Y), Direction(Di) {

}

const int WideEnemy::GetDirection() const {
	//Direction값을 반환한다.
	return  Direction;
}

void WideEnemy::SetDirection() {
	//Direction값을 설정한다. 1:왼쪽위, 2: 오른쪽 위, 3: 왼쪽아래, 4: 오른쪽아래
	Direction = rand() % 4 + 1;
}

void WideEnemy::SetHitCheck(Player* player, const bool OnOff) const {
	//HitCheck를 설정한다.

	//HitCheck를 변경할 범위를 설정한다.
	int Left, Right, Top, Bottom;

	//각각 설정한다.
	Left = 10 * (1 - Direction % 2);
	Right = 10 * (1 - Direction % 2) +9;
	Top = 10 * (Direction / 3);
	Bottom = 10 * (Direction / 3) + 9;

	//player의 SetHitCheck를 불러온다.
	player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
}

void WideEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	if (GetCharging() == 0)
		//Charging되지 않은 상태
		SelectObject(Bithdc, WEBitmap1);
	else
		//Charging이 되있는 상태
		SelectObject(Bithdc, WEBitmap2);

	TransparentBlt(hdc, GetXPos() - 45, GetYPos() - 45, 90, 90, Bithdc, 0, 0, 90, 90, RGB(0, 0, 0));
}

void WideEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//발사 중이거나 발사 대기중일때 작동
		if (GetCharging() == 0) {
			//발사 대기중이라면
			OldEBrush = (HBRUSH)SelectObject(hdc, WSBrush); 
			OldEPen = (HPEN)SelectObject(hdc, WSPen);

			POINT Pos[6];
			//각 방향별로 Pos값을 다르게 설정
			if (Direction == 1) {
				Pos[0] = { LEFTWALL,TOPWALL };
				Pos[1] = { (LEFTWALL + RIGHTWALL) / 2,TOPWALL };
				Pos[2] = { (LEFTWALL + RIGHTWALL) / 2, LTOPWALL };
				Pos[3] = { LLEFTWALL,LTOPWALL };
				Pos[4] = { LLEFTWALL,(TOPWALL + BOTTOMWALL) / 2 };
				Pos[5] = { LEFTWALL,(TOPWALL + BOTTOMWALL) / 2 };
			}
			else if (Direction == 2) {
				Pos[0] = { RIGHTWALL,TOPWALL };
				Pos[1] = { (LEFTWALL + RIGHTWALL) / 2,TOPWALL };
				Pos[2] = { (LEFTWALL + RIGHTWALL) / 2, LTOPWALL };
				Pos[3] = { LRIGHTWALL,LTOPWALL };
				Pos[4] = { LRIGHTWALL,(TOPWALL + BOTTOMWALL) / 2 };
				Pos[5] = { RIGHTWALL,(TOPWALL + BOTTOMWALL) / 2 };
			}
			else if (Direction == 3) {
				Pos[0] = { LEFTWALL,BOTTOMWALL };
				Pos[1] = { (LEFTWALL + RIGHTWALL) / 2,BOTTOMWALL };
				Pos[2] = { (LEFTWALL + RIGHTWALL) / 2, LBOTTOMWALL };
				Pos[3] = { LLEFTWALL,LBOTTOMWALL };
				Pos[4] = { LLEFTWALL,(TOPWALL + BOTTOMWALL) / 2 };
				Pos[5] = { LEFTWALL,(TOPWALL + BOTTOMWALL) / 2 };
			}
			else {
				Pos[0] = { RIGHTWALL,BOTTOMWALL };
				Pos[1] = { (LEFTWALL + RIGHTWALL) / 2,BOTTOMWALL };
				Pos[2] = { (LEFTWALL + RIGHTWALL) / 2, LBOTTOMWALL };
				Pos[3] = { LRIGHTWALL,LBOTTOMWALL };
				Pos[4] = { LRIGHTWALL,(TOPWALL + BOTTOMWALL) / 2 };
				Pos[5] = { RIGHTWALL,(TOPWALL + BOTTOMWALL) / 2 };
			}
			//폴리곤으로 그리기
			Polygon(hdc, Pos, 6);

			SelectObject(hdc, OldEBrush);
			SelectObject(hdc, OldEPen);

		}
		else {
			//발사중이라면
			if (GetCharging() > 2 && GetCharging() < 10) {
				SelectObject(Bithdc, WSBitmap[9 - GetCharging()]);
				if (Direction == 1)
					TransparentBlt(hdc, LEFTWALL, TOPWALL, 600, 600, Bithdc, 0, 0, 600, 600, RGB(255, 255, 255));
				else if (Direction == 2)
					TransparentBlt(hdc, LEFTWALL + 600, TOPWALL, 600, 600, Bithdc, 0, 0, 600, 600, RGB(255, 255, 255));
				else if (Direction == 3)
					TransparentBlt(hdc, LEFTWALL, TOPWALL + 600, 600, 600, Bithdc, 0, 0, 600, 600, RGB(255, 255, 255));
				else
					TransparentBlt(hdc, LEFTWALL + 600, TOPWALL + 600, 600, 600, Bithdc, 0, 0, 600, 600, RGB(255, 255, 255));
			}
		}
	}
}

void CreateWEnemy(WideEnemy** Wenemy) {

	//WideEnemyShotBrush, Pen (으)로 적의 포 색을 표현함.
	WSBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(178, 235, 244));
	WSPen = CreatePen(PS_SOLID, 1, RGB(92, 209, 229));


	//WideEnemy에서 사용될 Bitmap들을 불러온다.
	WEBitmap1 = (HBITMAP)LoadImage(NULL, L".\\BitMap\\WideEnemy1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	WEBitmap2 = (HBITMAP)LoadImage(NULL, L".\\BitMap\\WideEnemy2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	for (int i = 0; i < 7; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\WideShot%d.bmp", i + 1);
		WSBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	if (*Wenemy == NULL) {
		//*Wenemy가 NULL일때 작동
		//WideEnemy는 1개이다.
		*Wenemy = new WideEnemy(0, 0, (LLEFTWALL + LRIGHTWALL) / 2, (LTOPWALL + LBOTTOMWALL) / 2, 0);
	}
}

void DeleteWEnemy(WideEnemy** Wenemy) {
	if (*Wenemy != NULL) {
		delete* Wenemy;
		*Wenemy = NULL;

		DeleteObject(WSBrush);
		DeleteObject(WSPen);
		DeleteObject(WEBitmap1);
		DeleteObject(WEBitmap2);
	}
}

void ChangeWInfo(WideEnemy* Wenemy, Player* player, const int WaitTime) {

	if (Wenemy->GetDelay() == 0) {
			//방향 선택
			Wenemy->SetDirection();
			//발사 대기 시간 설정
			Wenemy->SetDelay(WaitTime + 11);
	}
	else {
		//발사 대기중이거나 발사중인 경우

		//Delay값 변경
		Wenemy->ChangeDelay();

		if(Wenemy->GetCharging() == 11) {
			//방금 충전이 됬을 경우
			//SetHitCheck를 호출한다.
			Wenemy->SetHitCheck(player, true);
		}

		if (Wenemy->ChangeCharging()) {
			//ChangeCharging()이 true(발사 종료)를 반환했을 경우에만 실행한다.

			//발사가 종료됬음으로
			//SetHitCheck를 호출한다.
			Wenemy->SetHitCheck(player, false);
		}
	}
}


//폭탄 에너미

BombEnemy::BombEnemy(int C, int D, int X, int Y) : MoveEnemy(X, Y, C, D){

}

void BombEnemy::SetHitCheck(Player* player, const bool OnOff) const {
	//HitCheck를 설정한다.

	//HitCheck를 변경할 범위를 설정한다.
	int Left, Right, Top, Bottom;

	//좌우 -> 위아래 순으로 처리
	for (int i = 0; i < 2; i++) {
		Left = GetXPos() - (2 - i);
		Right = GetXPos() + (2 - i);
		Top = GetYPos() - (1 + i);
		Bottom = GetYPos() + (1 + i);
		
		//player의 SetHitCheck를 불러온다.
		player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
	}
}

void BombEnemy::SetDropPos() {
	while (1) {
		//위,아래,좌,우로 최소한 2칸씩은 남겨놓아야 한다.
		ChangeXPos(rand() % 16 + 2);
		ChangeYPos(rand() % 16 + 2);

		//중간섬 에서도 당연히 2칸씩은 띄워주어야 한다.
		if ((GetXPos() < 6 || GetXPos() > 13) || (GetYPos() < 6 || GetYPos() > 13))
			break;
	}
}

void BombEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	//BombEnemy를 그린다.
	if (GetDelay() > 0 && GetDelay() < 12) {
		//폭탄이 떨어진 상태

		if (GetCharging() == 0) {
			//폭파 대기 상태
			//폭탄 그리기
			SelectObject(Bithdc, BBitmap);
			TransparentBlt(hdc, LEFTWALL + GetXPos() * 60, TOPWALL + GetYPos() * 60, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		}
	}
}

void BombEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//폭탄이 떨어진 후를 뜻함.
		//Delay12 이하인 이유는 불규칙 적인 폭탄을 구현하고 싶어서 저렇게 설정해주었다.

		//Brush와 Pen 선택
		OldEBrush = (HBRUSH)SelectObject(hdc, BBrush);
		OldEPen = (HPEN)SelectObject(hdc, BPen);

		if (GetCharging() == 0) {
			//폭파 대기상태

			//폭탄 범위 그리기
			Rectangle(hdc, LEFTWALL + (GetXPos() - 2) * 60, TOPWALL + (GetYPos() - 1) * 60, LEFTWALL + (GetXPos() + 3) * 60, TOPWALL + (GetYPos() + 2) * 60);
			Rectangle(hdc, LEFTWALL + (GetXPos() - 1) * 60, TOPWALL + (GetYPos() - 2) * 60, LEFTWALL + (GetXPos() + 2) * 60, TOPWALL + (GetYPos() + 3) * 60);
		}
		else {
			//폭파상태
			SelectObject(Bithdc, EXBitmap[11 - GetCharging()]);
			TransparentBlt(hdc, LEFTWALL + (GetXPos()-2) * 60, TOPWALL + (GetYPos()-2) * 60, 300, 300, Bithdc, 0, 0, 300, 300, RGB(255, 255, 255));
		}

		SelectObject(hdc, OldEBrush);
		SelectObject(hdc, OldEPen);
	}
}

void CreateBEnemy(BombEnemy** Benemy) {

	BBitmap = (HBITMAP)LoadImage(NULL, L".\\BitMap\\Bomb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	for (int i = 0; i < 11; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\BombEX%d.bmp", i);
		EXBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
		

	BBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(150, 150, 150));
	BPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));

	for (int i = 0; i < BENEMYMAX; i++) {
		//Benemy[i]가 NULL이면 생성
		if (Benemy[i] == NULL) {
			Benemy[i] = new BombEnemy(0, 0, 0, 0);
		}
	}
}

void DeleteBEnemy(BombEnemy** Benemy) {

	DeleteObject(BBitmap);

	for (int i = 0; i < BENEMYMAX; i++) {
		//Benemy[i]가 NULL이 아닐 경우
		if (Benemy[i] != NULL) {
			delete Benemy[i];
			Benemy[i] = NULL;
		}
	}
}

void SelectBShot(BombEnemy** Benemy, const int WaitTime) {

	while (1) {
		int Num = rand() % BENEMYMAX;
		if (Benemy[Num]->GetDelay() == 0) {
			//Delay가 0일경우만 실행한다.
			//0이 아니면 이미 선택된 녀석이라 다시 선택하면 안되기 때문에

			//최소 11  최대 11 + WaitTime만큼의 범위
			Benemy[Num]->SetDelay(rand() % WaitTime + 11);
			//DropPos를 지정한다.
			Benemy[Num]->SetDropPos();
			return;
		}
	}
}

int ChangeBInfo(BombEnemy** Benemy, Player* player) {
	//Benemy들을 검사해서 Delay값이 0이 아닌 녀석들 한해서 실행시킨다.

	int Count = 0;

	for (int i = 0; i < BENEMYMAX; i++) {
		if (Benemy[i]->ChangeDelay()) {
			//ChangeDelay함수가 정상적으로 실행되었을 경우에만 실행한다.

			//발사 대기중이거나 발사중임으로 Count를 1증가 시킨다.
			Count++;

			if (Benemy[i]->GetCharging() == 11) {
				//방금 충전이 됬을 경우
				//SetHitCheck를 호출한다.
				Benemy[i]->SetHitCheck(player, true);
			}

			if (Benemy[i]->ChangeCharging()) {
				//ChangeCharging()이 true(발사 종료)를 반환했을 경우에만 실행한다.

				//발사종료임으로 Count를 1감소 시킨다.
				Count--;

				//발사가 종료됬음으로
				//SetHitCheck를 호출한다.
				Benemy[i]->SetHitCheck(player, false);
			}
		}
	}
	//Count값 (현재 실행되고 있는 LEnemy의 수)을 반환하여 LShot에게 적용시켜준다. 
	return Count;
}



//범위포 에너미

AirEnemy::AirEnemy(int C, int D, int X, int Y, int DX, int DY) : MoveEnemy(C, D, X, Y), DXPos(DX), DYPos(DY) {

}

const int AirEnemy::GetDXPos() const {
	//DXPos값을 반환한다.
	return DXPos;	
}

const int AirEnemy::GetDYPos() const {
	//DYPos값을 반환한다.
	return DYPos;
}

void AirEnemy::SetDropPos(Player* player) {

	//현재 플레이어가 있는 곳을 타격 위치로 설정한다.
	DXPos = (player->GetXPos() - 120) / 60;
	DYPos = (player->GetYPos() - 120) / 60;


	//모서리에 있을 경우 폭파 범위 설정을 위해 DXPos값, DYPos값을 변경해준다.
	if (DXPos == 0)
		DXPos++;
	if (DYPos == 0)
		DYPos++;
	if (DXPos == 19)
		DXPos--;
	if (DYPos == 19)
		DYPos--;

	//중간섬도 적용된다.
	if (DXPos == 7 && DYPos > 7 && DYPos < 12)
		DXPos--;
	if (DXPos == 12 && DYPos > 7 && DYPos < 12)
		DXPos++;
	if (DYPos == 7 && DXPos > 7 && DXPos < 12)
		DYPos--;
	if (DYPos == 12 && DXPos > 7 && DXPos < 12)
		DYPos++;
	
}


void AirEnemy::SetHitCheck(Player* player, const bool OnOff) const {

	//HitCheck를 설정한다.

	//HitCheck를 변경할 범위를 설정한다.
	int Left, Right, Top, Bottom;
	Left = DXPos - 1;
	Right = DXPos + 1;
	Top = DYPos - 1;
	Bottom = DYPos + 1;

	player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
}

void AirEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//발사 신호일 때 작동한다.

		SelectObject(Bithdc, ABitmap);

		TransparentBlt(hdc, GetXPos() - 30, GetYPos() - 30, 120, 120, Bithdc, 0, 0, 120, 120, RGB(255, 255, 255));
	}
}

void AirEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//비행기가 출발했거나 폭탄이 터져있는 상태를 뜻한다.
		if (GetCharging() == 0) {
			//아직 터진 상태가 아닐때
			OldEBrush = (HBRUSH)SelectObject(hdc, ABrush);
			OldEPen = (HPEN)SelectObject(hdc, APen);

			//3*3모양의 직사각형을 그린다.
			Rectangle(hdc, LEFTWALL + (DXPos - 1) * 60, TOPWALL + (DYPos - 1) * 60, LEFTWALL + (DXPos + 2) * 60, TOPWALL + (DYPos + 2) * 60);

			SelectObject(hdc, OldEBrush);
			SelectObject(hdc, OldEPen);

		}
		else {
			//터진 상태일때
			SelectObject(Bithdc, ASBitmap[11 - GetCharging()]);
			TransparentBlt(hdc, LEFTWALL + (DXPos - 1) * 60, TOPWALL + (DYPos - 1) * 60, 180, 180, Bithdc, 0, 0, 180, 180, RGB(255, 255, 255));
		}
	}
}

void CreateAEnemy(AirEnemy** Aenemy) {

	//AirEnemy를 불러온다.
	ABitmap = (HBITMAP)LoadImage(NULL, L".\\BitMap\\AirPlane1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//AirEnemy샷을 불러온다.
	for (int i = 0; i < 11; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\AirShot%d.bmp", i);
		ASBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	ABrush = CreateHatchBrush(HS_FDIAGONAL, RGB(250, 237, 125));
	APen = CreatePen(PS_SOLID, 1, RGB(232, 229, 109));

	for (int i = 0; i < AENEMYMAX; i++) {
		if (Aenemy[i] == NULL) {
			//Aenemy[i]가 NULL일때만 작동한다.
			Aenemy[i] = new AirEnemy(0, 0, 0, 0, 0, 0);
		}
	}
}

void DeleteAEnemy(AirEnemy** Aenemy) {


	for(int i=0; i<AENEMYMAX; i++)
		if (Aenemy[i] != NULL) {
			//Aenemy[i]가 NULL이 아닐경우 작동
			delete Aenemy[i];
			Aenemy[i] = NULL;
		}
}

void SelectAShot(AirEnemy** Aenemy, Player* player, const int WaitTime) {
	while (1) {
		int Num = rand() % AENEMYMAX;
		if (Aenemy[Num]->GetDelay() == 0) {
			//Delay가 0일경우만 실행한다.
			//0이 아니면 이미 선택된 녀석이라 다시 선택하면 안되기 때문에

			//최소 12 최대 12+ WaitTime만큼의 범위
			Aenemy[Num]->SetDelay(rand() % WaitTime + 12);

			return;
		}
	}
}

int ChangeAInfo(AirEnemy** Aenemy, Player* player) {
	//Benemy들을 검사해서 Delay값이 0이 아닌 녀석들 한해서 실행시킨다.

	int Count = 0;

	for (int i = 0; i < AENEMYMAX; i++) {
		if (Aenemy[i]->ChangeDelay()) {
			//ChangeDelay함수가 정상적으로 실행되었을 경우에만 실행한다.

			//발사 대기중이거나 발사중임으로 Count를 1증가 시킨다.
			Count++;

			if (Aenemy[i]->GetDelay() == 11) {
				//발사 준비 완료 되었다면 즉 폭파범위가 나올때라면
				//DropPos를 지정한다.
				Aenemy[i]->SetDropPos(player);
			}


			if (Aenemy[i]->GetCharging() == 0) {
				//아직 폭파가 안된 상태

				//비행기의 XPos값과 YPos값을 변경한다.
				Aenemy[i]->ChangeXPos((LEFTWALL + Aenemy[i]->GetDXPos() * 60) / 10 * (11 - Aenemy[i]->GetDelay()));
				Aenemy[i]->ChangeYPos(TOPWALL + Aenemy[i]->GetDYPos() * 60);
	
			}
			else {
				//폭파중인 상태

				//비행기의 XPos값과 YPos값을 변경한다.
				Aenemy[i]->ChangeXPos(LEFTWALL + Aenemy[i]->GetDXPos() * 60 + (ALLMAPX - (LEFTWALL + Aenemy[i]->GetDXPos() * 60)) / 10 * (11 - Aenemy[i]->GetCharging()));
				Aenemy[i]->ChangeYPos(TOPWALL + Aenemy[i]->GetDYPos() * 60);
			}

			if (Aenemy[i]->GetCharging() == 11) {
				//방금 충전이 됬을 경우
				//SetHitCheck를 호출한다.
				Aenemy[i]->SetHitCheck(player, true);
			}

			if (Aenemy[i]->ChangeCharging()) {
				//ChangeCharging()이 true(발사 종료)를 반환했을 경우에만 실행한다.

				//발사종료임으로 Count를 1감소 시킨다.
				Count--;

				//발사가 종료됬음으로
				//SetHitCheck를 호출한다.
				Aenemy[i]->SetHitCheck(player, false);
			}
		}
	}
	//Count값 (현재 실행되고 있는 LEnemy의 수)을 반환하여 LShot에게 적용시켜준다. 
	return Count;
}