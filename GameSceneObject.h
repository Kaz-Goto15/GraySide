#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class GameSceneObject : public GameObject
{
protected:
    enum OBJECT_ATTRIBUTE {
        OBJ_FIELD,
        OBJ_ENTITY
    };
    bool isLand;
public:
    GameSceneObject(GameObject* parent, const std::string& name= "Button");    //�R���X�g���N�^
    ~GameSceneObject();                     //�f�X�g���N�^
    virtual void Initialize() override = 0; //������
    virtual void Update() override = 0;     //�X�V
    virtual void Draw() override = 0;       //�`��
    virtual void Release() override = 0;    //���
};