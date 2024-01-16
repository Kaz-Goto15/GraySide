#pragma once
#include "Engine/GameObject.h"
#include "StageData.h"
#include <vector>

using std::vector;

//�G�f�B�^�̃X�e�[�W�v���r���[���Ǘ�����N���X
class StageView : public GameObject
{
    STAGE_DATA* pStageData_;
    int hModel[(int)TILE_TAG::MAX];

public:
    StageView(GameObject* parent);    //�R���X�g���N�^
    ~StageView();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
};