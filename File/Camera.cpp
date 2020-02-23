#include "Resource.hpp"
#include "Player.hpp"
#include "Camera.hpp"

Camera::Camera(int L, int R, int T, int B) : CLeft(L), CRight(R), CTop(T), CBottom(B) {

}

const int Camera::GetCLeft() const {
	//CLeft값을 반환한다.
	return CLeft;
}

const int Camera::GetCRight() const {
	//CRight값을 반환한다.
	return CRight;
}

const int Camera::GetCTop() const {
	//CTop값을 반환한다.
	return CTop;
}

const int Camera::GetCBottom() const {
	//CBottom값을 반환한다.
	return CBottom;
}

void Camera::MoveLeft() {
	if (CLeft > CLEFTWALL) {
		//CLeft가 카메라맵의 왼쪽보다 클때에만 이동한다.
		CLeft -= 10;
		CRight -= 10;
	}
}

void Camera::MoveRight() {
	if (CRight < CRIGHTWALL) {
		//CRight가 카메라맵의 오른쪽보다 작을때만 이동한다.
		CLeft += 10;
		CRight += 10;
	}
	
}

void Camera::MoveTop() {
	if (CTop > CTOPWALL) {
		//CTop이 카메라맵의 위쪽보다 클때에만 이동한다.
		CTop -= 10;
		CBottom -= 10;
	}
}

void Camera::MoveBottom() {
	if (CBottom < CRIGHTWALL) {
		//CBottom이 카메라맵의 아래쪽보다 작을때만 이동한다.
		CTop += 10;
		CBottom += 10;
	}
}

void Camera::CameraMove(Player* player) {
	if (CLeft + 100 > player->GetXPos()) {
		//XPos값이 CLeft+100보다 작아졌을 경우 실행한다.
		MoveLeft();
	}

	if (CRight - 100 < player->GetXPos()) {
		//XPos값이 CRight값-100보다 커졌을 경우 실행한다.
		MoveRight();
	}

	if (CTop + 100 > player->GetYPos()) {
		//YPos값이 CTop+100보다 작아졌을 경우 실행한다.
		MoveTop();
	}

	if (CBottom - 100 < player->GetYPos()) {
		//YPos값이 CBottom값-100보다 커졌을 경우 실행한다.
		MoveBottom();
	}
}

void CreateCamera(Camera** camera) {
	if (*camera == NULL) {
		//카메라 생성
		*camera = new Camera(30, 1250, 30, 700);
	}
}

void DeleteCamera(Camera** camera) {
	if (*camera != NULL) {
		//카메라 제거
		delete* camera;
		*camera = NULL;
	}
}