#include "Resource.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


//�⺻ ���ʹ�

Enemy::Enemy(int C, int D) : Charging(C), Delay(D) {

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

//���� ���ʹ�

FixEnemy::FixEnemy(int C, int D, int X, int Y) : Enemy(C, D), XPos(X), YPos(Y) {

}

const int FixEnemy::GetXPos() const {
	//XPos���� ��ȯ�Ѵ�.
	return XPos;
}

const int FixEnemy::GetYPos() const {
	//YPos���� ��ȯ�Ѵ�.
	return YPos;
}


//�̵� ���ʹ�

MoveEnemy::MoveEnemy(int C, int D, int X, int Y) : Enemy(C, D), XPos(X), YPos(Y) {

}

const int MoveEnemy::GetXPos() const {
	//XPos���� ��ȯ�Ѵ�.
	return XPos;
}

const int MoveEnemy::GetYPos() const {
	//YPos���� ��ȯ�Ѵ�.
	return YPos;
}

void MoveEnemy::ChangeXPos(int X) {
	//XPos���� �����Ѵ�.
	XPos = X;
}

void MoveEnemy::ChangeYPos(int Y) {
	//YPos���� �����Ѵ�.
	YPos = Y;
}



//������ ���ʹ�

LineEnemy::LineEnemy(int C, int D, int X, int Y, int R, int Di) : FixEnemy(C, D, X, Y), Range(R), Direction(Di){

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

void LineEnemy::SetHitCheck(Player* player, const bool OnOff) const {
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
		//�߻� ���� �ð��� 0�� �ƴҶ� 
		if (GetCharging() != 0) {
			//�߻� ���϶� 
			//�� Delay�� 1�̰� Charging�� 1�̻��϶�

			if (abs(Direction) == 1) {
				//���� �߻� ��Ʈ���� �ҷ��´�.
				SelectObject(Bithdc, LSBitMap[22 - GetCharging()]);
				if (Direction == 1) {
					//Range * 61�� ������ *60�� �ϸ� ��ó���� �̻��ϰ� ������ �����̴�.
					//600����� Range*60��ŭ�� ������� �÷��ش�.
					StretchBlt(Bithdc2, 0, 0, 60, Range * 61, Bithdc, 0, 600, 60, -600, SRCCOPY);

					//������ ������ �߻����� ������ش�.
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
			//�߻� ������϶� 
			//�� Delay�� 1�̻��̰� Charging�� 0�϶�

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
				//Lenemy[i]�� NULL�̸� ���� �� ����
				Lenemy[i] = new LineEnemy(0, 0, 150 + 60 * i, CTOPWALL + 45, 0, 1);
		}
		else if (i >= 20 && i < 40) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� ���� �� ����
				Lenemy[i] = new LineEnemy(0, 0, CLEFTWALL + 45, 150 + 60 * (i - 20), 0, 2);
		}
		else if (i >= 40 && i < 60) {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� ������ �� ����
				Lenemy[i] = new LineEnemy(0, 0, CRIGHTWALL - 45, 150 + 60 * (i - 40), 0, -2);
		}
		else {
			if (Lenemy[i] == NULL)
				//Lenemy[i]�� NULL�̸� �Ʒ��� �� ����
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
	//LineEnemy�� 0~79�� 1���� �����Ѵ�.
	while (1) {
		int Num = rand() % LENEMYMAX;
		if (Lenemy[Num]->GetDelay() == 0) {
			//Delay�� 0�ϰ�츸 �����Ѵ�.
			//0�� �ƴϸ� �̹� ���õ� �༮�̶� �ٽ� �����ϸ� �ȵǱ� ������

			//Delay�� 11���� �����Ѵ�.
			Lenemy[Num]->SetDelay(rand() % WaitTime + 11);
			//Range�� �����Ѵ�.
			Lenemy[Num]->SetRange();

			return;
		}
	}
}

int ChangeLInfo(LineEnemy** Lenemy, Player* player) {
	//Lenemy���� �˻��ؼ� Delay���� 0�� �ƴ� �༮�� ���ؼ� �����Ų��.

	int Count = 0;

	for (int i = 0; i < LENEMYMAX; i++) {
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

WideEnemy::WideEnemy(int C, int D, int X, int Y, int Di) : FixEnemy(C, D, X, Y), Direction(Di) {

}

const int WideEnemy::GetDirection() const {
	//Direction���� ��ȯ�Ѵ�.
	return  Direction;
}

void WideEnemy::SetDirection() {
	//Direction���� �����Ѵ�. 1:������, 2: ������ ��, 3: ���ʾƷ�, 4: �����ʾƷ�
	Direction = rand() % 4 + 1;
}

void WideEnemy::SetHitCheck(Player* player, const bool OnOff) const {
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

void WideEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	if (GetCharging() == 0)
		//Charging���� ���� ����
		SelectObject(Bithdc, WEBitmap1);
	else
		//Charging�� ���ִ� ����
		SelectObject(Bithdc, WEBitmap2);

	TransparentBlt(hdc, GetXPos() - 45, GetYPos() - 45, 90, 90, Bithdc, 0, 0, 90, 90, RGB(0, 0, 0));
}

void WideEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//�߻� ���̰ų� �߻� ������϶� �۵�
		if (GetCharging() == 0) {
			//�߻� ������̶��
			OldEBrush = (HBRUSH)SelectObject(hdc, WSBrush); 
			OldEPen = (HPEN)SelectObject(hdc, WSPen);

			POINT Pos[6];
			//�� ���⺰�� Pos���� �ٸ��� ����
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
			//���������� �׸���
			Polygon(hdc, Pos, 6);

			SelectObject(hdc, OldEBrush);
			SelectObject(hdc, OldEPen);

		}
		else {
			//�߻����̶��
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

	//WideEnemyShotBrush, Pen (��)�� ���� �� ���� ǥ����.
	WSBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(178, 235, 244));
	WSPen = CreatePen(PS_SOLID, 1, RGB(92, 209, 229));


	//WideEnemy���� ���� Bitmap���� �ҷ��´�.
	WEBitmap1 = (HBITMAP)LoadImage(NULL, L".\\BitMap\\WideEnemy1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	WEBitmap2 = (HBITMAP)LoadImage(NULL, L".\\BitMap\\WideEnemy2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	for (int i = 0; i < 7; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\WideShot%d.bmp", i + 1);
		WSBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	if (*Wenemy == NULL) {
		//*Wenemy�� NULL�϶� �۵�
		//WideEnemy�� 1���̴�.
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
			//���� ����
			Wenemy->SetDirection();
			//�߻� ��� �ð� ����
			Wenemy->SetDelay(WaitTime + 11);
	}
	else {
		//�߻� ������̰ų� �߻����� ���

		//Delay�� ����
		Wenemy->ChangeDelay();

		if(Wenemy->GetCharging() == 11) {
			//��� ������ ���� ���
			//SetHitCheck�� ȣ���Ѵ�.
			Wenemy->SetHitCheck(player, true);
		}

		if (Wenemy->ChangeCharging()) {
			//ChangeCharging()�� true(�߻� ����)�� ��ȯ���� ��쿡�� �����Ѵ�.

			//�߻簡 �����������
			//SetHitCheck�� ȣ���Ѵ�.
			Wenemy->SetHitCheck(player, false);
		}
	}
}


//��ź ���ʹ�

BombEnemy::BombEnemy(int C, int D, int X, int Y) : MoveEnemy(X, Y, C, D){

}

void BombEnemy::SetHitCheck(Player* player, const bool OnOff) const {
	//HitCheck�� �����Ѵ�.

	//HitCheck�� ������ ������ �����Ѵ�.
	int Left, Right, Top, Bottom;

	//�¿� -> ���Ʒ� ������ ó��
	for (int i = 0; i < 2; i++) {
		Left = GetXPos() - (2 - i);
		Right = GetXPos() + (2 - i);
		Top = GetYPos() - (1 + i);
		Bottom = GetYPos() + (1 + i);
		
		//player�� SetHitCheck�� �ҷ��´�.
		player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
	}
}

void BombEnemy::SetDropPos() {
	while (1) {
		//��,�Ʒ�,��,��� �ּ��� 2ĭ���� ���ܳ��ƾ� �Ѵ�.
		ChangeXPos(rand() % 16 + 2);
		ChangeYPos(rand() % 16 + 2);

		//�߰��� ������ �翬�� 2ĭ���� ����־�� �Ѵ�.
		if ((GetXPos() < 6 || GetXPos() > 13) || (GetYPos() < 6 || GetYPos() > 13))
			break;
	}
}

void BombEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	//BombEnemy�� �׸���.
	if (GetDelay() > 0 && GetDelay() < 12) {
		//��ź�� ������ ����

		if (GetCharging() == 0) {
			//���� ��� ����
			//��ź �׸���
			SelectObject(Bithdc, BBitmap);
			TransparentBlt(hdc, LEFTWALL + GetXPos() * 60, TOPWALL + GetYPos() * 60, 60, 60, Bithdc, 0, 0, 60, 60, RGB(255, 255, 255));
		}
	}
}

void BombEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//��ź�� ������ �ĸ� ����.
		//Delay12 ������ ������ �ұ�Ģ ���� ��ź�� �����ϰ� �; ������ �������־���.

		//Brush�� Pen ����
		OldEBrush = (HBRUSH)SelectObject(hdc, BBrush);
		OldEPen = (HPEN)SelectObject(hdc, BPen);

		if (GetCharging() == 0) {
			//���� ������

			//��ź ���� �׸���
			Rectangle(hdc, LEFTWALL + (GetXPos() - 2) * 60, TOPWALL + (GetYPos() - 1) * 60, LEFTWALL + (GetXPos() + 3) * 60, TOPWALL + (GetYPos() + 2) * 60);
			Rectangle(hdc, LEFTWALL + (GetXPos() - 1) * 60, TOPWALL + (GetYPos() - 2) * 60, LEFTWALL + (GetXPos() + 2) * 60, TOPWALL + (GetYPos() + 3) * 60);
		}
		else {
			//���Ļ���
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
		//Benemy[i]�� NULL�̸� ����
		if (Benemy[i] == NULL) {
			Benemy[i] = new BombEnemy(0, 0, 0, 0);
		}
	}
}

void DeleteBEnemy(BombEnemy** Benemy) {

	DeleteObject(BBitmap);

	for (int i = 0; i < BENEMYMAX; i++) {
		//Benemy[i]�� NULL�� �ƴ� ���
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
			//Delay�� 0�ϰ�츸 �����Ѵ�.
			//0�� �ƴϸ� �̹� ���õ� �༮�̶� �ٽ� �����ϸ� �ȵǱ� ������

			//�ּ� 11  �ִ� 11 + WaitTime��ŭ�� ����
			Benemy[Num]->SetDelay(rand() % WaitTime + 11);
			//DropPos�� �����Ѵ�.
			Benemy[Num]->SetDropPos();
			return;
		}
	}
}

int ChangeBInfo(BombEnemy** Benemy, Player* player) {
	//Benemy���� �˻��ؼ� Delay���� 0�� �ƴ� �༮�� ���ؼ� �����Ų��.

	int Count = 0;

	for (int i = 0; i < BENEMYMAX; i++) {
		if (Benemy[i]->ChangeDelay()) {
			//ChangeDelay�Լ��� ���������� ����Ǿ��� ��쿡�� �����Ѵ�.

			//�߻� ������̰ų� �߻��������� Count�� 1���� ��Ų��.
			Count++;

			if (Benemy[i]->GetCharging() == 11) {
				//��� ������ ���� ���
				//SetHitCheck�� ȣ���Ѵ�.
				Benemy[i]->SetHitCheck(player, true);
			}

			if (Benemy[i]->ChangeCharging()) {
				//ChangeCharging()�� true(�߻� ����)�� ��ȯ���� ��쿡�� �����Ѵ�.

				//�߻����������� Count�� 1���� ��Ų��.
				Count--;

				//�߻簡 �����������
				//SetHitCheck�� ȣ���Ѵ�.
				Benemy[i]->SetHitCheck(player, false);
			}
		}
	}
	//Count�� (���� ����ǰ� �ִ� LEnemy�� ��)�� ��ȯ�Ͽ� LShot���� ��������ش�. 
	return Count;
}



//������ ���ʹ�

AirEnemy::AirEnemy(int C, int D, int X, int Y, int DX, int DY) : MoveEnemy(C, D, X, Y), DXPos(DX), DYPos(DY) {

}

const int AirEnemy::GetDXPos() const {
	//DXPos���� ��ȯ�Ѵ�.
	return DXPos;	
}

const int AirEnemy::GetDYPos() const {
	//DYPos���� ��ȯ�Ѵ�.
	return DYPos;
}

void AirEnemy::SetDropPos(Player* player) {

	//���� �÷��̾ �ִ� ���� Ÿ�� ��ġ�� �����Ѵ�.
	DXPos = (player->GetXPos() - 120) / 60;
	DYPos = (player->GetYPos() - 120) / 60;


	//�𼭸��� ���� ��� ���� ���� ������ ���� DXPos��, DYPos���� �������ش�.
	if (DXPos == 0)
		DXPos++;
	if (DYPos == 0)
		DYPos++;
	if (DXPos == 19)
		DXPos--;
	if (DYPos == 19)
		DYPos--;

	//�߰����� ����ȴ�.
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

	//HitCheck�� �����Ѵ�.

	//HitCheck�� ������ ������ �����Ѵ�.
	int Left, Right, Top, Bottom;
	Left = DXPos - 1;
	Right = DXPos + 1;
	Top = DYPos - 1;
	Bottom = DYPos + 1;

	player->SetHitCheck(Left, Right, Top, Bottom, OnOff);
}

void AirEnemy::PaintEnmey(HDC hdc, HDC Bithdc) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//�߻� ��ȣ�� �� �۵��Ѵ�.

		SelectObject(Bithdc, ABitmap);

		TransparentBlt(hdc, GetXPos() - 30, GetYPos() - 30, 120, 120, Bithdc, 0, 0, 120, 120, RGB(255, 255, 255));
	}
}

void AirEnemy::PaintShot(HDC hdc, HDC Bithdc, HDC Bithdc2) const {
	if (GetDelay() > 0 && GetDelay() < 12) {
		//����Ⱑ ����߰ų� ��ź�� �����ִ� ���¸� ���Ѵ�.
		if (GetCharging() == 0) {
			//���� ���� ���°� �ƴҶ�
			OldEBrush = (HBRUSH)SelectObject(hdc, ABrush);
			OldEPen = (HPEN)SelectObject(hdc, APen);

			//3*3����� ���簢���� �׸���.
			Rectangle(hdc, LEFTWALL + (DXPos - 1) * 60, TOPWALL + (DYPos - 1) * 60, LEFTWALL + (DXPos + 2) * 60, TOPWALL + (DYPos + 2) * 60);

			SelectObject(hdc, OldEBrush);
			SelectObject(hdc, OldEPen);

		}
		else {
			//���� �����϶�
			SelectObject(Bithdc, ASBitmap[11 - GetCharging()]);
			TransparentBlt(hdc, LEFTWALL + (DXPos - 1) * 60, TOPWALL + (DYPos - 1) * 60, 180, 180, Bithdc, 0, 0, 180, 180, RGB(255, 255, 255));
		}
	}
}

void CreateAEnemy(AirEnemy** Aenemy) {

	//AirEnemy�� �ҷ��´�.
	ABitmap = (HBITMAP)LoadImage(NULL, L".\\BitMap\\AirPlane1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//AirEnemy���� �ҷ��´�.
	for (int i = 0; i < 11; i++) {
		wchar_t str[100];
		swprintf_s(str, L".\\BitMap\\AirShot%d.bmp", i);
		ASBitmap[i] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	ABrush = CreateHatchBrush(HS_FDIAGONAL, RGB(250, 237, 125));
	APen = CreatePen(PS_SOLID, 1, RGB(232, 229, 109));

	for (int i = 0; i < AENEMYMAX; i++) {
		if (Aenemy[i] == NULL) {
			//Aenemy[i]�� NULL�϶��� �۵��Ѵ�.
			Aenemy[i] = new AirEnemy(0, 0, 0, 0, 0, 0);
		}
	}
}

void DeleteAEnemy(AirEnemy** Aenemy) {


	for(int i=0; i<AENEMYMAX; i++)
		if (Aenemy[i] != NULL) {
			//Aenemy[i]�� NULL�� �ƴҰ�� �۵�
			delete Aenemy[i];
			Aenemy[i] = NULL;
		}
}

void SelectAShot(AirEnemy** Aenemy, Player* player, const int WaitTime) {
	while (1) {
		int Num = rand() % AENEMYMAX;
		if (Aenemy[Num]->GetDelay() == 0) {
			//Delay�� 0�ϰ�츸 �����Ѵ�.
			//0�� �ƴϸ� �̹� ���õ� �༮�̶� �ٽ� �����ϸ� �ȵǱ� ������

			//�ּ� 12 �ִ� 12+ WaitTime��ŭ�� ����
			Aenemy[Num]->SetDelay(rand() % WaitTime + 12);

			return;
		}
	}
}

int ChangeAInfo(AirEnemy** Aenemy, Player* player) {
	//Benemy���� �˻��ؼ� Delay���� 0�� �ƴ� �༮�� ���ؼ� �����Ų��.

	int Count = 0;

	for (int i = 0; i < AENEMYMAX; i++) {
		if (Aenemy[i]->ChangeDelay()) {
			//ChangeDelay�Լ��� ���������� ����Ǿ��� ��쿡�� �����Ѵ�.

			//�߻� ������̰ų� �߻��������� Count�� 1���� ��Ų��.
			Count++;

			if (Aenemy[i]->GetDelay() == 11) {
				//�߻� �غ� �Ϸ� �Ǿ��ٸ� �� ���Ĺ����� ���ö����
				//DropPos�� �����Ѵ�.
				Aenemy[i]->SetDropPos(player);
			}


			if (Aenemy[i]->GetCharging() == 0) {
				//���� ���İ� �ȵ� ����

				//������� XPos���� YPos���� �����Ѵ�.
				Aenemy[i]->ChangeXPos((LEFTWALL + Aenemy[i]->GetDXPos() * 60) / 10 * (11 - Aenemy[i]->GetDelay()));
				Aenemy[i]->ChangeYPos(TOPWALL + Aenemy[i]->GetDYPos() * 60);
	
			}
			else {
				//�������� ����

				//������� XPos���� YPos���� �����Ѵ�.
				Aenemy[i]->ChangeXPos(LEFTWALL + Aenemy[i]->GetDXPos() * 60 + (ALLMAPX - (LEFTWALL + Aenemy[i]->GetDXPos() * 60)) / 10 * (11 - Aenemy[i]->GetCharging()));
				Aenemy[i]->ChangeYPos(TOPWALL + Aenemy[i]->GetDYPos() * 60);
			}

			if (Aenemy[i]->GetCharging() == 11) {
				//��� ������ ���� ���
				//SetHitCheck�� ȣ���Ѵ�.
				Aenemy[i]->SetHitCheck(player, true);
			}

			if (Aenemy[i]->ChangeCharging()) {
				//ChangeCharging()�� true(�߻� ����)�� ��ȯ���� ��쿡�� �����Ѵ�.

				//�߻����������� Count�� 1���� ��Ų��.
				Count--;

				//�߻簡 �����������
				//SetHitCheck�� ȣ���Ѵ�.
				Aenemy[i]->SetHitCheck(player, false);
			}
		}
	}
	//Count�� (���� ����ǰ� �ִ� LEnemy�� ��)�� ��ȯ�Ͽ� LShot���� ��������ش�. 
	return Count;
}