#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class DebugText;
//クレジット画面を管理するクラス
class CreditScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_BASIC_FRAME_TEX,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX - 1];

    XMINT4 frameMargin;  //上右下左
    float frameScale;    //可変フレーム拡大率
    DebugText* debugtext;
    std::string debugStr[20];
    float resize = 1;
    float scaleMag = 1.0f;
    bool b = true;
public:
    CreditScreen(GameObject* parent);
    ~CreditScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};