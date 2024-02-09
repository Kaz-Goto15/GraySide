#include "SystemConfig.h"
#include <assert.h>
#include <Windows.h>
//#include <stdlib.h>

namespace SystemConfig {
	int screenWidth = 800;
	int screenHeight = 600;
	int volBGM = 0;
	int volSE = 0;
	int FPS = 0;
	bool isFullScreen = false;

	void SetVolBGM(int vol) {
		volBGM = vol;
		assert(vol < 0 || vol > 100);
	}
	int GetVolBGM() { return volBGM; }

	void SetVolSE(int vol) {
		volSE = vol;
		assert(vol < 0 || vol > 100);
	}
	int GetVolSE() { return volSE; }

	void SetFPS(int fps) { FPS = fps; }
	int GetFPS() { return FPS; }

	void EnableFullScreen(bool b) { isFullScreen = b; }
	bool IsFullScreen() { return isFullScreen; }

	void Init() {
		SetCurrentDirectory("Assets");
		const char* section = "System";
		const char* iniFile = ".\\systemConf.ini";

		screenWidth = GetPrivateProfileInt(section, "width", screenWidth, iniFile);		//�X�N���[���̕�
		screenHeight = GetPrivateProfileInt(section, "height", screenHeight, iniFile);	//�X�N���[���̍���
		SetVolBGM(GetPrivateProfileInt(section, "vol_bgm", volBGM, iniFile));		//BGM
		SetVolSE(GetPrivateProfileInt(section, "vol_se", volSE, iniFile));			//SE
		SetFPS(GetPrivateProfileInt(section, "fps", 60, iniFile));					//FPS�i��ʍX�V���x�j
		EnableFullScreen(GetPrivateProfileInt(section, "enFullScreen", 0, iniFile));//�t���X�N���[���̗L������
	}
}