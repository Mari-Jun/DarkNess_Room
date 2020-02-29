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
		//범위를 5~8으로 설정한다.
		Range = rand() % 4 + 5;
	}
	else {
		//겹치지 않는 경우
		//범위를 11~20으로 설정한다
		Range = rand() % 10 + 11;
	}
}

void LineEnemy::SetHitCheck(Player* player, bool OnOff) {
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

	if (this->GetDelay() != 0) {
		if (abs(Direction) == 1) {
			if (Direction == 1)
				SelectObject(Bithdc, LBitMap[0]);
			else
				SelectObject(Bithdc, LBitMap[3]);
			TransparentBlt(hdc, GetXPos() - 30, GetYPos() - 40, 60, 80, Bithdc, 0, 0, 60, 80, RGB(255, 255, 255));
		}

		if (abs(Direction == 2)) {
			if (Direction == 2)
				SelectObject(Bithdc, LBitMap[1]);
			else
				SelectObject(Bithdc, LBitMap[2]);
			TransparentBlt(hdc, GetXPos() - 40, GetYPos() - 30, 80, 60, Bithdc, 0, 0, 80, 60, RGB(255, 255, 255));
		}
	}

	/*if (this->GetCharging() != 0) {
		//발사 중이라면
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}
	else {
		//발사 중이 아니라면
		if(GetDelay()==0)
			LBrush1 = CreateSolidBrush(RGB(10, 10, 10));
		else
			LBrush1 = CreateSolidBrush(RGB((10 - GetDelay()) * 15, 10, 10));
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
	
	DeleteObject(LBrush1);
	SelectObject(hdc, OldEBrush);
	SelectObject(hdc, OldEPen);*/
}

