#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

#include "SelectRect.h"
#include "SelectTriangle.h"
#include "SceneChange.h"

#include "GameData.h"
//���j���[���Ǘ�����N���X
class MenuSelect : public GameObject
{
    Text* pText;
    std::string testring;
    int selectNo;
    float lineSpace;
    float toLocateY;
    XMFLOAT3 selectVec;
    int quantity;
    SceneChange* pSC;
    SelectRect* pSelectRect;
    SelectTriangle* pSelectTriangle;
    int hSound_[2];


public:
    //�R���X�g���N�^
    MenuSelect(GameObject* parent);

    //�f�X�g���N�^
    ~MenuSelect();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���ݒn�_����I���|�C���g�ֈړ�
    void PointMove();

    double GetLineSpace() { return lineSpace; }
    int GetSelectNo() { return selectNo; }
    void SetToLocateY(float y_) { toLocateY = y_; }
    void SetSelectNo(int send_);
    void ExeTrig();

    float GetSelectVec(int i);
    std::string GetInfoRect();
    std::string GetInfoTriangle();
};