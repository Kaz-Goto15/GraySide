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
    hPict_ = Image::Load("black.png");
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
    Image::SetTransform(transform_);
    Image::Draw(hPict_);
}

//�J��
void CreditScreen::Release()
{
}