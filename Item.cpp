#include "Item.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"    
#include "Player.h"
#include "GameData.h"
#include "Engine/Audio.h"
//�R���X�g���N�^
Item::Item(GameObject* parent)
    :GameObject(parent, "Item")
{
    hModel_ = -1;
    hSound_[0] = -1;
    hSound_[1] = -1;
}

//�f�X�g���N�^
Item::~Item()
{
}

//������
void Item::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("item.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = 5;
    transform_.position_.x = 15;
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.3f, 0), 0.2f);
    AddCollider(collision);

    //SE load
    hSound_[0] = Audio::Load("se_SPEEDUP.wav", false, 5);
    hSound_[1] = Audio::Load("se_HEAL.wav",false, 5);
    assert(hSound_[0] >= 0);
    assert(hSound_[1] >= 0);
}

//�X�V
void Item::Update()
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
void Item::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Item::Release()
{
}

//�����ɓ�������
void Item::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player")//Player�ɓ���������Item�������鏈��
    {
        if (GameData::GetGamemode() == 0) {
            Audio::Play(hSound_[0]);
            GameData::AddSpeed(1);
        }
        if (GameData::GetGamemode() == 1) {
            Audio::Play(hSound_[1]);
            GameData::SetHealth(GameData::GetTempHealth());
            //GameData::SetTempHealth(GameData::GetHealth());
        }
        //�e������������G��������  //�e������������G��������
        this->KillMe();

    }

}