void LineEnemy::PaintShot(HDC hdc, HDC Bithdc) const{

	if (GetDelay() != 0) {
		//발사 시작 시간이 0이 아닐때 
		if (GetCharging() != 0) {
			//발사 중일때 
			//즉 Delay가 1이고 Charging도 1이상일때
			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
			OldEPen = (HPEN)SelectObject(hdc, LPen2);
		}
		else {
			//발사 대기중일때 
			//즉 Delay가 1이상이고 Charging은 0일때
			SetBkMode(hdc, TRANSPARENT);
			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush3);
			OldEPen = (HPEN)SelectObject(hdc, LPen2);
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

	for (int i = 0; i < 4; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\LineEnemy%d.bmp", i + 1);
		LBitMap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	LBrush2 = CreateSolidBrush(RGB(152, 10, 10));
	LBrush3 = CreateHatchBrush(HS_FDIAGONAL, RGB(100, 0, 0));
	LPen1 = CreatePen(PS_SOLID, 1, RGB(50, 0, 0));
	LPen2 = CreatePen(PS_SOLID, 1, RGB(150, 0, 0));
	
	for (int i = 0; i < LENEMYMAX; i++) {
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
	DeleteObject(LBrush3);
	DeleteObject(LPen1);
	DeleteObject(LPen2);
	DeleteObject(LPen3);
	DeleteObject(LBitMap);

	for (int i = 0; i < LENEMYMAX; i++) {
		if (Lenemy[i] != NULL) {
			delete Lenemy[i];
			Lenemy[i] = NULL;
		}
	}
}

void SelectLShot(LineEnemy** Lenemy) {
	//LineEnemy인 0~79중 1개를 선택한다.
	while (1) {
		int Num = rand() % LENEMYMAX;
		if (Lenemy[Num]->GetDelay() == 0) {
			//Delay가 0일경우만 실행한다.
			//0이 아니면 이미 선택된 녀석이라 다시 선택하면 안되기 때문에

			//Delay를 11으로 지정한다.
			Lenemy[Num]->SetDelay(11);
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

WideEnemy::WideEnemy(int X, int Y, int C, int D, int Di) : Enemy(X, Y, C, D), Direction(Di) {

}

const int WideEnemy::GetDirection() const {
	//Direction값을 반환한다.
	return  Direction;
}

void WideEnemy::SetDirection() {
	//Direction값을 설정한다. 1:왼쪽위, 2: 오른쪽 위, 3: 왼쪽아래, 4: 오른쪽아래
	Direction = rand() % 4 + 1;
}

void WideEnemy::SetHitCheck(Player* player, bool OnOff) {
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

void WideEnemy::PaintShot(HDC hdc, HDC Bithdc) const {
	if (GetDelay() != 0) {
		//발사 중이거나 발사 대기중일때 작동
		if (GetCharging() == 0) {
			//발사 대기중이라면
			SetBkMode(hdc, TRANSPARENT);
			OldEBrush = (HBRUSH)SelectObject(hdc, WSBrush2); 
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
	WSBrush1 = CreateSolidBrush(RGB(250, 237, 125));
	WSBrush2 = CreateHatchBrush(HS_FDIAGONAL, RGB(250, 237, 125));
	WSPen = CreatePen(PS_SOLID, 1, RGB(196, 183, 59));


	//WideEnemy에서 사용될 Bitmap들을 불러온다.
	WEBitmap1 = (HBITMAP)LoadImage(NULL, L".\\BitMap\\WideEnemy1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	WEBitmap2 = (HBITMAP)LoadImage(NULL, L".\\BitMap\\WideEnemy2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	for (int i = 0; i < 7; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\WideShot%d.bmp", i + 1);
		WSBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	if (*Wenemy == NULL) {
		//*Wenemy가 NULL일때 작동
		//WideEnemy는 1개이다.
		*Wenemy = new WideEnemy((LLEFTWALL + LRIGHTWALL) / 2, (LTOPWALL + LBOTTOMWALL) / 2, 0, 0, 0);
	}
}

void DeleteWEnemy(WideEnemy** Wenemy) {
	if (*Wenemy != NULL) {
		delete* Wenemy;
		*Wenemy = NULL;

		DeleteObject(WSBrush1);
		DeleteObject(WSBrush2);
		DeleteObject(WSPen);
		DeleteObject(WEBitmap1);
		DeleteObject(WEBitmap2);
	}
}

void ChangeWInfo(WideEnemy* Wenemy, Player* player) {
	static int Wait = 0;
	if (Wenemy->GetDelay() == 0) {
		//Delay가 0인 상태인 경우
		Wait++;
		if (Wait == 40) {
			//발사 쿨다운 설정
			//즉 4초+1초마다 발사된다.
			
			//방향 선택
			Wenemy->SetDirection();
			//발사 대기 시간 설정
			Wenemy->SetDelay(11);

			//다시 쿨다운을 돌리기 위해 0으로 설정
			Wait = 0;
		}
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

void BombEnemy::SetHitCheck(Player* player, bool OnOff) {
	//HitCheck를 설정한다.

	//HitCheck를 변경할 범위를 설정한다.
	int Left, Right, Top, Bottom;

	//좌우 -> 위아래 순으로 처리
	for (int i = 0; i < 2; i++) {
		Left = DXPos - (2 - i);
		Right = DXPos + (2 - i);
		Top = DYPos - (1 + i);
		Bottom = DYPos + (1 + i);
		
		//player의 SetHitCheck를 불러온다.
		player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
	}
}

void BombEnemy::SetDropPos() {
	while (1) {
		//위,아래,좌,우로 최소한 2칸씩은 남겨놓아야 한다.
		DXPos = rand() % 16 + 2;
		DYPos = rand() % 16 + 2;

		//중간섬 에서도 당연히 2칸씩은 띄워주어야 한다.
		if ((DXPos < 6 || DXPos > 13) && (DYPos < 6 || DXPos > 13))
			break;
	}
}

void BombEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	//일단 Enemy그리기는 나중에 하자.
}

void BombEnemy::PaintShot(HDC hdc, HDC Bithdc) const {
	if (GetDelay() != 0) {
		//폭탄이 떨어진 후를 뜻함.

		//Brush와 Pen 선택
		OldEBrush = (HBRUSH)SelectObject(hdc, BBrush1);
		OldEPen = (HPEN)SelectObject(hdc, BPen1);

		if (GetCharging() == 0) {
			//폭파 대기상태

			//폭탄 범위 그리기
			Rectangle(hdc, LEFTWALL + (DXPos - 2) * 60, TOPWALL + (DYPos - 1) * 60, LEFTWALL + (DXPos + 3) * 60, TOPWALL + (DYPos + 2) * 60);
			Rectangle(hdc, LEFTWALL + (DXPos - 1) * 60, TOPWALL + (DYPos - 2) * 60, LEFTWALL + (DXPos + 2) * 60, TOPWALL + (DYPos + 3) * 60);

			//폭탄 그리기
			SelectObject(Bithdc, BBitmap);
			TransparentBlt(hdc, LEFTWALL + DXPos * 60, TOPWALL + DYPos * 60, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		}
		else {
			//폭파상태
			SelectObject(Bithdc, EXBitmap[11 - GetCharging()]);
			TransparentBlt(hdc, LEFTWALL + (DXPos-2) * 60, TOPWALL + (DYPos-2) * 60, 300, 300, Bithdc, 0, 0, 300, 300, RGB(255, 255, 255));
		}

		SelectObject(hdc, OldEBrush);
		SelectObject(hdc, OldEPen);
	}
}

void CreateBEnemy(BombEnemy** Benemy) {

	BBitmap = (HBITMAP)LoadImage(NULL, L".\\BitMap\\Bomb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	for (int i = 0; i < 11; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\BombEX%d.bmp", i);
		EXBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
		

	BBrush1 = CreateHatchBrush(HS_FDIAGONAL, RGB(150, 150, 150));
	BPen1 = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));

	for (int i = 0; i < BENEMYMAX; i++) {
		//Benemy[i]가 NULL이면 생성
		if (Benemy[i] == NULL) {
			Benemy[i] = new BombEnemy(LLEFTWALL + 30 + (i % 2) * 180, LTOPWALL + 30 + i / 2 * 180, 0, 0, 0, 0);
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

void SelectBShot(BombEnemy** Benemy) {
	while (1) {
		int Num = rand() % BENEMYMAX;
		if (Benemy[Num]->GetDelay() == 0) {
			//Delay가 0일경우만 실행한다.
			//0이 아니면 이미 선택된 녀석이라 다시 선택하면 안되기 때문에

			//Delay를 11으로 지정한다.
			Benemy[Num]->SetDelay(11);
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

RectEnemy::RectEnemy(int X, int Y, int C, int D, int DX, int DY, int Co) : BombEnemy(X, Y, C, D, DX, DY), Count(Co) {

}

const int RectEnemy::GetCount() const {
	//Count값을 반환한다.
	return Count;
}

void RectEnemy::SetCount() {

}

void RectEnemy::SetHitCheck(Player* player, bool OnOff) {

}

void RectEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {

}

void RectEnemy::PaintShot(HDC hdc, HDC Bithdc) const {

}







void CreateREnemy(RectEnemy** Renemy) {

}