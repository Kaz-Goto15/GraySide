#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class DebugText;
class Button;
//�N���W�b�g��ʂ��Ǘ�����N���X
class OptionScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_BASIC_FRAME_TEX,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    XMINT4 frameMargin;  //��E����
    float frameScale;    //�σt���[���g�嗦
    XMFLOAT3 framePos;

    DebugText* debugtext;
    Button* backBtn;
    std::string debugStr[20];
public:
    OptionScreen(GameObject* parent);
    ~OptionScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void ButtonAct(int hAct);
};