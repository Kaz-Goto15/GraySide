#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Sample : public GameObject
{

public:
    Sample(GameObject* parent);    //�R���X�g���N�^
    ~Sample();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
};