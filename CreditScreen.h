#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class DebugText;
//�N���W�b�g��ʂ��Ǘ�����N���X
class CreditScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_BASIC_FRAME_TEX,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX - 1];

    XMINT4 margin;  //��E����
    int scrW = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//�X�N���[���̕�
    int scrH = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//�X�N���[���̍���
    DebugText* debugtext;
    std::string debugStr[20];
public:
    CreditScreen(GameObject* parent);
    ~CreditScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};