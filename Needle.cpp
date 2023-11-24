#include "Needle.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"    
#include "Player.h"
#include "GameData.h"
//�R���X�g���N�^
Needle::Needle(GameObject* parent)
    :GameObject(parent, "Needle"), hModel_(-1)
{
}

//�f�X�g���N�^
Needle::~Needle()
{
}

//������
void Needle::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("needle.fbx");
    assert(hModel_ >= 0);

    transform_.position_.y = 5;
    transform_.position_.x = 15;

    //transform_.position_.x = (float)(rand() % 401 - 200) / 10;

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
  
}

//�X�V
void Needle::Update()
{
    if (transform_.position_.x > -30)
    {
        transform_.position_.x -= GameData::GetSpeed() * 0.05f;
    }
    if (transform_.position_.x < -20)
    {
        KillMe();
    }

}

//�`��
void Needle::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Needle::Release()
{
}

//�����ɓ�������
void Needle::OnCollision(GameObject* pTarget)
{
       //�Ƃ��ɓ��������Ƃ���������
    if (pTarget->GetObjectName() == "Player")//�Ƃ��ɓ���������Player�������鏈��
    {
        if (GameData::GetGamemode() == 1) {
            int dmgs = 50 + rand() % 101;
            GameData::AddHealth(-dmgs);
            GameData::AddTempHealth(-dmgs / 3);
        }
        
        //�Ƃ��ɓ�������Player��������
        //pTarget->KillMe();
        KillMe();
        GameData::AddHits(1);

    }
}
