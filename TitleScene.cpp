#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
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
}
void TitleScene::Update() {
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		Run(selectState_);
	}
}
void TitleScene::Draw() {
	std::string str = "TitleScene: ";
	newText->Draw(40, 40, str.c_str());

	for (int& h : hPict_) {
		Image::Draw(h);
	}
}
void TitleScene::Release() {}

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