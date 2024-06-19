#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
class Cube;
class CubeSelectIndicator;
class DebugText;

using std::vector;
//�Ǘ�����N���X
class ModelTestScreen : public Screen
{
    int hImgBG;
    int hModel;

    const int PIECES = 3;
    vector<vector<vector<Cube*>>> cube;
    vector<vector<vector<Transform>>> cubePrevTra;
    vector<vector<vector<Transform>>> cubeNextTra;
    CubeSelectIndicator* indicator;
    enum ROTATE_DIR {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        CW,
        CCW
    };
    enum MODE {
        MODE_SET,       //���~��ݒu
        MODE_ROTATE,    //�L���[�u����]
        MODE_VIEW       //��]
    }mode;
    enum CONTROL {
        CONTROL_IDLE,
        CONTROL_1P,
        CONTROL_2P
    };
    CONTROL control, nextTurn;
    struct SelectData {
        int x, y, z;
        Cube::SURFACE surface;
        SelectData() {
            x = 1;
            y = 1;
            z = 0;
            surface = Cube::SURFACE::SURFACE_FRONT;
        }
    }selectData;
    void CalcCubeTrans();

    bool isMoving = false;

    const int angleOfRotate = 90;
    ROTATE_DIR dir;
    int rotateNo;
    int rotTime = 0; 

    //�ړ��֘A
    enum DIR {
        X,
        Y,
        Z
    };
    void MoveSelectParts(DIR dir, bool plus, Cube::SURFACE outSurface);
    void MoveSelect();
    void MoveIndicator();

    //�l���͈͓���
    template <class T>
    bool Between(T value, T min, T max) {
        return (min <= value && value <= max);
    }

    //�J�����֘A
    Transform camTra;                       //�J�����ό`���
    float rotSpdX, rotSpdY;                 //�J������]���x
    bool isEnded;                           //�Q�[���I���t���O
    const int CAM_DISTANCE = 10;            //�J�������� �Œ�
    //const float DC_VALUE = 0.05f;         //�J���������l
    const float TH_ZEROSPEED = 0.3f;        //�J�������x0�ɂ���臒l
    const float DC_RATIO = 1.2f;            //�J������������
    const float AT_RATIO = 0.5f;        //�J�����ړ��ʂɑ΂����]�����P��
    const float MAX_CAM_ROTATE_X = 89.9999f;    //�J����X��]�̍ō��p�x����
    const float MIN_CAM_ROTATE_X = -89.9999f;   //�J����X��]�̍Œ�p�x����
    const int LIMIT_CAM_ROTATE_Y = 180;         //�J����Y��]�̊p�x����(�I�[�o�[�t���[���)
    const int DEFAULT_SPEED = 0;                //�J�����̃f�t�H���g���x(0)

    //�f�o�b�O�e�L�X�g
    std::string debugStr[20];
    DebugText* debugtext;
    void UpdateStr();

    /// <summary>
    /// �L���[�u��]�̃g���K�[ �����������ƃt���O�Ǘ�
    /// 
    /// </summary>
    /// <param name="dir">��]���� �O�ォ�猩�đO(��)��(��))���E���v�����v</param>
    /// <param name="no">��]����s/�� [0][0][0]����Ƃ��A0,1,2�Ŏw��</param>
    /// <param name="angle">���x��]�����邩</param>
    void RotateCube(ROTATE_DIR dir, int no, float angle = 90.0f);
    void TurnEnd();
    void Judge();

    /// �J�����֘A�̏���
    void RotateCamera();
    void FinishCamera();
    
public:
    ModelTestScreen(GameObject* parent);
    ~ModelTestScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

/*
SET,ROTATE
SPACE:�ݒu
LSHIFT:�ؑ�
WASD:�㉺���E�ړ�/��]�����ؑ�
E:(ROTATE�̂�)���ؑ�
�E�N���b�N:VIEW�ֈڍs
VIEW
SET,ROTATE�Ŏg���L�[:�O�񃂁[�h�ֈڍs Space�ł����񂶂��
�E�N���b�N�������Ƀh���b�O:���_��]


*/