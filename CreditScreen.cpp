#include "CreditScreen.h"

//�R���X�g���N�^
CreditScreen::CreditScreen(GameObject* parent)
    :GameObject(parent, "CreditScreen")
{
}

//�f�X�g���N�^
CreditScreen::~CreditScreen()
{
}

//������
void CreditScreen::Initialize()
{
    //keyHelp.push_back(KEY_CANCEL, "�߂�");
}

//�X�V
void CreditScreen::Update()
{
}

//�`��
void CreditScreen::Draw()
{
    if (enScreen) {
        
    }
}

//�J��
void CreditScreen::Release()
{
}

void CreditScreen::Show() {
    enScreen = true;
}