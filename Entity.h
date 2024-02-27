#pragma once
#include "GameSceneObject.h"

//���������Ǘ�����N���X 
class Entity : public GameSceneObject
{

public:
    Entity(GameObject* parent, const std::string& name);    //�R���X�g���N�^
    ~Entity();                     //�f�X�g���N�^
    virtual void Initialize() override = 0; //������
    virtual void Update() override = 0;     //�X�V
    virtual void Draw() override = 0;       //�`��
    virtual void Release() override = 0;    //���
};