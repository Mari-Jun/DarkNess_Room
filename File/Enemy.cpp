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
	//Charging���� 10���� �����Ѵ�.
	Charging = 11;
}

bool Enemy::ChangeCharging() {
	//Charging�� 0���� ũ�ٸ� 1�� ���ҽ�Ų��.
	if (Charging > 0) {
		
		Charging--;

		if (Charging == 0) {
			//���� Charging�� 0�� �ȴٸ� Delay�� 0���� ������ش�.
			Delay = 0;
			//�߻� �ð��� ���� ���������� true�� ��ȯ
			return true;
		}
		return false;
	}
	//���� �߻�ð������� false�� ��ȯ
	return false;

}

void Enemy::SetDelay(int D) {
	//���� �������� Delay�� �޶�������� ���� D�� �Է½�Ų��.
	Delay = D;
}

bool Enemy::ChangeDelay() {
	//Delay�� 1���� ũ�ٸ� 1�� ���ҽ�Ų��.
	if (Delay > 1) {
		Delay--;
		//���� Delay�� 1�̶�� Charging�� �������ش�.
		if (Delay == 1) {
			SetCharging();
		}
		return true;
	}
	else if (Delay == 1)
		//Delay�� 1�̸� �߻����̱� ������
		return true;
	return false;
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
		//������ 5~8���� �����Ѵ�.
		Range = rand() % 4 + 5;
	}
	else {
		//��ġ�� �ʴ� ���
		//������ 11~20���� �����Ѵ�
		Range = rand() % 10 + 11;
	}
}

