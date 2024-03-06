#pragma once
#include "Button.h"
//�^�C�g���̃{�^�����Ǘ�����N���X
class ButtonGP : public Button
{
public:
    ButtonGP(GameObject* parent);    //�R���X�g���N�^
    ~ButtonGP();                     //�f�X�g���N�^
    std::string LinkImageFile(STATE state) override;
    void Init() override;
private:
    void DrawIdle() override;
    void DrawSelect() override;
    void DrawPush() override;
    void DrawSelected() override;
    int hButtonShadow_;
    int shadowXY;
};