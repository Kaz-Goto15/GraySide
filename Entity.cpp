#include "Entity.h"
#include <cmath>
//�R���X�g���N�^
Entity::Entity(GameObject* parent, const std::string& name)
    :GameSceneObject(parent, name)
{
}

//�f�X�g���N�^
Entity::~Entity()
{
}

//������
void Entity::Initialize()
{
}

//�X�V
void Entity::Update()
{
    using std::sqrtf;
    using std::powf;
    XMFLOAT3 playerPos = FindObject("Player")->GetPosition();   //���ꎀ�ʂقǃR�X�g
    if (sqrtf(powf(playerPos.x - transform_.position_.x, 2.f) + powf(playerPos.y - transform_.position_.y, 2.0f) + powf(playerPos.z - transform_.position_.z, 2.0f))
        < 5)Visible();
    else Invisible();
}

//�`��
void Entity::Draw()
{
}

//�J��
void Entity::Release()
{
}