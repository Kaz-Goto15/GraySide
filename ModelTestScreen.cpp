#include "ModelTestScreen.h"
#include "Engine/Input.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "Cube.h"
#include "./Engine/Camera.h"
#include "Easing.h"

//�R���X�g���N�^
ModelTestScreen::ModelTestScreen(GameObject* parent) :
    Screen(parent, "ModelTestScreen"),
    hModel(-1),
    debugtext(nullptr)
{
}

//�f�X�g���N�^
ModelTestScreen::~ModelTestScreen()
{
}

//������
void ModelTestScreen::Initialize()
{
    cube.resize(3, vector<vector<Cube*>>(3, vector<Cube*>(3, nullptr)));
    cubeNextTra.resize(3, vector<vector<Transform>>(3, vector<Transform>(3)));

    for (auto& cx : cube) {
        for (auto& cy : cx) {
            for (auto& cz : cy) {
                cz = Instantiate<Cube>(this);
            }
        }
    }
    for (int x = 0; x < cube.size();x++) {
        for (int y = 0; y < cube[0].size();y++) {
            for (int z = 0; z < cube[0][0].size();z++) {
                cube[x][y][z]->SetPosition(x - 1, y - 1, z - 1);
                cubeNextTra[x][y][z] = cube[x][y][z]->GetTransform(); //���̏ꏊ�̏�����
            }
        }
    }

    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
}

//�X�V
void ModelTestScreen::Update()
{
    //���ǂ�
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }

    if (!isMoving) {
        if (Input::IsKey(DIK_R)) {
            transform_.rotate_.z++;
        }
        //kaiten
        int column = 0;
        if (Input::IsKey(DIK_LSHIFT)) {
            if (Input::IsKey(DIK_LALT))column = 2;
            else column = 1;
        }
        if (Input::IsKey(DIK_Q)) {
            RotateCube(CCW, column, 45);
        }
        if (Input::IsKey(DIK_E)) {
            RotateCube(CW, column, 45);
        }
        if (Input::IsKey(DIK_W)) {
            RotateCube(BACK, column, 45);
        }
        if (Input::IsKey(DIK_S)) {
            RotateCube(FRONT, column, 45);
        }
        if (Input::IsKey(DIK_A)) {
            RotateCube(LEFT, column, 45);
        }
        if (Input::IsKey(DIK_D)) {
            RotateCube(RIGHT, column, 45);
        }
    }
    UpdateStr();
}

void ModelTestScreen::UpdateStr()
{
    using std::to_string;
    debugStr[0] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
}

void ModelTestScreen::CalcCubeTrans(ROTATE_DIR rot, int col, float value)
{
}

//�`��
void ModelTestScreen::Draw()
{

}

//�J��
void ModelTestScreen::Release()
{
}

void ModelTestScreen::RotateCube(ROTATE_DIR rot, int col, float value)
{
    //�t���O�Ǘ�
    isMoving = true;    //�ړ����t���O

    //���̍��W�w�� ��]�͈ꎞ�I�Ȃ̂ł��Ȃ��A�ړ���ɃL���[�u�����X�V����=�ό`��̃^�C����� ����������Ŏw�肵�Ă�������(�Ƃ肠����������)
    switch (rot)
    {
    case ModelTestScreen::FRONT:
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                cubeNextTra[col][y][z].position_ = { (float)col,(float)-(z-1),(float)y - 1};
                cube[col][y][z]->SetPosition({ (float)col,(float)-(z - 1),(float)y - 1 });
                
            }
        }
        //cube[col][1][1]->SetRotate(value, 0, 0);
        break;
    case ModelTestScreen::BACK:
        break;
    case ModelTestScreen::LEFT:
        break;
    case ModelTestScreen::RIGHT:
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (x == 1 && y == 1)break;
                cube[x][y][0]->SetParent(cube[1][1][col]);
                //cube[col][y][z]->SetParent(cube[col][1][1]);
            }
        }
        cube[1][1][col]->SetRotate(0, 0, value);

        break;
    case ModelTestScreen::CW:
        break;
    case ModelTestScreen::CCW:
        break;
    default:
        break;
    }
}
