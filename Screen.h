#pragma once
#include "Engine/GameObject.h"
//�T�u��ʃx�[�X
class Screen : public GameObject
{
public:

    void Show();
    void Hide();

private:
    bool debug;
    void DebugAction();
public:
    Screen(GameObject* parent);
    ~Screen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    virtual void CloseAnim();
    void Close();
    
};