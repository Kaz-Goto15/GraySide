#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"

//�L���[�u���Ǘ�����N���X
class CubeSelectIndicator : public GameObject
{
private:
    int hModel;
    XMFLOAT3 Surface2Rotate(Cube::SURFACE surface);
public:
    CubeSelectIndicator(GameObject* parent);    //�R���X�g���N�^
    ~CubeSelectIndicator();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    /// <summary>
    /// �`��ʂ̕ύX
    /// </summary>
    /// <param name="surface">��enum</param>
    void SetSurface(Cube::SURFACE surface);
};