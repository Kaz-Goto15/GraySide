#pragma once
#include "Entity.h"
class TestEntity : public Entity
{
public:
    TestEntity(GameObject* parent);    //�R���X�g���N�^
    ~TestEntity();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
};

