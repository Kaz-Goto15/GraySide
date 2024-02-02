#include "Screen.h"
#include "Engine/Image.h"

void Screen::DebugAction()
{
    
    LPSTR str = nullptr;
    GetWindowText(GetActiveWindow(), str, 0);
    str += *objectName_.c_str();
    SetWindowText(GetActiveWindow(),str);
}

//�R���X�g���N�^
Screen::Screen(GameObject* parent, const std::string& name) :
    GameObject(parent, "Screen"),
    pPrevObject(nullptr)
{
    Leave();
    Invisible();
}

//�f�X�g���N�^
Screen::~Screen()
{
}

//������
void Screen::Initialize()
{
}

//�X�V
void Screen::Update()
{
}

//�`��
void Screen::Draw()
{   
}

//�J��
void Screen::Release()
{
}

void Screen::SetPrevScene(GameObject* prevScene)
{
    pPrevObject = prevScene;
}

void Screen::Prev()
{
    pPrevObject->Enter();
    KillMe();   //��������A�j���[�V�����͖���
}

void Screen::Run()
{
    Enter();
    Visible();
    pPrevObject->Leave();
}
