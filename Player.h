#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    int hModel_;
    float velY;
    float maxVel;
    int hSound_[3]; //�T�E���h�ԍ�
    bool nowFly;

    float knockback;
    bool hasHealth;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    void OnCollision(GameObject* pTarget);
    float GetPositionY();
};
