#pragma once
#include "Engine/GameObject.h"
#include "SceneChange.h"
#include "Engine/Text.h"
#include "GameData.h"
#include "KeyConfig.h"
#include "Effect.h"

#include "Player.h"
#include "RivalObject.h"

#include "SelectRect.h"
#include "Health.h"
//�e�X�g�V�[�����Ǘ�����N���X
class GameScene : public GameObject
{
	int hPict_;	//�摜�ԍ�
	int hSound_[3]; //�T�E���h�ԍ�
	XMFLOAT3 camPos_, camTarget_;	//�J���� ���W/�^�Q

	SceneChange* pSC;
	Text* pText;
	std::string despString;
	//�f�o�b�O
	Text* debugTxt;
	bool gamePlaying_, gameStart_;
	Effect* pEffect_ = nullptr;
	Player* pPlayer_ = nullptr;
	RivalObject* pRivalObject_ = nullptr;
	int waitTime_;

	int gameType_;
	
	//�g�Q�ƃA�C�e���������p
	int needleMeter_, itemMeter_;
	int speedMeter_;

	//�G���h���X�p
	Health* pHealth_ = nullptr;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// ���݃Q�[�����J�n����(�J�n�O�̐ڒn�����ړ�+�W�����v���������󒆂ŃL�[������󂯕t���邩)��Ԃ�
	/// </summary>
	/// <returns>true �Q�[���i�s�� false: �J�n�O�E���Ԑ؂�E�ڒn</returns>
	bool IsPlayed() { return gamePlaying_; }
};