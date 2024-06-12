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
    enum MARK {
        MARK_BLANK,
        MARK_O,
        MARK_X,
        MARK_MAX
    };
    enum ROTATE_DIR {
        UP,
        DOWN,
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

    int hModelCube;
    //int hModel_col;
    int hModelMark[MARK_MAX];
    MARK cubeData_[SURFACE_MAX];
    XMFLOAT3 Surface2Rotate(SURFACE surface);
public:
    Cube(GameObject* parent);    //�R���X�g���N�^
    ~Cube();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void SwapData(ROTATE_DIR dir);    //�O���猩����]�������w�肵�A�e�ʂ̃f�[�^�����ւ���

    void SetMark(SURFACE surface, MARK mark);
    MARK GetMark(SURFACE surface) { return cubeData_[surface]; }
};