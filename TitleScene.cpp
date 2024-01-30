#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"

#include "TitleButton.h"
#include "DebugText.h"
using std::to_string;

std::string TitleScene::TitleImgFileName(Img E_IMG)
{
	switch (E_IMG)
	{
	case Img::PIC_BACKGROUND:		return "lobby_bg_720p.png";
	case Img::PIC_TITLE:			return "result_meter.png";
	case Img::PIC_CHARACTER:		return "grayman\\hm.png";
	}
	return "null.png";
}

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	newText(nullptr),
	selectState_(S_SEL_START)
{}

void TitleScene::Initialize() {
	for (int i = 0; i < Img::MAX; i++) {
		hPict_[i] = Image::Load(TitleImgFileName(static_cast<Img>(i)));
	}
	newText = new Text();
	newText->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
	debugText = Instantiate<DebugText>(this);
	for (int i = 0; i < 20; i++) debugText->AddStrPtr(&debugStr[i]);

	InitButton(S_SEL_START, "START", { 180,-240 });
	InitButton(S_SEL_CREDIT, "CREDIT", { 180,-80 });
	InitButton(S_SEL_OPTION, "OPTION", { 180,80 });
	InitButton(S_SEL_EXIT, "EXIT", { 180, 240 });

}
void TitleScene::Update() {
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		Run(selectState_);
	}
	if (Input::IsKeyDown(DIK_9)) {
		Invisible();
	}
}
void TitleScene::Draw() {
	std::string str = "TitleScene: ";
	newText->Draw(40, 40, str.c_str());

	for (int& h : hPict_) {
		//Image::Draw(h);
	}
	XMFLOAT3 mousePos = Input::GetMousePosition();
	//debugStr[0] = "imgSize: " + std::to_string(Image::GetWidth(hImg_)) + ", " + std::to_string(Image::GetHeight(hImg_));
	//debugStr[1] = "imgScale: " + std::to_string(nullScale_.x) + ", " + std::to_string(nullScale_.y);
	debugStr[2] = "mousePos: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y);
	//debugStr[3] = "state:" + to_string(newBtn->state);
	//debugStr[4] = newBtn->GetDebugStr(0);
	//debugStr[5] = newBtn->GetDebugStr(1);
	//debugStr[6] = newBtn->GetDebugStr(2);
	//debugStr[7] = newBtn->GetDebugStr(3);
	//debugStr[8] = newBtn->GetDebugStr(4);
	//debugStr[9] = newBtn->GetDebugStr(5);

}
void TitleScene::Release() {}

void TitleScene::Act(int hAct)
{
	SELECT_STATE ss = static_cast<SELECT_STATE>(hAct);
	switch (ss)
	{
	case TitleScene::S_SEL_START:
		//GameScene?
		break;
	case TitleScene::S_SEL_CREDIT:
		//CreditScene?
		break;
	case TitleScene::S_SEL_OPTION:
		//OptionScreen?
		break;
	case TitleScene::S_SEL_EXIT:
		exit(0);
	default:
		break;
	}
}

void TitleScene::Run(SELECT_STATE& ss) {
	switch (ss)
	{
	case SELECT_STATE::S_SEL_START:
		//FileList.EnDraw();
		manipTarget = MANIP_FILE_LIST;
		break;
	case SELECT_STATE::S_SEL_CREDIT:
		//credit.Show();
		manipTarget = MANIP_CREDIT;
		break;
	case SELECT_STATE::S_SEL_OPTION:
		break;
	case SELECT_STATE::S_SEL_EXIT:
		//ConfirmWIndow cw = new ConfirmWindow();
		//cw.SetMessage("�f�X�N�g�b�v�ɖ߂�܂����H");
		manipTarget = MANIP_CONFIRM_WINDOW;
		break;
	default:
		MessageBox(NULL, "Error", "�v���I�G���[�F�͈͊O�̑I���X�e�[�g", MB_OK);
		exit(1);
	}
}

