#pragma once

#include "Engine/GameObject.h"

enum TRANSITION_ID {
    E_LATTICE = 0,
    E_FADEOUT_BLACK,
    E_FADEIN_BLACK,
    E_FADEOUT_WHITE,
    E_FADEIN_WHITE,
};
enum STATE {
    S_IDLE,
    S_RUN
};
//�t�B���^���ʂ̏W�����Ǘ�
namespace Transition {

    void Initialize();
    void Load();
    void Run(TRANSITION_ID tID, float sec, int easeNum = 1);
}

//class Transition : public GameObject
//{
//    //��΂�����������̕��@�Œ萔����Ȃ��Ă��������� ���͎蓮�ł��� �����Ǝ��Ԃ�����Ȃ�
//    TransitionAnim* pChangeAnim[32][18];
//    int animpts;
//    int nowFrame;
//    bool fade_;
//    bool mvSwitch;
//    bool tileReset;
//    SCENE_ID sceneName;
//
//    int hPict_;
//    int scID;
//    int waitTime;
//    double sinx;
//    double val;
//public:
//    Transition(GameObject* parent);
//    ~Transition();
//    void Initialize() override;
//    void Update() override;
//    void Draw() override;
//    void Release() override;
//
//    void SetFade(bool _fade) { fade_ = _fade; }
//    //SetFade�͔p���\��
//    void SetState(SCENE_CHANGE_ID _mode, bool _fade) {
//
//    }
//    bool IsFinished();
//
//    void ChangeScene(SCENE_ID sceneName_);
//    void ModifySC(SCENE_CHANGE_ID sc, int _wait = 0);
//    void Init();
//};