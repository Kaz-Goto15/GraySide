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
    enum MARK {
        MARK_BLANK = -1,
        MARK_O,
        MARK_X
    };
    enum ROTATE_DIR {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        CW,
        CCW
    };
    enum SURFACE {
        SURFACE_TOP,
        SURFACE_BOTTOM,
        SURFACE_LEFT,
        SURFACE_RIGHT,
        SURFACE_FRONT,
        SURFACE_BACK,
        SURFACE_MAX

    };

    MARK cubeData_[SURFACE_MAX];

public:
    Cube(GameObject* parent);    //�R���X�g���N�^
    ~Cube();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
    void RotateCube(ROTATE_DIR dir);    //�O���猩�Ă��̕����։�]����
    void SetMark(SURFACE surface, MARK mark);
};