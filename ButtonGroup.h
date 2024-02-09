#pragma once
#include "Engine/GameObject.h"
#include "Button.h"

//�{�^���W�����Ǘ�����N���X
class ButtonGroup : public GameObject
{

public:
    ButtonGroup(GameObject* parent);    //�R���X�g���N�^
    ~ButtonGroup();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void AddButton(int handle, Button* btn);
};


/*

button
�E�}�E�X�͓Ɨ����Ă���
�E�����̍ۂɉ����ꂽ�ۂ̃A�N�V�������n���h���Ŏw�肷��
�E���{�^���I�u�W�F�N�g�ƌ݊�������
�E��邽�߂̉�����������΃L�[���������ۂɂQ�I�������

buttonGroup?
�E���݃t�H�[�J�X�{�^�����w�肷��?
�E�ς�����ۂ݂̂���ȊO�������I��IDLE��Ԃɂ���?
*/