#pragma once
#include <windows.h>

class Player;

class Camera {
public:
	Camera(int L, int R, int T, int B);				//ī�޶� ������

	const int GetCLeft() const;						//CLeft���� �ҷ��´�
	const int GetCRight() const;					//CRight���� �ҷ��´�
	const int GetCTop() const;						//CTop���� �ҷ��´�
	const int GetCBottom() const;					//CBottom���� �ҷ��´�

	void MoveLeft();								//ī�޶� �������� �̵��Ѵ�.
	void MoveRight();								//ī�޶� ���������� �̵��Ѵ�.
	void MoveTop();									//ī�޶� �������� �̵��Ѵ�.
	void MoveBottom();								//ī�޶� �Ʒ������� �̵��Ѵ�.

	void CameraMove(Player* player);				//ī�޶� �̵� �Լ�

private:
	int CLeft;
	int CRight;
	int CTop;
	int CBottom;
};

void CreateCamera(Camera** camera);
void DeleteCamera(Camera** camera);
