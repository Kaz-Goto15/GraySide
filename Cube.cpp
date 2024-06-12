#include "Cube.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"

XMFLOAT3 Cube::Surface2Rotate(SURFACE surface)
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
Cube::Cube(GameObject* parent)
    :GameObject(parent, "Cube")
{
    std::fill_n(hModelMark, MARK_MAX, -1);
    std::fill_n(cubeData_, SURFACE_MAX, MARK_BLANK);
}

//�f�X�g���N�^
Cube::~Cube()
{
}

//������
void Cube::Initialize()
{
    hModelCube = ModelLoader::Load(ModelLoader::MODEL::Cube);
    //hModel_col = ModelLoader::Load(ModelLoader::MODEL::COLOR_YELLOW);
    hModelMark[MARK_BLANK] = ModelLoader::Load(ModelLoader::MODEL::MARK_BLANK);
    hModelMark[MARK_O] = ModelLoader::Load(ModelLoader::MODEL::MARK_O);
    hModelMark[MARK_X] = ModelLoader::Load(ModelLoader::MODEL::MARK_X);
}

//�X�V
void Cube::Update()
{
}

//�`��
void Cube::Draw()
{
    //�I�u�W�F�N�g�̎��ό`��񂩂�`��
    //�L���[�u�͗����̂Ȃ̂ŉ�]���Ă��e�����󂯂Ȃ����e�I�u�W�F�N�g�̉�]�Ń����`�����o�O�邩���ԍŏ��ɑ��
    transform_.rotate_ = { 0,0,0 };
    Model::SetTransform(hModelCube, transform_);
    Model::Draw(hModelCube);
    for (SURFACE surface = static_cast<SURFACE>(0); surface < SURFACE_MAX; static_cast<SURFACE>(surface+1)) {
        transform_.rotate_ = Surface2Rotate(surface);
        Model::SetTransform(hModelMark[cubeData_[surface]], transform_);
        Model::Draw(hModelMark[cubeData_[surface]]);
    }
    //Model::SetTransform(hModel_col, transform_);
    //Model::Draw(hModel_col);
}

//�J��
void Cube::Release()
{
}

void Cube::SwapData(ROTATE_DIR dir)
{
    MARK temp = cubeData_[SURFACE_FRONT];
    switch (dir)
    {
    case Cube::UP:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = temp;
        break;
    case Cube::DOWN:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = temp;
        break;
    case Cube::LEFT:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = temp;
        break;
    case Cube::RIGHT:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = temp;
        break;
    case Cube::CW:
        temp = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = temp;
        break;
    case Cube::CCW:
        temp = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = temp;
        break;
    default:
        break;
    }
}

void Cube::SetMark(SURFACE surface, MARK mark)
{
    cubeData_[surface] = mark;
}

/*
�����(x�����v)
�@���@�@�@�@�O��
���O�E�@���@�����E
�@���@�@�@�@�@��@

������(x�������v)
�@���@�@�@�@�㉺
���O�E�@���@����E
�@���@�@�@�@�@�O�@

������(y�����v)
�@���@�@�@�@�㍶
���O�E�@���@�O�E��
�@���@�@�@�@�@���@

�E����(y�������v)
�@���@�@�@�@��E
���O�E�@���@�㍶�O
�@���@�@�@�@�@���@

���v����(z�������v)
�@���@�@�@�@����
���O�E�@���@���O��
�@���@�@�@�@�@�E�@

�����v����(z�����v)
�@���@�@�@�@�E��
���O�E�@���@��O��
�@���@�@�@�@�@���@
*/