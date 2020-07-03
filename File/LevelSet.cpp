#include "Resource.hpp"
#include "LevelSet.hpp"

LevelSet::LevelSet(int LS, int BS, int AS, int LM, int WM, int BM, int AM, int LW, int WW, int BW, int AW)
: LShot(LS), BShot(BS), AShot(AS), LMaxShot(LM), WMaxShot(WM), BMaxShot(BM), AMaxShot(AM), LWT(LW), WWT(WW), BWT(BW), AWT(AW) {

}

const int LevelSet::GetLShot() const {
	//LShot���� return�Ѵ�.
	return  LShot;
}

const int LevelSet::GetBShot() const {
	//BShot���� return�Ѵ�.
	return  BShot;
}

const int LevelSet::GetAShot() const {
	//AShot���� return�Ѵ�.
	return  AShot;
}

const int LevelSet::GetLMaxShot() const {
	//LMaxShot���� return�Ѵ�.
	return  LMaxShot;
}

const int LevelSet::GetWMaxShot() const {
	//WMaxShot���� return�Ѵ�.
	return  WMaxShot;
}

const int LevelSet::GetBMaxShot() const {
	//BMaxShot���� return�Ѵ�.
	return  BMaxShot;
}

const int LevelSet::GetAMaxShot() const {
	//AMaxShot���� return�Ѵ�.
	return  AMaxShot;
}

const int LevelSet::GetLWT() const {
	//LWT���� return�Ѵ�.
	return  LWT;
}

const int LevelSet::GetWWT() const {
	//WWT���� return�Ѵ�.
	return  WWT;
}

const int LevelSet::GetBWT() const {
	//BWT���� return�Ѵ�.
	return  BWT;
}

const int LevelSet::GetAWT() const {
	//AWT���� return�Ѵ�.
	return  AWT;
}

void LevelSet::ChangeLShot(const int Num) {
	//LShot���� �����Ѵ�.
	LShot = Num;
}

void LevelSet::ChangeBShot(const int Num) {
	//BShot���� �����Ѵ�.
	BShot = Num;
}

void LevelSet::ChangeAShot(const int Num) {
	//AShot���� �����Ѵ�.
	AShot = Num;
}

void LevelSet::LevelSetting(const int Level) {
	switch (Level) {
	case 1:
		//Level1�� ���
		LMaxShot = 20;
		WMaxShot = 0;
		BMaxShot = 0;
		AMaxShot = 0;
		break;
	case 2:
		LMaxShot = 20;
		WMaxShot = 1;
		BMaxShot = 1;
		AMaxShot = 0;
		break;
	case 3:
		LMaxShot = 25;
		WMaxShot = 0;
		BMaxShot = 2;
		AMaxShot = 1;
		break;
	case 4:
		LMaxShot = 25;
		WMaxShot = 1;
		BMaxShot = 2;
		AMaxShot = 1;
		break;
	case 5:
		LMaxShot = 30;
		WMaxShot = 1;
		BMaxShot = 3;
		AMaxShot = 1;
		break;
	case 6:
		LMaxShot = 30;
		WMaxShot = 1;
		BMaxShot = 4;
		AMaxShot = 2;
		break;
	case 7:
		LMaxShot = 30;
		WMaxShot = 1;
		BMaxShot = 4;
		AMaxShot = 2;
		break;
	case 8:
		LMaxShot = 35;
		WMaxShot = 1;
		BMaxShot = 5;
		AMaxShot = 2;
		break;
	case 9:
		LMaxShot = 40;
		WMaxShot = 1;
		BMaxShot = 6;
		AMaxShot = 2;
		break;
	case 10:
		LMaxShot = 40;
		WMaxShot = 1;
		BMaxShot = 6;
		AMaxShot = 2;
		//������ ����
		break;
	}
}

void LevelSet::WaitTimeSetting(const int Level) {
	switch (Level) {
	case 1:
		LWT = 1;
		WWT = 50;
		BWT = 20;
		AWT = 30;
		break;
	case 2:
		LWT = 1;
		WWT = 50;
		BWT = 20;
		AWT = 30;
		break;
	case 3:
		LWT = 1;
		WWT = 45;
		BWT = 20;
		AWT = 30;
		break;
	case 4:
		LWT = 1;
		WWT = 45;
		BWT = 20;
		AWT = 30;
		break;
	case 5:
		LWT = 1;
		WWT = 40;
		BWT = 15;
		AWT = 20;
		break;
	case 6:
		LWT = 1;
		WWT = 40;
		BWT = 15;
		AWT = 20;
		break;
	case 7:
		LWT = 1;
		WWT = 40;
		BWT = 10;
		AWT = 20;
		break;
	case 8:
		LWT = 1;
		WWT = 40;
		BWT = 10;
		AWT = 15;
		break;
	case 9:
		LWT = 1;
		WWT = 30;
		BWT = 10;
		AWT = 15;
		break;
	case 10:
		LWT = 4;
		WWT = 30;
		BWT = 5;
		AWT = 15;
		break;
	}
}

void CreateLevelSet(LevelSet** Level) {
	if (*Level == NULL) {
		*Level = new LevelSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}

void DeleteLevelSet(LevelSet** Level) {
	if (*Level != NULL) {
		delete* Level;
		*Level = NULL;
	}
}