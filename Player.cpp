#include "Player.h"
#include "ModelLoader.h"
#include "AudioManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Ground.h"
#include "Needle.h"
#include "KeyConfig.h"
#include "Engine/Debug.h"
#include "GameData.h"

//�R���X�g���N�^
Player::Player(GameObject* parent):
    GameObject(parent, "Player"),
    state_(S_IDLE),
    hModel_(-1)
{
    std::fill(hSound_, hSound_ + 3, -1);
    nowFly = false;

    knockback = 0;
    hasHealth = true;
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = ModelLoader::Load(ModelLoader::MODEL::Player);
    assert(hModel_ >= 0);

    maxVel = -0.15f; //���R�����̍ō���

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1.05f, 0), 0.35f);
    AddCollider(collision);
    BoxCollider* collision1 = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0));
    AddCollider(collision1);
  
    //�T�E���h�̃��[�h
    using AudioManager::AUDIO_SOURCE;
    AudioManager::Load(AUDIO_SOURCE::SE_DAMAGED, AUDIO_SOURCE::SE_THROW);
    //std::string audioFileName_[] = { "se_JUMP.wav", "se_LAND.wav", "se_HIT.wav" };
    //for (int i = 0; i < sizeof(audioFileName_) / sizeof(audioFileName_[0]); i++) {
    //    using AudioManager::AUDIO_SOURCE;
    //    AudioManager::Load(AUDIO_SOURCE::SE_DAMAGED);

    //    assert(hSound_[i] >= 0);
    //}

}

//�X�V
void Player::Update()
{
    if (GameData::GetHealth() <= 0) {
        AUDIO_ASSET
    }
    else {
        hasHealth = true;
    }
    if (hasHealth) {
        //���E�̈ړ��ƈړ��͈�
        if (Input::IsKey(KeyConfig::GetKey(KEY_ID_RIGHT))) {
            transform_.position_.x += 0.1f;
            if (transform_.position_.x > -3)transform_.position_.x = -3;
        }
        if (Input::IsKey(KeyConfig::GetKey(KEY_ID_LEFT))) {
            transform_.position_.x -= 0.1f;
            if (transform_.position_.x < -9)transform_.position_.x = -9;
        }

        //�W�����v
        if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_UP_JUMP))) {
            nowFly = true;
            Debug::Log("FLY", true);
            Audio::Play(hSound_[0]);
            velY = 0.6f;
        }
    }
    //�ō����x
    if (transform_.position_.y > 10) {
        transform_.position_.y = 10;
        velY = 0;
    }

    //knockback
    if (knockback > 0) {
        transform_.position_.x -= knockback;
        if (transform_.position_.x < -9)transform_.position_.x = -9;
        knockback -= 0.05f;
    }

    //�d�͍~��
    velY -= 0.05f;
    
    //���R�����̍ō���������Ƃ��㏑������
    if (maxVel > velY)velY = maxVel;
    //���̍�������(�㏑)
    if (Input::IsKey(KeyConfig::GetKey(KEY_ID_DOWN)))velY = -0.55f;

    transform_.position_.y += velY;

    Debug::Log(transform_.position_.y, true);

    Ground* pGround = (Ground*)FindObject("Ground");
    int hGroundModel = pGround->GetModelHandle();
    RayCastData rayData;
    rayData.start = transform_.position_;   //���C�̔��ˈʒu
    rayData.start.y = 0;
    rayData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &rayData); //���C�𔭎�
    
    //���n����
    if (rayData.hit){
        if (transform_.position_.y < 0.01) {
            if (nowFly) {
                nowFly = false;
                Debug::Log("LAND", true);
                Audio::Play(hSound_[1]);
            }
            transform_.position_.y = -rayData.dist;
        }
    }

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Player::Release()
{
}

//�����������̏���
void Player::OnCollision(GameObject* pTarget){
        //���������Ƃ��̏���
    if (pTarget->ExistTag("Enemy", "Neutral")) {    //�^�O������I�u�W�F�N�g�ɓ����������̏���
        ChangeState(S_DAMAGED);
    }
    if(pTarget->ExistTag("item"))
        if (pTarget->GetObjectName() == "Needle")//Bullet�ɓ���������G�������鏈��
        {
            Audio::Play(hSound_[2]);
            knockback = 0.4f;
        }

        //���������Ƃ��̏���

}

float Player::GetPositionY()
{
    return transform_.position_.y;
}

void Player::UpdateAct(STATE state)
{
    bool doOnce
    switch (state)
    {
    case Player::STATE::S_IDLE:
        ModelLoader::ChangeAnim(hModel_, "idle");
        
        break;
    case Player::STATE::S_MOVE:
        break;
    case Player::STATE::S_JUMP:
        break;
    case Player::STATE::S_FALL:
        break;
    case Player::STATE::S_DAMAGED:
        break;
    case Player::STATE::S_THROW:
        break;
    case Player::STATE::S_DOWN:
        break;
    default:
        break;
    }
}

void Player::ChangeState(STATE state)
{
    state_ = state;

    //�estate��doonce�I�������s��
    switch (state)
    {
    case Player::S_IDLE:
        ModelLoader::ChangeAnim(hModel_, "idle");
        break;
    case Player::S_MOVE:
        break;
    case Player::S_JUMP:
        break;
    case Player::S_FALL:
        break;
    case Player::S_DAMAGED:
        break;
    case Player::S_THROW:
        break;
    case Player::S_DOWN:
        break;
    default:
        break;
    }
}
