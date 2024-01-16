#include "Screen.h"
#include "Engine/Image.h"

//�R���X�g���N�^
Screen::Screen(GameObject* parent) :
    GameObject(parent, "Screen"),
{
    parent->Leave();
}

//�f�X�g���N�^
Screen::~Screen()
{
}

//������
void Screen::Initialize()
{
}

//�X�V
void Screen::Update()
{
}

//�`��
void Screen::Draw()
{
    if (enScreen_) {
        Image::Draw(hPictBar_);

    }
}

//�J��
void Screen::Release()
{
}

void Screen::Close()
{
    this->Leave();
    GetParent()->Enter();
    CloseAnim();
    KillMe();
}

void Screen::AddInput(Screen_RESOURCE si) {
    supportInputList_.push_back(si);
}