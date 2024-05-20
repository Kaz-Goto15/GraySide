#include "ControlSlider.h"
#include "./Engine/Input.h"
#include "./Engine/Image.h"
#include "SystemConfig.h"

//�R���X�g���N�^
ControlSlider::ControlSlider(GameObject* parent)
    :GameObject(parent, "ControlSlider"),
	trackWidth(420),
	trackHeight(50)
{
}

//�f�X�g���N�^
ControlSlider::~ControlSlider()
{
}

//������
void ControlSlider::Initialize()
{
	//�摜�Ǎ�
	hImg_[SLIDER_THUMB] = Image::Load("Slider\\sliderThumb.png");
	hImg_[SLIDER_FORE] = Image::Load("Slider\\sliderFore.png");
	hImg_[SLIDER_BK] = Image::Load("Slider\\sliderBack.png");

	//�g���b�N�̕�
	float trackWRatio = defScrX / trackWidth;
	float trackHRatio = defScrY / trackHeight;
	XMFLOAT3 imgSize[IMAGE::MAX];
	imgSize[SLIDER_THUMB] = Image::GetSize(hImg_[SLIDER_THUMB]);
	imgSize[SLIDER_FORE] = Image::GetSize(hImg_[SLIDER_FORE]);
	imgSize[SLIDER_BK] = Image::GetSize(hImg_[SLIDER_BK]);
	//int imgBackW = Image::GetWidth(hImg_[SLIDER_BK]);
	//int imgBackH = Image::GetHeight(hImg_[SLIDER_BK]);
	Transform traImage[IMAGE::MAX];
	for (int i = 0; i < IMAGE::MAX; i++)
		traImage[hImg_[i]].scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[i].x;
		traImage[hImg_[i]].scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[i].x;
	}
	//traImageBack.scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgBackW;
	//traImageBack.scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgBackH;
	
	/*
	FORE��BK�͓����T�C�Y����Ȃ��Ƃ����Ȃ��H�Ⴄ�T�C�Y�̏ꍇ���T�C�Y���邩�������~�߂�K�v������
	*/
}

//�X�V
void ControlSlider::Update()
{
	if (IsEntered()) {
		//�}�E�X�݂̂ɂ��܂���?�͂�
		//������Ă�Ƃ���
		if (Input::IsMouseButtonDown(0)) {

		}
	}

	if (Input::IsKey(DIK_1)) {
		transform_.position_.x++;
	}
	if (Input::IsKey(DIK_2)) {
		transform_.position_.x--;
	}
	if (Input::IsKey(DIK_3)) {
		transform_.position_.y++;
	}
	if (Input::IsKey(DIK_4)) {
		transform_.position_.y--;
	}
}

//�`��
void ControlSlider::Draw()
{
	for (int& img : hImg_) {
		Image::Draw(img);
	}
}

//�J��
void ControlSlider::Release()
{
}

bool ControlSlider::IsEntered()
{
	////1280x720�Ő������ꂽ���̂����݂̃X�N���[���T�C�Y����
	//Transform buttonTra = Image::GetTransform(hImg_[state]);
	//
	//XMFLOAT3 imageSize = {
	//	Image::GetSize(hImg_[state]).x * transform_.scale_.x,
	//	Image::GetSize(hImg_[state]).y * transform_.scale_.y,
	//	Image::GetSize(hImg_[state]).z * transform_.scale_.z
	//};
	//XMFLOAT3 mousePos = Input::GetMousePosition();
	//if (
	//	Between(mousePos.x,
	//		buttonTra.position_.x + SystemConfig::screenWidth / 2.0f - imageSize.x / 2.0f,
	//		buttonTra.position_.x + SystemConfig::screenWidth / 2.0f + imageSize.x / 2.0f) &&
	//	Between(mousePos.y,
	//		buttonTra.position_.y + SystemConfig::screenHeight / 2.0f - imageSize.y / 2.0f,
	//		buttonTra.position_.y + SystemConfig::screenHeight / 2.0f + imageSize.y / 2.0f)
	//	) {
	//	return true;
	//}
	return false;
}