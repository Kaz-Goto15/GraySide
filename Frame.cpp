#include "Frame.h"
#include "Engine/Image.h"

#include "SystemConfig.h"

//�R���X�g���N�^
Frame::Frame(GameObject* parent)
    :GameObject(parent, "Frame"),
    hFrameImg_(-1)
{
}

//�f�X�g���N�^
Frame::~Frame()
{
}

//������
void Frame::Initialize()
{
     hFrameImg_ = Image::Load("Screen/frame256_2.png");
}

//�X�V
void Frame::Update()
{
}

//�`��
void Frame::Draw()
{
    Image::Draw(hFrameImg_);
}

//�J��
void Frame::Release()
{
}

void Frame::TransformFrame(int up, int right, int down, int left)
{
    Image::SetRect(hFrameImg_, 0, 0, edge, edge);

    using namespace SystemConfig;
    //frame�\�z
    for (int y = 0; y < 3; y++) {
        switch (y) {
        case 0:
            frameTra.position_.y = (float)(-screenHeight + (frameMargin.x + frameMargin.z + edge)) / 2.0f;
            frameTra.scale_.y = 1;
            break;
        case 1:
            frameTra.position_.y = 0;
            frameTra.scale_.y = (float)(screenHeight - (frameMargin.x + frameMargin.z + edge + edge)) / (float)edge;
            break;
        case 2:
            frameTra.position_.y = (float)(screenHeight - (frameMargin.x + frameMargin.z + edge)) / 2.0f;
            frameTra.scale_.y = 1;
            break;
        }
        for (int x = 0; x < 3; x++) {
            switch (x) {
            case 0:
                frameTra.position_.x = (float)(-screenWidth + (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                frameTra.scale_.x = 1;
                break;
            case 1:
                frameTra.position_.x = 0;
                frameTra.scale_.x = (float)(screenWidth - (frameMargin.y + frameMargin.w + edge + edge)) / (float)edge;
                break;
            case 2:
                frameTra.position_.x = (float)(screenWidth - (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                frameTra.scale_.x = 1;
                break;
            }

            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x * edge, y * edge, edge, edge);
            Transform tmp = frameTra;

            tmp.SetReSize(frameScale);

            Image::SetTransform(hPict_[p], tmp);
            Image::Draw(hPict_[p]);
        }
    }
}