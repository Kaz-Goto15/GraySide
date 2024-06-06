#pragma once
#include "Engine/GameObject.h"

//�L���[�u���Ǘ�����N���X
class Cube : public GameObject
{
    enum MODEL_ENUM {
        CUBE,
        FRONT_COLOR,
        BACK_COLOR,
        LEFT_COLOR,
    };
    int hModel_;
    int hModel_col;
public:
    Cube(GameObject* parent);    //�R���X�g���N�^
    ~Cube();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
};