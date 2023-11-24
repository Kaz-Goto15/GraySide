#include "ResultScene.h"
#include "Engine/Input.h"
#include "KeyConfig.h"
#include "Engine/Debug.h"
#include "Engine/Audio.h"
//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
	std::fill(hPict_, hPict_ + RESULT_IMG_EOF, -1);
	std::fill(pText, pText + RESULT_IMG_EOF, nullptr);
	phase_ = 0;
	drawImgPhase_ = 0;
	waitTime = 0;
	keyResponse = false;
	pSC = nullptr;
	hSound_ = -1;
	isFinal = false;
}

//������
void ResultScene::Initialize()
{
	//�摜���[�h
	LoadImg(RESULT_IMG_BG, "result_bg.png");
	LoadImg(RESULT_IMG_TIME, "result_time.png");
	LoadImg(RESULT_IMG_SPEED, "result_speed.png");
	LoadImg(RESULT_IMG_METER, "result_meter.png");
	LoadImg(RESULT_IMG_HIT, "result_hit.png");
	LoadImg(RESULT_IMG_SCORE, "result_score.png");

	//�V�[���`�F���W�̋L��
	pSC = Instantiate<SceneChange>(GetParent());
	pSC->ModifySC(SC_BLACK);
	pSC->SetFade(false);

	//�T�E���h���[�h
	hSound_ = Audio::Load("se_PAGE.wav", false, 5);
	assert(hSound_ >= 0);

	//�z�u�E�e�L�X�g������
	for (int i = 0; i < RESULT_IMG_EOF; i++) {
		if (i >= RESULT_IMG_TIME) {
			imgTrans_[i].position_ = { -0.3f, 0.8f + i * -0.3f, 0 };
			imgTrans_[i].scale_ = { 35.0f / 64.0f, 35.0f / 64.0f, 1 };
		}
		pText[i] = new Text;
		pText[i]->Initialize("char_kurokaneEB_aqua1024_35.png", 35, 70, 16);
	}

	//�X�R�A�����E�\��������
	if (GameData::GetGamemode() == 1) {
		score = GameData::GetSpeed() * GameData::GetMeters() - GameData::GetSpeed() * GameData::GetHits();
		finalPhase_ = 3;
		dispContent->insert(dispContent->end(), {RESULT_IMG_BG, RESULT_IMG_SPEED, RESULT_IMG_METER, RESULT_IMG_HIT, RESULT_IMG_SCORE});
	}
	else {
		score = GameData::GetSpeed()* ((1800 - GameData::GetTime()) * GameData::GetMeters() - 30000 * GameData::GetHits());
		finalPhase_ = 5;
		dispContent->insert(dispContent->end(), { RESULT_IMG_BG, RESULT_IMG_TIME, RESULT_IMG_SPEED, RESULT_IMG_METER, RESULT_IMG_HIT, RESULT_IMG_SCORE });
	}
}

//�X�V
void ResultScene::Update()
{
	/*
	{���̃L�[�Ń��U���g���I�����邩}���I�t�̂Ƃ�
	  �҂����Ԃ�-1����
	  (����L�[�������ꂽ)
	    �҂����Ԃ����Z�b�g
		�t�F�[�Y���P���₷
		����炷
	  (�҂����Ԃ�0�ȉ��̂Ƃ�)
	    �҂����Ԃ����Z�b�g����
		�t�F�[�Y���P���₷
		����炷
	�I���̂Ƃ�
	  {����L�[�������ꂽ}
	    �V�[�����ړ�����
	*/

	if (isFinal) {
		if (keyResponse) {
			if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_SELECT))) {
				pSC = Instantiate<SceneChange>(GetParent());
				pSC->ModifySC(SC_LATTICE);
				pSC->SetFade(true);
				pSC->ChangeScene(SCENE_ID_LOBBY);

				keyResponse = false;
			}
		}
	}
	else {
		if (keyResponse) {
			waitTime++;
			if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_SELECT))) {
				waitTime = 0;
				phase_++;
				Audio::Play(hSound_);
			}
			if (waitTime >= WAIT_FRAME) {
				waitTime = 0;
				phase_++;
				Audio::Play(hSound_);
			}

			if (phase_ >= finalPhase_) {
				isFinal = true;
			}
		}else
		if(!FindObject("SceneChange")) {
			keyResponse = true;
			waitTime = WAIT_FRAME;
}
	}
	////Debug::Log("phase_: "); Debug::Log(phase_, true);
	////Debug::Log("waitTime: "); Debug::Log(waitTime, true);

}

//�`��
void ResultScene::Draw()
{
	//�S���`�� 0���珇��
	for (int i = 0; i <= phase_; i++) {
		Image::SetTransform(hPict_[i], imgTrans_[i]);
		Image::Draw(hPict_[i]);
		pText[i]->Draw(
			640- (int)((imgTrans_[i].position_.x) * 640) - 150,
			360- (int)((imgTrans_[i].position_.y) * 360), 
			drawText[i].c_str());
	}
}

//�J��
void ResultScene::Release()
{
}

//�摜���[�h
void ResultScene::LoadImg(int hpict, std::string imgFile)
{
	hPict_[hpict] = Image::Load(imgFile);
	assert(hPict_[hpict] >= 0);
}