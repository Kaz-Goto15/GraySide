#pragma once
#include <vector>

#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "CsvManager.h"
#include "MenuSelect.h"
#include "SceneChange.h"
#include "KeyConfig.h"
#include "Engine/Text.h"

enum RESULT_IMG {
	RESULT_IMG_BG = 0,
	//RESULT_IMG_FRAME,
	RESULT_IMG_TIME,
	RESULT_IMG_SPEED,
	RESULT_IMG_METER,
	RESULT_IMG_HIT,
	RESULT_IMG_SCORE,
	RESULT_IMG_EOF,
};
//�e�X�g�V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
	/*
	�w�i
	//�g
	�X�R�A�摜�Y�~3��4
	
	*/
	//SPD(�o�ߎ���*����-30000*��e��)
	int score = GameData::GetSpeed() * ((1800 - GameData::GetTime()) * GameData::GetMeters() - 30000 * GameData::GetHits());
	int hPict_[RESULT_IMG_EOF];
	Transform imgTrans_[RESULT_IMG_EOF];
	Text* pText[RESULT_IMG_EOF];
	std::string drawText[RESULT_IMG_EOF] = {
		 "",
		 GameData::GetTimeString() + "s",
		 "x" + GameData::GetSpeedString(),
		GameData::GetMeterString() + "m",
		std::to_string(GameData::GetHits()),
		std::to_string(score)
	};
	int phase_;
	int drawImgPhase_;
	int waitTime;
	const int WAIT_FRAME = 40;
	bool keyResponse;
	SceneChange* pSC;
	int hSound_;

	bool isFinal;
	int finalPhase_;
	std::vector<int> dispContent[RESULT_IMG_EOF];
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//imageload
	void LoadImg(int hpict, std::string imgFile);
};