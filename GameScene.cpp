#include "GameScene.h"
#include "Engine/Image.h"
#include "Needle.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include"Engine/Debug.h"
#include "SelectRect.h"
#include <sstream>
//�R���X�g���N�^
GameScene::GameScene(GameObject* parent)
	: GameObject(parent, "GameScene")
{
	hPict_ = -1;
	std::fill(hSound_, hSound_ + 3, -1);
	pSC = nullptr;
	camPos_ = { 0,2,-13 };
	camTarget_ = { 0,5,0 };
	pText = nullptr;
	debugTxt = nullptr;
	gamePlaying_ = false;
	gameStart_ = false;
	waitTime_ = 100;

	gameType_ = -1;

	needleMeter_ = 0;
	itemMeter_ = 0;
	speedMeter_ = 0;
}

//������
void GameScene::Initialize()
{
	//�f�[�^��������Ԃ֖߂�
	GameData::Reset();

	//debug
	pText = new Text;
	pText->Initialize("char_kurokaneEB_aqua512_30.png", 30, 60, 16);

	//debugTxt = new Text;
	//debugTxt->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
	//debugTxt->setAlpha(128);
	despString = "";
	pSC = Instantiate<SceneChange>(GetParent());
	pSC->SetFade(false);

	//�w�i���[�h
	hPict_ = Image::Load("game_bg.png");
	assert(hPict_ >= 0);

	//�T�E���h�f�[�^�̃��[�h
	// TODO: �X�^�[�g�ƃG���h����SE��BGM���쐬�E�e����ɋL�q
	std::string audioFileName_[]= { "se_WIND.wav", "bgm_GAME.wav", "se_POPUP.wav"};
	for (int i = 0; i < sizeof(audioFileName_) / sizeof(audioFileName_[0]); i++) {
		if (i < 2)hSound_[i] = Audio::Load(audioFileName_[i], true);
		else hSound_[i] = Audio::Load(audioFileName_[i], false);

		assert(hSound_[i] >= 0);
	}
	Audio::Play(hSound_[0]);
	//�J�����ʒu(�Œ�)
	Camera::SetPosition(camPos_);
	Camera::SetTarget(camTarget_);

	//�v���C���[�A�G�A�X�e�[�W�̕\��
	pPlayer_ = Instantiate<Player>(this);
	pRivalObject_ = Instantiate<RivalObject>(this);
	
	gameType_ = GameData::GetGamemode();
	if(gameType_ == 1)pHealth_ = Instantiate<Health>(this);
}

