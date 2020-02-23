#pragma once
#include <windows.h>

class Player;

class Camera {
public:
	Camera(int L, int R, int T, int B);				//카메라 생성자

	const int GetCLeft() const;						//CLeft값을 불러온다
	const int GetCRight() const;					//CRight값을 불러온다
	const int GetCTop() const;						//CTop값을 불러온다
	const int GetCBottom() const;					//CBottom값을 불러온다

	void MoveLeft();								//카메라를 왼쪽으로 이동한다.
	void MoveRight();								//카메라를 오른쪽으로 이동한다.
	void MoveTop();									//카메라를 위쪽으로 이동한다.
	void MoveBottom();								//카메라를 아래쪽으로 이동한다.

	void CameraMove(Player* player);				//카메라 이동 함수

private:
	int CLeft;
	int CRight;
	int CTop;
	int CBottom;
};

void CreateCamera(Camera** camera);
void DeleteCamera(Camera** camera);
