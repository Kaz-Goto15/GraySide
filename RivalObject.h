#pragma once
#include <vector>
#include "Engine/GameObject.h"
#include "SceneChange.h"
#include "Item.h"
#include "Needle.h"

//�e�X�g�V�[�����Ǘ�����N���X
class RivalObject : public GameObject
{
	int hModel_;
	int hPict_;	//�摜�ԍ�
	bool nowPlaying = false;
	int Switch = 0;
	int time_;
	int a;

	const int LOOP_NEEDLE_ARRAY = 30;
	int randFill[10];
	Item* pItem;
	Needle* pNeedle[30];	//�Ȃ�constint������
	int setNeedlePtr = 0;

	SceneChange* pSC;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	RivalObject(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool IsPlaying() { return nowPlaying; }
	void SetPlaying(bool state) { nowPlaying = state; }

	void SpawnNeedle();
	void SpawnItem();
};