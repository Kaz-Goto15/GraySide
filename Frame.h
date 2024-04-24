#pragma once
#include "Engine/GameObject.h"

//�g���Ǘ�����N���X
class Frame : public GameObject
{
    enum FRAME_W {
        W_LEFT= 0,
        W_CENTER,
        W_RIGHT,
        W_MAX,
    };
    enum FRAME_H {
        H_TOP = 0,
        H_CENTER,
        H_BOTTOM,
        H_MAX
    };
    std::string fileName;
    int edge;
    int hFrameImg_;
    Transform tra[FRAME_H::H_MAX][FRAME_W::W_MAX];

    //��E�����Ń}�[�W�����w��
    void TransformFrame(XMINT4 margin) { TransformFrame(margin.x, margin.y, margin.z, margin.w); }
    //��E�����Ń}�[�W�����w��
    void TransformFrame(int up, int right, int down, int left);

public:
    Frame(GameObject* parent);    //�R���X�g���N�^
    ~Frame();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void SetMargin(int up, int right, int down, int left);

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }
};