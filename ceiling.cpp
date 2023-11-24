#include "ceiling.h"
#include "Engine/Model.h"
//�R���X�g���N�^
ceiling::ceiling(GameObject* parent)
	: GameObject(parent, "ceiling"), hModel_(-1)

{
}

//������
void ceiling::Initialize()
{

	//���f���Ǎ�
	hModel_ = Model::Load("floor.fbx");
	assert(hModel_ >= 0);

	 //�V��ʒu�E�R���C�_�[
	transform_.position_.x = 40;
    transform_.position_.y = 18.0f;
	BoxCollider* collision = new BoxCollider(XMFLOAT3(-40, -5.8f, 0), XMFLOAT3(70, 0, 100));
	AddCollider(collision);

}

//�X�V
void ceiling::Update()
{
}

//�`��
void ceiling::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void ceiling::Release()
{
}
