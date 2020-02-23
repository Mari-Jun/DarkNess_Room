#include "Sound.hpp"

void SoundInit() {
	FMOD_System_Create(&M_System);
	FMOD_System_Init(M_System, Sound10, FMOD_INIT_NORMAL, 0);

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
	FMOD_System_CreateSound(M_System, ".\\Sound\\Effect2.mp3", FMOD_LOOP_OFF, 0, &M_Sound[3]);
	
}

void PlayStartBKSound() {
	//현재 Cahnnel0에 재생되는 음악을 정지한다.
	FMOD_Channel_Stop(M_Channel[0]);
	//배경 음악 Sound0를 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[0], NULL, FALSE, &M_Channel[0]);
}

void PlayGameBKSound() {
	//현재 Cahnnel0,1에 재생되는 음악을 정지한다.
	StartPageSoundStop();
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

void StartPageSoundStop() {
	FMOD_Channel_Stop(M_Channel[0]);
	FMOD_Channel_Stop(M_Channel[1]);
}