#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "CsvManager.h"
#include "MenuSelect.h"
#include "SceneChange.h"
#include "KeyConfig.h"

#include "Effect.h"

//�e�X�g�V�[�����Ǘ�����N���X
class RecordScene : public GameObject
{
	int hPict_;    //�摜�ԍ�
	Text* pTextName[5]; //�����ǂ��ɂ����Ď�����������
	Text* pTextOV;
	int quantity;
	CsvManager csv;
	MenuSelect* pMenuSelect;

	//�e�L�X�g����
	std::string OVText;
	int keepNo;
	int OVTextLen;

	//�f�o�b�O
	Text* debugTxt;
	Text* debugTxt2;
	Text* debugTxt3;

	SceneChange* pSC;
	SceneChange* pSCd;

	//�G�t�F�N�g�����Ńf�o�b�O����
	Effect* debugEf;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	RecordScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};