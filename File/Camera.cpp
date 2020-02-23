#include "Resource.hpp"
#include "Player.hpp"
#include "Camera.hpp"

Camera::Camera(int L, int R, int T, int B) : CLeft(L), CRight(R), CTop(T), CBottom(B) {

}

const int Camera::GetCLeft() const {
	//CLeft���� ��ȯ�Ѵ�.
	return CLeft;
}

const int Camera::GetCRight() const {
	//CRight���� ��ȯ�Ѵ�.
	return CRight;
}

const int Camera::GetCTop() const {
	//CTop���� ��ȯ�Ѵ�.
	return CTop;
}

const int Camera::GetCBottom() const {
	//CBottom���� ��ȯ�Ѵ�.
	return CBottom;
}

void Camera::MoveLeft() {
	if (CLeft > CLEFTWALL) {
		//CLeft�� ī�޶���� ���ʺ��� Ŭ������ �̵��Ѵ�.
		CLeft -= 10;
		CRight -= 10;
	}
}

void Camera::MoveRight() {
	if (CRight < CRIGHTWALL) {
		//CRight�� ī�޶���� �����ʺ��� �������� �̵��Ѵ�.
		CLeft += 10;
		CRight += 10;
	}
	
}

void Camera::MoveTop() {
	if (CTop > CTOPWALL) {
		//CTop�� ī�޶���� ���ʺ��� Ŭ������ �̵��Ѵ�.
		CTop -= 10;
		CBottom -= 10;
	}
}

void Camera::MoveBottom() {
	if (CBottom < CRIGHTWALL) {
		//CBottom�� ī�޶���� �Ʒ��ʺ��� �������� �̵��Ѵ�.
		CTop += 10;
		CBottom += 10;
	}
}

void Camera::CameraMove(Player* player) {
	if (CLeft + 100 > player->GetXPos()) {
		//XPos���� CLeft+100���� �۾����� ��� �����Ѵ�.
		MoveLeft();
	}

	if (CRight - 100 < player->GetXPos()) {
		//XPos���� CRight��-100���� Ŀ���� ��� �����Ѵ�.
		MoveRight();
	}

	if (CTop + 100 > player->GetYPos()) {
		//YPos���� CTop+100���� �۾����� ��� �����Ѵ�.
		MoveTop();
	}

	if (CBottom - 100 < player->GetYPos()) {
		//YPos���� CBottom��-100���� Ŀ���� ��� �����Ѵ�.
		MoveBottom();
	}
}

void CreateCamera(Camera** camera) {
	if (*camera == NULL) {
		//ī�޶� ����
		*camera = new Camera(30, 1250, 30, 700);
	}
}

void DeleteCamera(Camera** camera) {
	if (*camera != NULL) {
		//ī�޶� ����
		delete* camera;
		*camera = NULL;
	}
}