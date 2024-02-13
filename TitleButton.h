#pragma once
#include "Button.h"
//�^�C�g���̃{�^�����Ǘ�����N���X
class TitleButton : public Button
{
public:
    TitleButton(GameObject* parent);    //�R���X�g���N�^
    ~TitleButton();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
    std::string LinkImageFile(STATE state) override;
private:
};