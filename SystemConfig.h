#pragma once
#include <Windows.h>

namespace SystemConfig {
	extern int windowHeight;
	extern int windowWidth;
	/// BGM���ʐݒ� 0-100
	/// <param name="vol">����(%)</param>
	void SetVolBGM(int vol);

	/// BGM���ʎ擾
	/// <returns>����(%)</returns>
	int GetVolBGM();

	/// SE���ʐݒ�
	/// <param name="vol">����(%)</param>
	void SetVolSE(int vol);

	/// SE���ʎ擾
	/// <returns>����(%)</returns>
	int GetVolSE();

	/// �t���[�����[�g�w��
	/// <param name="fps">FPS</param>
	void SetFPS(int fps);

	/// �t���[�����[�g�擾
	/// <returns>FPS</returns>
	int GetFPS();

	/// �t���X�N���[����L���ɂ��邩
	/// <param name="b">true=�L�� false=����</param>
	void SetFullScreen(bool b);

	/// �t���X�N���[�����L�����ǂ���
	/// <returns>�L���ł����true</returns>
	bool IsFullScreen();

	/// �E�B���h�E�����ύX
	/// <param name="h">�V�K����</param>
	void SetWindowHeight(int h);

	/// �E�B���h�E���ύX
	/// <param name="w">�V�K��</param>
	void SetWindowWidth(int w);

	/// �E�B���h�E�T�C�Y�ύX
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	void SetWindowSize(int w, int h);

	bool IsResized();
	/// �ݒ�ۑ�
	void SaveConfig();

	/// ������
	void Init();

	bool IsDebug();

	void SetWindowHandle(HWND hwnd);
	HWND GetWindowHandle();
}