#pragma once
#include "Engine/GameObject.h"

//�X���C�_�[���Ǘ�����N���X
class ControlSlider : public GameObject
{
private:
    int trackWidth, trackHeight;  //�g���b�N��H,W
    const int defScrX = 1280;
    const int defScrY = 720;
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
    //�l���͈͓���
    bool Between(float value, float min, float max);
public:
    int GetValue() { return value; }
    bool IsEntered();
    void SetImage(IMAGE img, std::string fileName);
    void SetHeight(int height);
    void SetWidth(int width);
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