#include "Sound.hpp"

void SoundInit() {
	FMOD_System_Create(&M_System);
	FMOD_System_Init(M_System, Sound10, FMOD_INIT_NORMAL, 0);

	//����� ����
	for (int i = 0; i < Sound3; i++) {
		char str[100];
		sprintf_s(str, ".\\Sound\\BKMusic%d.mp3", i + 1);
		FMOD_System_CreateStream(M_System, str, FMOD_LOOP_NORMAL, 0, &M_Sound[i]);
		//0 : ���� ������ �������
		//1 : ���� ������ �������
	}

	//2 : ���� ������ ���� ȿ����
	FMOD_System_CreateStream(M_System, ".\\Sound\\Effect1.mp3", FMOD_LOOP_OFF, 0, &M_Sound[2]);

	//3 : ��ư Ŭ����
	FMOD_System_CreateSound(M_System, ".\\Sound\\Effect2.mp3", FMOD_LOOP_OFF, 0, &M_Sound[3]);
	
}

void PlayStartBKSound() {
	//���� Cahnnel0�� ����Ǵ� ������ �����Ѵ�.
	FMOD_Channel_Stop(M_Channel[0]);
	//��� ���� Sound0�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[0], NULL, FALSE, &M_Channel[0]);
}

void PlayGameBKSound() {
	//���� Cahnnel0,1�� ����Ǵ� ������ �����Ѵ�.
	StartPageSoundStop();
	//��� ���� Sound1�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[1], NULL, FALSE, &M_Channel[0]);

	//FMOD_System_Update(M_System); <-�̰� Ÿ�̸ӿ� ���߿� �־��ּ���~
}

void PlayLightningSound() {
	//ȿ���� Lightning�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[2], NULL, FALSE, &M_Channel[1]);
}

void PlayButtonClickSound(){
	//ȿ���� Effect2.mp3�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[3], NULL, FALSE, &M_Channel[2]);
}

void StartPageSoundStop() {
	FMOD_Channel_Stop(M_Channel[0]);
	FMOD_Channel_Stop(M_Channel[1]);
}