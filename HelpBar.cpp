#include "HelpBar.h"
#include "Engine/Image.h"

//�R���X�g���N�^
HelpBar::HelpBar(GameObject* parent):
    GameObject(parent, "HelpBar"),
    enScreen_(false),
    hPictBar_(-1)

{
}

//�f�X�g���N�^
HelpBar::~HelpBar()
{
}

//������
void HelpBar::Initialize()
{
    hPictBar_ = Image::Load("bar.png");
}

//�X�V
void HelpBar::Update()
{
}

//�`��
void HelpBar::Draw()
{
    if (enScreen_) {
        Image::Draw(hPictBar_);

    }
}

//�J��
void HelpBar::Release()
{
}

void HelpBar::Show() {
    enScreen_ = true;
}
void HelpBar::Hide() {
    enScreen_ = false;
}

void HelpBar::AddInput(HELPBAR_RESOURCE si) {
    supportInputList_.push_back(si);
}