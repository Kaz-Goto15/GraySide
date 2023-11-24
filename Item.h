#pragma once
#include "Engine/GameObject.h"

class Item : public GameObject
{
    int hModel_;
    int hSound_[2];
public:
    //�R���X�g���N�^
    Item(GameObject* parent);
    ~Item();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //�����ɓ�������
   //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //���WY��ύX
    void SetPositionY(float setY) { transform_.position_.y = setY; }

};