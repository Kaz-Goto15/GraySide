#include "Cube.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Cube::Cube(GameObject* parent)
    :GameObject(parent, "Cube")
{
}

//�f�X�g���N�^
Cube::~Cube()
{
}

//������
void Cube::Initialize()
{
    hModel_ = ModelLoader::Load(ModelLoader::MODEL::Cube);
}

//�X�V
void Cube::Update()
{
}

//�`��
void Cube::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Cube::Release()
{
}