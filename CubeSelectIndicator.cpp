#include "CubeSelectIndicator.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"

XMFLOAT3 CubeSelectIndicator::Surface2Rotate(Cube::SURFACE surface)
{
    //���f���ŏ����(0,1,0)�ɔz�u����
    switch (surface)
    {
    case Cube::SURFACE_TOP: return { 0,0,0 };
    case Cube::SURFACE_BOTTOM:return { 180,0,0 };
    case Cube::SURFACE_LEFT:    return { 0,0,90 };
    case Cube::SURFACE_RIGHT:   return { 0,0,-90 };
    case Cube::SURFACE_FRONT:   return { 90,0,0 };
    case Cube::SURFACE_BACK:    return { -90,0,0 };
    }
}

//�R���X�g���N�^
CubeSelectIndicator::CubeSelectIndicator(GameObject* parent)
    :GameObject(parent, "CubeSelectIndicator")
{
    hModel = -1;
}

//�f�X�g���N�^
CubeSelectIndicator::~CubeSelectIndicator()
{
}

//������
void CubeSelectIndicator::Initialize()
{
    hModel = ModelLoader::Load(ModelLoader::CubeSelectIndicator);
    ModelLoader::ChangeAnim(hModel, "green");
}

//�X�V
void CubeSelectIndicator::Update()
{
}

//�`��
void CubeSelectIndicator::Draw()
{
    Model::SetTransform(hModel, transform_);
    Model::Draw(hModel);
}

//�J��
void CubeSelectIndicator::Release()
{
}

void CubeSelectIndicator::SetSurface(Cube::SURFACE surface)
{
}