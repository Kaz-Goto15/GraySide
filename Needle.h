#pragma once
#include "Engine/GameObject.h"

class Needle : public GameObject
{
    int hModel_;
    int time_;
    float a;

public:
    //�R���X�g���N�^
    Needle(GameObject* parent);

    //�f�X�g���N�^
    ~Needle();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
   //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //positionY�ݒ�
    void SetPositionY(float setY) { transform_.position_.y = setY; }
};