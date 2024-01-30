#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
//�^�C�g���̃{�^�����Ǘ�����N���X
class TitleButton : public GameObject
{
    enum STATE {
        IDLE,
        SELECT,
        PUSH,
        SELECTED,
        MAX
    };
    Text* buttonTextObj_;
    std::string buttonName_;
    int hImg_[MAX];
    int scrW, scrH;
public:
    STATE state;
    TitleButton(GameObject* parent);    //�R���X�g���N�^
    ~TitleButton();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
    void SetText(std::string buttonName);
    std::string LinkImageFile(STATE state);

    std::string GetDebugStr(int i);
private:
    void UpdateIdle();
    void UpdateSelect();
    void UpdatePush();
    void UpdateSelected();

    bool IsEntered();
};