#include "SystemConfig.h"
#include <assert.h>
#include <Windows.h>
#include <string>
#include "./Include/inicpp.h"
#include "./Engine/Direct3D.h"
//#include <stdlib.h>

namespace SystemConfig {
	int screenWidth = 800;
	int screenHeight = 600;
	int windowWidth = 800;
	int windowHeight = 600;
	int volBGM = 0;
	int volSE = 0;
	int FPS = 0;
	bool isFullScreen = false;
	bool debug = false;
	ini::IniFile confIni;
	bool isResized = false;

	const char* section = "System";
	const char* directory = "Assets";
	const char* filePath = ".\\systemConf.ini";

	HWND windowHandle;

	void SetVolBGM(int vol) {
		volBGM = vol;
		assert(0 <=vol && vol <= 100);
		confIni[section]["vol_bgm"] = vol;
	}
	int GetVolBGM() { return volBGM; }

	void SetVolSE(int vol) {
		volSE = vol;
		assert(0 <= vol && vol <= 100);
		confIni[section]["vol_se"] = vol;
	}
	int GetVolSE() { return volSE; }

	void SetFPS(int fps) {
		FPS = fps;
		confIni[section]["fps"] = fps;
	}
	int GetFPS() { return FPS; }

	void SetFullScreen(bool b) {
		isFullScreen = b;
		confIni[section]["enFullScreen"] = b;

		Direct3D::SetFullScreen(b);
	}

	bool IsFullScreen() { return isFullScreen; }

	void SetWindowHeight(int h)
	{
		windowHeight = h;
		confIni[section]["height"] = h;
	}

	void SetWindowWidth(int w)
	{
		windowWidth = w;
		confIni[section]["width"] = w;
	}

	void SetWindowSize(int w, int h)
	{
		windowHeight = h;
		windowWidth = w;
		confIni[section]["height"] = h;
		confIni[section]["width"] = w;
		isResized = true;
	}

	bool IsResized()
	{
		if (isResized) {
			isResized = false;
			return true;
		}
		return isResized;
	}

	void SaveConfig()
	{
		SetCurrentDirectory(directory);
		confIni.save(filePath);
	}

	void Init() {
		//���r���Ń��j�^�[�ς����肵�ăT�C�Y�ς���Ă��ύX����Ȃ�
		screenWidth = GetSystemMetrics(SM_CXSCREEN);			//�X�N���[����
		screenHeight = GetSystemMetrics(SM_CYSCREEN);			//�X�N���[������

		confIni.load(filePath);									//ini���[�h
		windowWidth = confIni[section]["width"].as<int>();		//�E�B���h�E��
		windowHeight = confIni[section]["height"].as<int>();	//�E�B���h�E����
		volBGM = confIni[section]["vol_bgm"].as<int>();			//BGM����
		volSE = confIni[section]["vol_se"].as<int>();			//SE����
		FPS = confIni[section]["fps"].as<int>();				//FPS�l
		//isFullScreen = confIni[section]["enFullScreen"].as<int>();
		SetFullScreen(confIni[section]["enFullScreen"].as<int>());	//�t���X�N���[���t���O
		debug = confIni[section]["debug"].as<int>();			//�f�o�b�O�t���O
		SystemConfig::AspectRatio::Init();	//�A�X��֘A�̋@�\������
	}

	bool IsDebug(){	return debug;	}

	void SetWindowHandle(HWND hwnd)	{	windowHandle = hwnd;	}
	HWND GetWindowHandle()	{	return windowHandle;	}

	namespace AspectRatio {
		int aspectRatioX;
		int aspectRatioY;

		void Init() {
			const char* section = "Aspect Ratio";
			aspectRatioX = SystemConfig::confIni[section]["width"].as<int>();
			aspectRatioY = SystemConfig::confIni[section]["height"].as<int>();
		}
		bool Between(int val, int min, int max) {
			return (min <= val && val <= max);
		}
		void ConvertWindowSize(int& w, int& h) {
			RECT rc;
			GetWindowRect(SystemConfig::GetWindowHandle(), &rc);
			int windowX = rc.left;
			int windowY = rc.top;

			if (w > screenWidth)w = screenWidth;	//�E�B���h�E���̍ő���X�N���[������
			h = w * aspectRatioY / aspectRatioX;	//���ƃA�X�䂩�獂�������߂�
			if (h > screenHeight)h = screenHeight;	//�E�B���h�E�����̍ő���X�N���[��������
			w = h * aspectRatioX / aspectRatioY;	//�����ƃA�X�䂩�畝�����߂�

			//�E�B���h�E���W�����E�����X�N���[���O�������肵����X�N���[���T�C�Y����E�B���h�E�T�C�Y�������l�ɂ���
			//�f���A���͍l�����ĂȂ�
			if (!Between(windowX, 0, screenWidth - windowX)) windowX = screenWidth - w;
			if (!Between(windowY, 0, screenHeight - windowY)) windowY = screenHeight - h;
		}
	}
}