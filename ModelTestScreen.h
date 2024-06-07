#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
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
public:
    ModelTestScreen(GameObject* parent);
    ~ModelTestScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};