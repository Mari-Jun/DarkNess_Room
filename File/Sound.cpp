#include "Sound.hpp"

void SoundInit() {
	FMOD_System_Create(&M_System);
	FMOD_System_Init(M_System, Sound20, FMOD_INIT_NORMAL, 0);

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
	FMOD_System_CreateStream(M_System, ".\\Sound\\Effect2.mp3", FMOD_LOOP_OFF, 0, &M_Sound[3]);

	//4: ���� �� �Ҹ�
	FMOD_System_CreateStream(M_System, ".\\Sound\\LevelUp.mp3", FMOD_LOOP_OFF, 0, &M_Sound[4]);

	//12,5,6,7 Wide,Bomb,Air Eemey Shot Sound
	FMOD_System_CreateStream(M_System, ".\\Sound\\LineShot.mp3", FMOD_LOOP_OFF, 0, &M_Sound[12]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\WideShot.mp3", FMOD_LOOP_OFF, 0, &M_Sound[5]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\Bomb.mp3", FMOD_LOOP_OFF, 0, &M_Sound[6]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\AirShot.mp3", FMOD_LOOP_OFF, 0, &M_Sound[7]);

	//8: Rankpage ���� �Ҹ�
	FMOD_System_CreateStream(M_System, ".\\Sound\\Rank.mp3", FMOD_LOOP_OFF, 0, &M_Sound[8]);

	//9,10,11 : Skill Q,W E
	FMOD_System_CreateStream(M_System, ".\\Sound\\SkillQ.mp3", FMOD_LOOP_OFF, 0, &M_Sound[9]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\SkillW.mp3", FMOD_LOOP_OFF, 0, &M_Sound[10]);
	FMOD_System_CreateStream(M_System, ".\\Sound\\SkillE.mp3", FMOD_LOOP_OFF, 0, &M_Sound[11]);
	
}

void PlayMainBKSound() {
	//���� Cahnnel0�� ����Ǵ� ������ �����Ѵ�.
	FMOD_Channel_Stop(M_Channel[0]);
	//��� ���� Sound0�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[0], NULL, FALSE, &M_Channel[0]);
}

void PlayGameBKSound() {
	//���� Cahnnel0,1�� ����Ǵ� ������ �����Ѵ�.
	MainPageSoundStop();
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

void PlayLevelUpSound() {
	//ȿ���� LevelUp�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[4], NULL, FALSE, &M_Channel[1]);
}

void PlayLineShotSound() {
	//ȿ���� LineShot�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[12], NULL, FALSE, &M_Channel[2]);
}

void PlayWideShotSound() {
	//ȿ���� WideShot�� ����Ѵ�.
	FMOD_System_PlaySound(M_System, M_Sound[5], NULL, FALSE, &M_Channel[3]);
}

void PlayBombShotSound(int Num) {
	//ȿ���� BombShot�� ����Ѵ�.

	//Num�� Bomb���� ���� 8���� �Ѱ� ��4~11

	FMOD_System_PlaySound(M_System, M_Sound[6], NULL, FALSE, &M_Channel[4+Num]);
}

void PlayAirShotSound(int Num) {
	//ȿ���� AirShot�� ����Ѵ�.

	//Num�� Air���� ���� 2���� �Ѱ� ��12~13
	FMOD_System_PlaySound(M_System, M_Sound[7], NULL, FALSE, &M_Channel[12+Num]);
}

void PlayRankPageSound() {
	//ȿ���� Rank�� ����Ѵ�.
	
	FMOD_System_PlaySound(M_System, M_Sound[8], NULL, FALSE, &M_Channel[0]);
}

void PlaySkillQSound() {
	//ȿ���� SkillQ�� ����Ѵ�.

	FMOD_System_PlaySound(M_System, M_Sound[9], NULL, FALSE, &M_Channel[14]);
}

void PlaySkillWSound() {
	//ȿ���� SkillW�� ����Ѵ�.

	FMOD_System_PlaySound(M_System, M_Sound[10], NULL, FALSE, &M_Channel[15]);
}

void PlaySkillESound() {
	//ȿ���� SkillE�� ����Ѵ�.

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