#include "Resource.hpp"
#include "LevelSet.hpp"

void LevelSetting(const int Level, int& L, int& W, int& B, int& A) {
	switch (Level) {
	case 1:
		//Level1일 경우
		L = 20;
		W = 0;
		B = 0;
		A = 0;
		break;
	case 2:
		L = 20;
		W = 1;
		B = 1;
		A = 0;
		break;
	case 3:
		L = 25;
		W = 0;
		B = 2;
		A = 1;
		break;
	case 4:
		L = 25;
		W = 1;
		B = 2;
		A = 1;
		break;
	case 5:
		L = 30;
		W = 1;
		B = 3;
		A = 1;
		break;
	case 6:
		L = 30;
		W = 1;
		B = 4;
		A = 2;
		break;
	case 7:
		L = 30;
		W = 1;
		B = 4;
		A = 2;
		break;
	case 8:
		L = 35;
		W = 1;
		B = 5;
		A = 2;
		break;
	case 9:
		L = 40;
		W = 1;
		B = 6;
		A = 2;
		break;
	case 10:
		L = 40;
		W = 1;
		B = 6;
		A = 2;
		//마지막 레벨
		break;
	}
}

void WaitTimeSet(const int Level, int& L, int& W, int& B, int& A) {
	switch (Level) {
	case 1:
		L = 1;
		W = 50;
		B = 20;
		A = 30;
		break;
	case 2:
		L = 1;
		W = 50;
		B = 20;
		A = 30;
		break;
	case 3:
		L = 1;
		W = 45;
		B = 20;
		A = 30;
		break;
	case 4:
		L = 1;
		W = 45;
		B = 20;
		A = 30;
		break;
	case 5:
		L = 1;
		W = 40;
		B = 15;
		A = 20;
		break;
	case 6:
		L = 1;
		W = 40;
		B = 15;
		A = 20;
		break;
	case 7:
		L = 1;
		W = 40;
		B = 10;
		A = 20;
		break;
	case 8:
		L = 1;
		W = 40;
		B = 10;
		A = 15;
		break;
	case 9:
		L = 1;
		W = 30;
		B = 10;
		A = 15;
		break;
	case 10:
		L = 4;
		W = 30;
		B = 5;
		A = 15;
		break;
	}
}