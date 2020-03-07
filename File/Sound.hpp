#pragma once
#include "Resource.hpp"

enum SOUNDTRACK {
	Sound1 = 0, Sound2, Sound3, Sound4, Sound5,
	Sound6, Sound7, Sound8, Sound9, Sound10,
	Sound11, Sound12, Sound13, Sound14, Sound15,
	Sound16, Sound17, Sound18, Sound19, Sound20
};

static FMOD_SYSTEM* M_System;
static FMOD_SOUND* M_Sound[Sound20];
static FMOD_CHANNEL* M_Channel[Sound20];

void SoundInit();

void PlayMainBKSound();				//게임 시작 화면 BGM 재생
void PlayGameBKSound();				//게임 진행 화면 BGM 재생

void PlayLightningSound();			//번개 소리 재생
void PlayButtonClickSound();		//버튼 클릭 소리 재생

void MainPageSoundStop();			//MainPage에서 발생하는 모든 소리 중지