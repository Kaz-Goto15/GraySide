#pragma once
#include "Engine/GameObject.h"

//�N���W�b�g��ʂ��Ǘ�����N���X
class CreditScreen : public GameObject
{

    bool enScreen;
    int hPict_;
public:
    CreditScreen(GameObject* parent);
    ~CreditScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void Show();
    void Hide();
};