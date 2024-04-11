#pragma once
#include "Engine/GameObject.h"

//�g���Ǘ�����N���X
class Frame : public GameObject
{
    const int FRAME_������
    int hFrameImg_;
    Transform tra[3][3];
public:
    Frame(GameObject* parent);    //�R���X�g���N�^
    ~Frame();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
    
    //��E�����Ń}�[�W�����w��
    void TransformFrame(XMINT4 margin) { TransformFrame(margin.x, margin.y, margin.z, margin.w); }
    //��E�����Ń}�[�W�����w��
    void TransformFrame(int up, int right, int down, int left);


    template <class T>
    T Half(T* value) { return value / 2.0f };
};