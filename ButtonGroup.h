#pragma once
#include "Engine/GameObject.h"

//�{�^���W�����Ǘ�����N���X
class ButtonGroup : public GameObject
{

public:
    ButtonGroup(GameObject* parent);    //�R���X�g���N�^
    ~ButtonGroup();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void AddB
};