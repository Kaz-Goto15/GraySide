#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
class Cube;
class DebugText;

using std::vector;
//�Ǘ�����N���X
class ModelTestScreen : public Screen
{
    int hModel;

    DebugText* debugtext;
    std::string debugStr[20];
    vector<vector<vector<Cube*>>> cube;
    vector<vector<vector<Transform>>> cubePrevTra;
    vector<vector<vector<Transform>>> cubeNextTra;
    void UpdateStr();

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
            x = 0;
            y = 0;
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
SET,ROTATE�Ŏg���L�[:�O�񃂁[�h�ֈڍs
�E�N���b�N�������Ƀh���b�O:���_��]


*/