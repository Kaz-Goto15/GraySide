#pragma once

namespace SystemConfig {
	extern int screenHeight;
	extern int screenWidth;
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
	void EnableFullScreen(bool b);

	/// �t���X�N���[�����L�����ǂ���
	/// <returns>�L���ł����true</returns>
	bool IsFullScreen();

	/// ������
	void Init();
}