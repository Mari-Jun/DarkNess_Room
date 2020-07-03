#include "Sound.hpp"

void SoundInit() {
	FMOD_System_Create(&M_System);
	FMOD_System_Init(M_System, Sound20, FMOD_INIT_NORMAL, 0);

	//배경음 생성
	for (int i = 0; i < Sound3; i++) {
		char str[100];
		sprintf_s(str, ".\\Sound\\BKMusic%d.mp3", i + 1);
		FMOD_System_CreateStream(M_System, str, FMOD_LOOP_NORMAL, 0, &M_Sound[i]);
		//0 : 시작 페이지 배경음악
		//1 : 게임 페이지 배경음악
	}

	//2 : 시작 페이지 번개 효과음
	FMOD_System_CreateStream(M_System, ".\\Sound\\Effect1.mp3", FMOD_LOOP_OFF, 0, &M_Sound[2]);

	//3 : 버튼 클릭음
	FMOD_System_CreateStream(M_System, ".\\Sound\\Effect2.mp3", FMOD_LOOP_OFF, 0, &M_Sound[3]);

	//4: 레벨 업 소리
	FMOD_System_CreateStream(M_System, ".\\Sound\\LevelUp.mp3", FMOD_LOOP_OFF, 0, &M_Sound[4]);

	//12,5,6,7 Wide,Bomb,Air Eemey Shot Sound
	FMOD_System_CreateStream(M_System, ".\\Sound\\LineShot.mp3", FMOD_LOOP_OFF, 0, &M_Sound[12]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\WideShot.mp3", FMOD_LOOP_OFF, 0, &M_Sound[5]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\Bomb.mp3", FMOD_LOOP_OFF, 0, &M_Sound[6]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\AirShot.mp3", FMOD_LOOP_OFF, 0, &M_Sound[7]);

	//8: Rankpage 생성 소리
	FMOD_System_CreateStream(M_System, ".\\Sound\\Rank.mp3", FMOD_LOOP_OFF, 0, &M_Sound[8]);

	//9,10,11 : Skill Q,W E
	FMOD_System_CreateStream(M_System, ".\\Sound\\SkillQ.mp3", FMOD_LOOP_OFF, 0, &M_Sound[9]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\SkillW.mp3", FMOD_LOOP_OFF, 0, &M_Sound[10]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\SkillE.mp3", FMOD_LOOP_OFF, 0, &M_Sound[11]);
	
}

void PlayMainBKSound() {
	//현재 Cahnnel0에 재생되는 음악을 정지한다.
	FMOD_Channel_Stop(M_Channel[0]);
	//배경 음악 Sound0를 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[0], NULL, FALSE, &M_Channel[0]);
}

void PlayGameBKSound() {
	//현재 Cahnnel0,1에 재생되는 음악을 정지한다.
	MainPageSoundStop();
	//배경 음악 Sound1를 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[1], NULL, FALSE, &M_Channel[0]);

	//FMOD_System_Update(M_System); <-이거 타이머에 나중에 넣어주세욤~
}

void PlayLightningSound() {
	//효과음 Lightning을 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[2], NULL, FALSE, &M_Channel[1]);
}

void PlayButtonClickSound(){
	//효과음 Effect2.mp3을 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[3], NULL, FALSE, &M_Channel[2]);
}

void PlayLevelUpSound() {
	//효과음 LevelUp을 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[4], NULL, FALSE, &M_Channel[1]);
}

void PlayLineShotSound() {
	//효과음 LineShot을 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[12], NULL, FALSE, &M_Channel[2]);
}

void PlayWideShotSound() {
	//효과음 WideShot을 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[5], NULL, FALSE, &M_Channel[3]);
}

void PlayBombShotSound(int Num) {
	//효과음 BombShot을 재생한다.

	//Num은 Bomb적의 숫자 8개중 한개 즉4~11

	FMOD_System_PlaySound(M_System, M_Sound[6], NULL, FALSE, &M_Channel[4+Num]);
}

void PlayAirShotSound(int Num) {
	//효과음 AirShot을 재생한다.

	//Num은 Air적의 숫자 2개중 한개 즉12~13
	FMOD_System_PlaySound(M_System, M_Sound[7], NULL, FALSE, &M_Channel[12+Num]);
}

void PlayRankPageSound() {
	//효과음 Rank을 재생한다.
	
	FMOD_System_PlaySound(M_System, M_Sound[8], NULL, FALSE, &M_Channel[0]);
}

void PlaySkillQSound() {
	//효과음 SkillQ을 재생한다.

	FMOD_System_PlaySound(M_System, M_Sound[9], NULL, FALSE, &M_Channel[14]);
}

void PlaySkillWSound() {
	//효과음 SkillW을 재생한다.

	FMOD_System_PlaySound(M_System, M_Sound[10], NULL, FALSE, &M_Channel[15]);
}

void PlaySkillESound() {
	//효과음 SkillE을 재생한다.

	FMOD_System_PlaySound(M_System, M_Sound[11], NULL, FALSE, &M_Channel[16]);
}


void MainPageSoundStop() {
	FMOD_Channel_Stop(M_Channel[0]);
	FMOD_Channel_Stop(M_Channel[1]);
}

void GamePageSoundStop() {
	for(int i=0; i<17; i++)
		FMOD_Channel_Stop(M_Channel[i]);
}