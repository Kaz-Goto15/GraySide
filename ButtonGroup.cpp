#include "ButtonGroup.h"

//�R���X�g���N�^
ButtonGroup::ButtonGroup(GameObject* parent)
    :GameObject(parent, "ButtonGroup")
{
}

//�f�X�g���N�^
ButtonGroup::~ButtonGroup()
{
}

//������
void ButtonGroup::Initialize()
{
}

//�X�V
void ButtonGroup::Update()
{
}

//�`��
void ButtonGroup::Draw()
{
}

//�J��
void ButtonGroup::Release()
{
}

void ButtonGroup::AddButton(int handle, Button* btn)
{
	//btn[ss] = Instantiate <TitleButton>(this);
	//btn[ss]->SetText(text);
	//btn[ss]->SetAction(ss);
	//btn[ss]->SetPosition(pos.x, pos.y, 0.0f);
}