void TitleScene::InitButton(SELECT_STATE ss, std::string text, XMFLOAT2 pos)
{
	btn[ss] = Instantiate <TitleButton>(this);
	btn[ss]->SetText(text);
	btn[ss]->SetAction(ss);
	btn[ss]->SetPosition(pos.x, pos.y, 0.0f);
}

/*
BUTTON STATE
IDLE:
 �I���O�̃A�j���[�V����
 �J�[�\������������SELECT�Ɉړ�

 �{�^���őI�΂ꂽ�Ƃ�SELECT�Ɉړ�

SELECT:
 �I�𒆂̃A�j���[�V����
 �}�E�X�{�^���������ꂽ��PUSH�Ɉړ�
 �J�[�\�����O�ꂽ��IDLE�Ɉړ�
 �{�^���������ꂽ��SELECTED�Ɉړ�(keydown up�ł͂Ȃ�)
 �{�^�������ɍs�����Ƃ�IDLE�Ɉړ�

PUSH:
 �������A�j���[�V����

 �J�[�\�����O�ꂽ��IDLE�Ɉړ�
 �}�E�X�{�^���������ꂽ�Ƃ��ASELECTED�Ɉړ�

SELECTED:
 �I�����ꂽ�A�j���[�V����
 �������s��
 �������I�������IDLE�Ɉړ�

 �}�E�X�͎����ŏ����ł���
 �{�^����������



�J�[�\�����ڂ����ɗ������̏����Fbtn_select
�{�^����ŉ����A���������Ă��鎞�̏����Fbtn_push
�{�^����ŉ����A�������Ƃ��̏����Fbtn_selected
�����ꂽ�Ƃ��E�{�^����ɖ������̏����Fbtn_idle


�I�𒆂�BTN_ENUM

��in�Ń{�^���t�F�[�h�C�� �I���\
 �{�^���F�I���O/�I��/�I�𒆂�������Ă���/�I����̏�����
 �����ꂽ�Ƃ��̏������l����
 �{�^����o�^����Ƃ���Generate(cmd);
 �\���͐e�̂ق���TitleBtn.count()����for��Draw
 �{�^���������ꂽ��e��Run(COMMAND cmd);���Ă�
main
background
select: logo (���t�F�[�h)
start/option/edit/exit
start��screen�ŐV���ɋL�q
option��screen
edit���u���b�N�A�E�g����editscene
exit�����̂܂��exit(0)�ł���


�{�^���Ƃ��Ēǉ����邩�H
12
34�@�Œǉ������Ƃ�

1�̂Ƃ� �㉺���E 0+2 0+1
2�̂Ƃ� �㉺���E 0+2-1 0
3�̂Ƃ� �㉺���E-2 0 0+1
4�̂Ƃ� �㉺���E-2 0-1 0

12
(3)4�@�Œǉ������Ƃ�

1�̂Ƃ� �㉺���E 0+3 0+1
2�̂Ƃ� �㉺���E 0+2-1 0
3�ɂ������̓��� --+3-3--
4�̂Ƃ� �㉺���E-2 0-3 0

1�̂Ƃ� �㉺���E 0+2 0+1
2�̂Ƃ� �㉺���E 0+2-1 0
3�ɂ������̓��� --+1-2--
4�̂Ƃ� �㉺���E-2 0-1 0

������+2 �����-2 3�ȏ�̂Ƃ������͓���Ȃ� 2�ȉ��̂Ƃ������Ȃ�
�E+1
fadein �C�[�W���O�ԍ��ɉ����ē����x�ύX�@0��100��idle SPACE:end
idle �w�莞�ԑҋ@�@�w�莞�Ԓ��߂�fadeout�� SPACE:end
fadeout �C�[�W���O�ԍ��ɉ����ē����x�ύX�@100��0��end�� SPACE:end
end �\��������̂������fadein �Ȃ���΃^�C�g���V�[����
*/