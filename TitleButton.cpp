#include "TitleButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//�R���X�g���N�^
TitleButton::TitleButton(GameObject* parent):
    GameObject(parent, "TitleButton"),
	buttonTextObj_(nullptr),
	buttonName_("")
{
	std::fill_n(hImg_, MAX, -1);
}

//�f�X�g���N�^
TitleButton::~TitleButton()
{
}

//������
void TitleButton::Initialize()
{
	for (int i = 0; i < MAX; i++) {
		hImg_[i] = Image::Load(LinkImageFile(static_cast<STATE>(i)));
	}
}

//�X�V
void TitleButton::Update()
{
	switch (state)
	{
	case TitleButton::IDLE:		UpdateIdle();	break;
	case TitleButton::SELECT:	UpdateSelect();	break;
	case TitleButton::PUSH:		UpdatePush();	break;
	case TitleButton::SELECTED:	UpdateSelected();	break;
	}
}

//�`��
void TitleButton::Draw()
{
	for (int i = 0; i < MAX; i++) {
		Image::Draw(hImg_[i]);
	}
}

//�J��
void TitleButton::Release()
{
}

void TitleButton::SetText(std::string buttonName)
{
    buttonName_ = buttonName;
}

std::string TitleButton::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Title\\";
	std::string fileName;
	switch (_state)
	{
	case TitleButton::IDLE:		fileName = "btnIdle.png";	break;
	case TitleButton::SELECT:	fileName = "btnSelect.png";	break;
	case TitleButton::PUSH:		fileName = "btnPush.png";	break;
	case TitleButton::SELECTED:	fileName = "btnSelected.png";	break;
	}
	return AssetDir + fileName;
}

void TitleButton::UpdateIdle()
{
	XMFLOAT3 mousePos = Input::GetMousePosition();
}

void TitleButton::UpdateSelect()
{
}

void TitleButton::UpdatePush()
{
}

void TitleButton::UpdateSelected()
{
}