//�X�V
void GameScene::Update()
{
	//GameObject�N���X�̃e�X�g
	if (Input::IsKey(DIK_T)) {
		transform_.scale_.x += 0.005f;
		transform_.scale_.y += 0.005f;
		SetScale(transform_.scale_.x, -1, 0, 0);
		//std::list<GameObject*>*
	}
	if (Input::IsKey(DIK_G)) {
		transform_.scale_.x -= 0.005f;
		transform_.scale_.y -= 0.005f;
		SetScale(transform_.scale_.x, -1, 0, 0);
		Debug::Log("����Ă�H");
	}

	Debug::Log(std::to_string(GameData::GetMeters()), true);
	//�Q�[���V�X�e��
	if (1) {
		//�J�n�O
		if (gameStart_ == false && Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_UP_JUMP))) {
			gameStart_ = true;
			gamePlaying_ = true;
			Audio::Stop(hSound_[0]);
			Audio::Play(hSound_[1]);
			Audio::Play(hSound_[2]);
			pRivalObject_->SetPlaying(gamePlaying_);
			pEffect_ = Instantiate<Effect>(this);
			pEffect_->SetEffect(EFFECT_GO);
		}

		if (gamePlaying_) {
			//�Q�[����
			needleMeter_ += GameData::GetSpeed();
			itemMeter_ += GameData::GetSpeed();
			if (needleMeter_ >= 300) {
				needleMeter_ = 0;
				pRivalObject_->SpawnNeedle();
			}
			if (itemMeter_ >= 400) {
				itemMeter_ = 20;
				pRivalObject_->SpawnItem();
			}

			if (gameType_ == 0) {
				GameData::AddTime(-1);
				GameData::AddMeters(GameData::GetSpeed());
				//�n�ʂɗ�����
				if (pPlayer_->GetPositionY() <= 0.0f && GameData::GetTime() < 1790) {
					Audio::Stop(hSound_[1]);
					Audio::Play(hSound_[2]);
					gamePlaying_ = false;
					pRivalObject_->SetPlaying(gamePlaying_);
					pEffect_ = Instantiate<Effect>(this);
					pEffect_->SetEffect(EFFECT_GAME_END);
				}
				//���Ԑ؂�
				if (GameData::GetTime() == 0) {
					Audio::Stop(hSound_[1]);
					Audio::Play(hSound_[2]);
					gamePlaying_ = false;
					pRivalObject_->SetPlaying(gamePlaying_);
					pEffect_ = Instantiate<Effect>(this);
					pEffect_->SetEffect(EFFECT_TIME_UP);
				}
			}

			//�Q�[����
			if (gameType_ == 1) {

				speedMeter_ += GameData::GetSpeed();
				if (speedMeter_ >= 1000) {
					speedMeter_ = 0;
					GameData::AddSpeed(1);
				}

				GameData::AddMeters(GameData::GetSpeed());

				//�n�ʂɗ�����
				if (pPlayer_->GetPositionY() <= 0.0f && GameData::GetMeters() >10) {
					Audio::Stop(hSound_[1]);
					Audio::Play(hSound_[2]);
					gamePlaying_ = false;
					pRivalObject_->SetPlaying(gamePlaying_);
					pEffect_ = Instantiate<Effect>(this);
					pEffect_->SetEffect(EFFECT_GAME_END);
				}
			}

		}

		//�I��
		if (gameStart_ && !gamePlaying_) {
			waitTime_--;
			if (waitTime_ == 0) {
				pSC = Instantiate<SceneChange>(GetParent());
				pSC->ModifySC(SC_BLACK);
				pSC->SetFade(true);
				pSC->ChangeScene(SCENE_ID_RESULT);
			}
		}

	}

	if (gameType_ == 0) {
		despString = "Time: " + GameData::GetTimeString() + "sec  Flying: " + GameData::GetMeterString() + "m";
	}
	if (gameType_ == 1) {
		despString = "                   Flying: " + GameData::GetMeterString() + "m";
	}
	//debug camera
	/*
	if (1) {
		if (Input::IsKeyDown(DIK_1))camPos_.x++;
		if (Input::IsKeyDown(DIK_2))camPos_.x--;
		if (Input::IsKeyDown(DIK_3))camPos_.y++;
		if (Input::IsKeyDown(DIK_4))camPos_.y--;
		if (Input::IsKeyDown(DIK_5))camPos_.z++;
		if (Input::IsKeyDown(DIK_6))camPos_.z--;
		if (Input::IsKeyDown(DIK_7))camTarget_.x++;
		if (Input::IsKeyDown(DIK_8))camTarget_.x--;
		if (Input::IsKeyDown(DIK_9))camTarget_.y++;
		if (Input::IsKeyDown(DIK_0))camTarget_.y--;
		if (Input::IsKeyDown(DIK_MINUS))camTarget_.z++;
		if (Input::IsKeyDown(DIK_CIRCUMFLEX))camTarget_.z--;
		Camera::SetPosition(camPos_);
		Camera::SetTarget(camTarget_);
	}
	*/
}

//�`��
void GameScene::Draw()
{
	//�w�i���W�w��E�`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	//�e�L�X�g�`��
	pText->Draw(30, 30, despString.c_str());
	//�J�����̃f�o�b�O
	//std::stringstream ss;
	//ss <<
	//	"camPos:( " <<
	//	(int)camPos_.x << " , " <<
	//	(int)camPos_.y << " , " <<
	//	(int)camPos_.z << " ) " <<
	//	"Tag:( " <<
	//	(int)camTarget_.x << " , " <<
	//	(int)camTarget_.y << " , " <<
	//	(int)camTarget_.z << " ) ";
	//debugTxt->Draw(20, 100, ss.str().c_str());
}

//�J��
void GameScene::Release()
{
}