void LineEnemy::SetHitCheck(Player* player, bool OnOff) {
	//HitCheck�� �����Ѵ�.

	//HitCheck�� ������ ������ �����Ѵ�.
	int Left, Right, Top, Bottom;
	if (abs(Direction) == 1) {
		//�� �Ʒ� �������ϰ��
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
		//���� ������ �������ϰ��
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

	//player�� SetHitCheck�� �ҷ��´�.
	player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
}


void LineEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {

	if (abs(Direction) == 1) {
		if(Direction==1)
			SelectObject(Bithdc, LBitMap[0]);
		else
			SelectObject(Bithdc, LBitMap[3]);
		TransparentBlt(hdc, GetXPos() - 30, GetYPos() -40, 60, 80, Bithdc, 0, 0, 60, 80, RGB(255, 255, 255));
	}

	if (abs(Direction == 2)) {
		if (Direction == 2)
			SelectObject(Bithdc, LBitMap[1]);
		else
			SelectObject(Bithdc, LBitMap[2]);
		TransparentBlt(hdc, GetXPos() - 40, GetYPos() - 30, 80, 60, Bithdc, 0, 0, 80, 60, RGB(255, 255, 255));
	}

	/*if (this->GetCharging() != 0) {
		//�߻� ���̶��
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}
	else {
		//�߻� ���� �ƴ϶��
		if(GetDelay()==0)
			LBrush1 = CreateSolidBrush(RGB(10, 10, 10));
		else
			LBrush1 = CreateSolidBrush(RGB((10 - GetDelay()) * 15, 10, 10));
		OldEBrush = (HBRUSH)SelectObject(hdc, LBrush1);
		OldEPen = (HPEN)SelectObject(hdc, LPen1);
	}*/

/*	if (abs(Direction) == 1) {
		//���� ���ϰ�� , //�Ʒ��� ���ϰ��
		POINT Pos[4] = { {GetXPos() - 20,GetYPos() - 20 * Direction},{GetXPos() + 20,GetYPos() - 20 * Direction},{GetXPos() + 10,GetYPos() + 35 * Direction},{GetXPos() - 10,GetYPos() + 35 * Direction} };

		Ellipse(hdc, GetXPos() - 20, GetYPos() - 40 * Direction, GetXPos() + 20, GetYPos());
		Polygon(hdc, Pos, 4);
		RoundRect(hdc, GetXPos() - 13, GetYPos() + 32 * Direction, GetXPos() + 13, GetYPos() + 38 * Direction, 6, 6);
	
	}*/
	/*else {
		//���� ���ϰ��, //������ ���ϰ��
		POINT Pos[4] = { {GetXPos() - 20 * Direction / 2,GetYPos() - 20},{GetXPos() + 35 * Direction / 2,GetYPos() - 10},{GetXPos() + 35 * Direction / 2,GetYPos() + 10},{GetXPos() - 20 * Direction / 2,GetYPos() + 20} };

		Ellipse(hdc, GetXPos() - 40 * Direction / 2, GetYPos() - 20, GetXPos(), GetYPos() + 20);
		Polygon(hdc, Pos, 4);
		RoundRect(hdc, GetXPos() + 32 * Direction / 2, GetYPos() - 13, GetXPos() + 38 * Direction / 2, GetYPos() + 13, 6, 6);
	}
	*/
/*	DeleteObject(LBrush1);
	SelectObject(hdc, OldEBrush);
	SelectObject(hdc, OldEPen);*/
}

void LineEnemy::PaintShot(HDC hdc) const{

	if (this->GetDelay() != 0) {
		//�߻� ���� �ð��� 0�� �ƴҶ� 
		if (this->GetCharging() != 0) {
			//�߻� ���϶� 
			//�� Delay�� 1�̰� Charging�� 1�̻��϶�
			OldEBrush = (HBRUSH)SelectObject(hdc, LBrush2);
			OldEPen = (HPEN)SelectObject(hdc, LPen2);
		}
		else {
			//�߻� ������϶� 
			//�� Delay�� 1�̻��̰� Charging�� 0�϶�
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

			//Delay�� 11���� �����Ѵ�.
			Lenemy[Num]->SetDelay(11);
			//Range�� �����Ѵ�.
			Lenemy[Num]->SetRange();

			return;
		}
	}
}

int ChangeLInfo(LineEnemy** Lenemy, Player* player) {
	//Lenemy���� �˻��ؼ� Delay���� 0�� �ƴ� �༮�� ���ؼ� �����Ų��.

	int Count = 0;

	for (int i = 0; i < 80; i++) {
		if (Lenemy[i]->ChangeDelay()) {
			//ChangeDelay�Լ��� ���������� ����Ǿ��� ��쿡�� �����Ѵ�.

			//�߻� ������̰ų� �߻��������� Count�� 1���� ��Ų��.
			Count++;

			if (Lenemy[i]->GetCharging() == 11) {
				//��� ������ ���� ���
				//SetHitCheck�� ȣ���Ѵ�.
				Lenemy[i]->SetHitCheck(player, true);
			}

			if (Lenemy[i]->ChangeCharging()) {
				//ChangeCharging()�� true(�߻� ����)�� ��ȯ���� ��쿡�� �����Ѵ�.

				//�߻����������� Count�� 1���� ��Ų��.
				Count--;

				//�߻簡 �����������
				//SetHitCheck�� ȣ���Ѵ�.
				Lenemy[i]->SetHitCheck(player, false);
			}
		}
	}
	//Count�� (���� ����ǰ� �ִ� LEnemy�� ��)�� ��ȯ�Ͽ� LShot���� ��������ش�. 
	return Count;
}




//������ ���ʹ�

WideEnemy::WideEnemy(int X, int Y, int C, int D, int Di) : Enemy(X, Y, C, D), Direction(Di) {

}

const int WideEnemy::GetDirection() const {
	//Direction���� ��ȯ�Ѵ�.
	return  Direction;
}

void WideEnemy::SetDirection() {
	//Direction���� �����Ѵ�. 1:������, 2: ������ ��, 3: ���ʾƷ�, 4: �����ʾƷ�
	Direction = rand() % 4 + 1;
}

void WideEnemy::SetHitCheck(Player* player, bool OnOff) {
	//HitCheck�� �����Ѵ�.

	//HitCheck�� ������ ������ �����Ѵ�.
	int Left, Right, Top, Bottom;

	//���� �����Ѵ�.
	Left = 10 * (1 - Direction % 2);
	Right = 10 * (1 - Direction % 2) +9;
	Top = 10 * (Direction / 3);
	Bottom = 10 * (Direction / 3) + 9;

	//player�� SetHitCheck�� �ҷ��´�.
	player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
}

void WideEnemy::PaintEnmey(HDC hdc, HDC BIthdc) const {
	
}

void WideEnemy::PaintShot(HDC hdc) const {

}

void CreateWEnemy(WideEnemy** Wenemy) {
	if (*Wenemy == NULL) {
		//*Wenemy�� NULL�϶� �۵�
		//WideEnemy�� 1���̴�.
		*Wenemy = new WideEnemy((LLEFTWALL + LRIGHTWALL) / 2, (LTOPWALL + LBOTTOMWALL / 2), 0, 0, 0);

		//WideEnemyBrush , Pen (��)�� ���� ���� ǥ����
		WEBrush = CreateSolidBrush(RGB(250, 237, 125));
		WEPen = CreatePen(PS_SOLID, 1, RGB(50, 50, 50));

		//WideEnemyShotBrush, Pen (��)�� ���� �� ���� ǥ����.
		WSBrush1 = CreateSolidBrush(RGB(250, 237, 125));
		WSBrush2 = CreateHatchBrush(HS_FDIAGONAL, RGB(250, 237, 125));
		WSPen = CreatePen(PS_SOLID, 1, RGB(196, 183, 59));
	}
}

void DeleteWEnemy(WideEnemy** Wenemy) {
	if (*Wenemy != NULL) {
		delete* Wenemy;
		*Wenemy = NULL;

		DeleteObject(WEBrush);
		DeleteObject(WEPen);
		DeleteObject(WSBrush1);
		DeleteObject(WSBrush2);
		DeleteObject(WSPen);
	}
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

void BombEnemy::SetHitCheck(Player* player, bool OnOff) {

}

void BombEnemy::SetDropPos() {

}

void BombEnemy::PaintEnmey(HDC hdc, HDC BIthdc) const {

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

void RectEnemy::SetHitCheck(Player* player, bool OnOff) {

}

void RectEnemy::PaintEnmey(HDC hdc, HDC BIthdc) const {

}

void RectEnemy::PaintShot(HDC hdc) const {

}





void CreateBEnemy(BombEnemy** Benemy) {

}

void CreateREnemy(RectEnemy** Renemy) {

}