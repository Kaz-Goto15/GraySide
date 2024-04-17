#pragma once
#include "Engine/GameObject.h"

//�g���Ǘ�����N���X
class Frame : public GameObject
{
    enum FRAME_W {
        LEFT= 0,
        CENTER,
        RIGHT,
        MAX,
    };
    enum FRAME_H {
        TOP = 0,
        CENTER,
        BOTTOM,
        MAX
    };
    std::string fileName;
    int edge;
    int hFrameImg_;
    Transform tra[FRAME_H::MAX][FRAME_W::MAX];

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

    void SetMargin(int up, int right, int down, int left)

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }
};