#pragma once
#include <windows.h>

class Player {

public:
	Player(int X, int Y);							//Player ������
		
	const int GetXPos() const;						//XPos���� �ҷ��´�.
	const int GetYPos() const;						//YPos���� �ҷ��´�.

	void MoveBasic();								//Move�� �������� ���
	const bool MoveRangeCheck() const;				//�����ϼ� �ִ� ���� üũ
	void MoveLeft();								//�������� �̵�
	void MoveRight();								//���������� �̵�		
	void MoveTop();									//�������� �̵�	
	void MoveBottom();								//�Ʒ������� �̵�

	void PaintPlayer(HDC hdc) const;				//Player �׸���

private:
	int XPos;
	int YPos;
};

void CreatePlayer(Player** player);					//Player�� ����� ���� ��ü�� ����
void DeletePlayer(Player** player);					//Player�� ���� ������� ��ü�� ����

