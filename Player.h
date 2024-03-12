#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    enum STATE {
        S_IDLE,
        S_MOVE,
        S_JUMP,
        S_FALL,
        S_DAMAGED,
        S_THROW,
        S_DOWN
    }state_;

    enum AUDIO_ASSET {
        SE_JUMP,
        SE_LAND,
        SE_THROW,
        SE_MAX
    };

    float velY;
    float maxVel;
    int hSound_[SE_MAX]; //�T�E���h�ԍ�
    int hModel_;
    bool nowFly;

    float knockback;
    bool hasHealth;

    float nowIFrame, iFrame;
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
private:
    void UpdateAct(STATE state_);   
    void ChangeState(STATE state);  //��ԑJ��

};