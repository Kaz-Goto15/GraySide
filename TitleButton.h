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
    Text::HORIZONAL_ALIGNMENT hAl;
    Text::VERTICAL_ALIGNMENT vAl;
    int actHandle_;
    XMINT4 clip = { 0,0,128,128 };
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

    //���g(�{�^��)�Ɛe�̑I���X�e�[�g��R�Â���
    void SetAction(int hAct);

    //�����I���Ɩ��ł��Ă��邪�A�����I��IDLE��Ԃɂ���֐�
    void EndAct() { state = IDLE; }
private:
    void UpdateIdle();
    void UpdateSelect();
    void UpdatePush();
    void UpdateSelected();

    bool IsEntered();
    bool Between(float value, float min, float max);
};