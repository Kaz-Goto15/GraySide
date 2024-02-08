#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�R���X�g���N�^
CreditScreen::CreditScreen(GameObject* parent)
    :Screen(parent, "CreditScreen")
{
}

//�f�X�g���N�^
CreditScreen::~CreditScreen()
{
}

//������
void CreditScreen::Initialize()
{
    hPict_[PIC_BACKGROUND] = Image::Load("black.png");
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("frame.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("descr.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    //keyHelp.push_back(KEY_CANCEL, "�߂�");
}

//�X�V
void CreditScreen::Update()
{
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }
}

//�`��
void CreditScreen::Draw()
{
    for (int i = 0; i < PIC_MAX; i++) {
        Image::SetTransform(hPict_, transform_);
        Image::Draw(hPict_);
    }
}

//�J��
void CreditScreen::Release()
{
}