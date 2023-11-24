#pragma once
#include "Engine/GameObject.h"
struct MVSINGLE
{
    float x;
    float y;
};
//���j���[���Ǘ�����N���X
class SceneChangeAnim : public GameObject
{
    int hPict_;    //�摜�ԍ�
    XMFLOAT3 fromVec, toVec;
    float sinx;
    bool fade_, move_;
    MVSINGLE mv;
    bool animStats = true;
    
public:
    //�R���X�g���N�^
    SceneChangeAnim(GameObject* parent);

    //�f�X�g���N�^
    ~SceneChangeAnim();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    std::string GetInfo();

    void ModifyRect(int x, int y, bool _fade);

    void AnimPlaying(bool animplay) { animStats = animplay; }
};