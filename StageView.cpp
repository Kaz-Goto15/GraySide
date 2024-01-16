#include "StageView.h"
#include "Engine/Model.h"
//�R���X�g���N�^
StageView::StageView(GameObject* parent) :
    GameObject(parent, "StageView"),
    pStageData_(nullptr)
{
}

//�f�X�g���N�^
StageView::~StageView()
{
}

//������
void StageView::Initialize()
{

}

//�X�V
void StageView::Update()
{
}

//�`��
void StageView::Draw()
{
    Transform stagetrans;
    for (int z = 0; z < pStageData_->stageRange.z; z++) {
        stagetrans.position_.y = z;
        for (int x = 0; x < pStageData_->stageRange.x; x++) {
            stagetrans.position_.x = x;
            for (int y = 0; y < pStageData_->stageRange.y; y++) {
                stagetrans.position_.z = y;
                stagetrans.rotate_.x = (int)(pStageData_->sData[x][y][z].rot) * 90;
                Model::SetTransform(hModel[(int)(pStageData_->sData[x][y][z].tag)], stagetrans);
                Model::Draw(hModel[(int)(pStageData_->sData[x][y][z].tag)]);
                
            }
        }
    }
}

//�J��
void StageView::Release()
{
}