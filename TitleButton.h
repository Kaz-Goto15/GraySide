#pragma once
#include "Button.h"
//�^�C�g���̃{�^�����Ǘ�����N���X
class TitleButton : public Button
{
public:
    TitleButton(GameObject* parent);    //�R���X�g���N�^
    ~TitleButton();                     //�f�X�g���N�^
    std::string LinkImageFile(STATE state) override;
    void Init() override;
private:
};