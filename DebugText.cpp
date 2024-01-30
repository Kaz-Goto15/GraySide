#include "DebugText.h"
#include "Engine/Text.h"

//�R���X�g���N�^
DebugText::DebugText(GameObject* parent)
    :GameObject(parent, "DebugText"),
    pos({-640,-360}),
    count(0)
{
}

//�f�X�g���N�^
DebugText::~DebugText()
{
}

//������
void DebugText::Initialize()
{
    txt = new Text();
    txt->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
}

//�X�V
void DebugText::Update()
{
}

//�`��
void DebugText::Draw()
{
    for (int i = 0; i < count; i++) {
        txt->Draw(pos.x, pos.y + 35 * i, pStrList_[i]->c_str(), Text::HORIZONAL_ALIGNMENT::LEFT, Text::VERTICAL_ALIGNMENT::TOP);
    }
}

//�J��
void DebugText::Release()
{
}

void DebugText::AddStrPtr(string* pStr)
{
    count++;
    pStrList_.push_back(pStr);
}
