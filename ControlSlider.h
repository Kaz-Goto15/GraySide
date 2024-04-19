#pragma once
#include "Engine/GameObject.h"

//�X���C�_�[���Ǘ�����N���X
class ControlSlider : public GameObject
{
private:
    int trackSize;  //�g���b�N�̒���
    int value, minValue, maxValue; //�l�A�ő�ŏ�
    POINT thumbPos; //�� �T���ʒu

    //������O���b�h�`���ɂ��ł���悤��
    //bool freeMove;
    //int gridNum;

    enum IMAGE {
        SLIDER_THUMB,
        SLIDER_FORE,
        SLIDER_BK,
        MAX
    };
    int hImg_[IMAGE::MAX];
public:
    int GetValue() { return value; }
protected:
    virtual void InitValue() = 0;   //���ɍő�ŏ��ƌ��ݒl������������R�[�h������

public:
    ControlSlider(GameObject* parent);    //�R���X�g���N�^
    ~ControlSlider();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
};