#pragma once
#include "windows.h"

class LevelSet {
public:
	explicit LevelSet(int LS, int BS, int AS, int LM, int WM, int BM, int AM, int LW, int WW, int BW, int AW);

	const int GetLShot() const;
	const int GetBShot() const;
	const int GetAShot() const;
	const int GetLMaxShot() const;
	const int GetWMaxShot() const;
	const int GetBMaxShot() const;
	const int GetAMaxShot() const;
	const int GetLWT() const;
	const int GetWWT() const;
	const int GetBWT() const;
	const int GetAWT() const;

	void ChangeLShot(const int Num);
	void ChangeBShot(const int Num);
	void ChangeAShot(const int Num);

	void LevelSetting(const int Level);

	void WaitTimeSetting(const int Level);

private:
	int LShot;
	int BShot;
	int AShot;
	int LMaxShot;
	int WMaxShot;
	int BMaxShot;
	int AMaxShot;
	int LWT;
	int WWT;
	int BWT;
	int AWT;
};

void CreateLevelSet(LevelSet** Level);
void DeleteLevelSet(LevelSet** Level);