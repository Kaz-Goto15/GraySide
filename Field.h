#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>

using std::vector;
//�t�B�[���h�I�u�W�F�N�g���Ǘ�����N���X
class Field : public GameObject
{
public:
    struct FIELD_DATA {
        int hModel = -1;
        Transform transform;
    };
private:
    vector<FIELD_DATA> fieldData_;
public:
    Field(GameObject* parent);    //�R���X�g���N�^
    ~Field();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
    void AddData(FIELD_DATA dat) { fieldData_.push_back(dat); } //�n�`�f�[�^�ǉ�
    void SetFieldData(vector<FIELD_DATA> dataList) { fieldData_ = dataList; }
};