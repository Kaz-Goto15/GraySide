#include "ModelTestScreen.h"
#include "Engine/Input.h"

#include "SystemConfig.h"
#include "DebugText.h"
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
    cubePrevTra.resize(3, vector<vector<Transform>>(3, vector<Transform>(3)));

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
    //���ǂ�(�f�o�b�O)
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }
    //�����Ԃ��A�C�h���łȂ����
    if (control != CONTROL_IDLE) {
        //���݂̃��[�h�ŏ���
        switch (mode)
        {
        case ModelTestScreen::MODE_SET:
            //�L�[�֘A�̋L�q�͓���������h�����ߎ�芸�������ׂ�elif�ŏ���
            //�}�[�N�ݒu
            if (Input::IsKeyDown(DIK_SPACE)) {
                //�I���ӏ����󔒂̂Ƃ��ɐݒu����
                if (cube[selectData.x][selectData.y][selectData.x]->GetMark(selectData.surface) == Cube::MARK_BLANK) {
                    Cube::MARK mark;

                    if (control == CONTROL_1P) {
                        mark = Cube::MARK::MARK_O;
                    }
                    else {
                        mark = Cube::MARK::MARK_X;
                    }

                    cube[selectData.x][selectData.y][selectData.x]->SetMark(selectData.surface, mark);
                    TurnEnd();
                }
                else {
                    //�󔒂łȂ��Ƃ��̃A�j���[�V����������΂����ɏ��� �I����\�����������f�������炷�Ȃ�
                }
            }
            else if (Input::IsKeyDown(DIK_LSHIFT)) {
                mode = MODE_ROTATE;
            }
            else if (Input::IsKeyDown(DIK_W)) {
                using SURFACE = Cube::SURFACE;
                switch (selectData.surface)
                {
                case Cube::SURFACE_TOP:
                    selectData.z++;
                    if (selectData.z > 3) {
                        selectData.z = 3;
                        selectData.surface = SURFACE::SURFACE_BOTTOM;
                    }
                    break;
                case Cube::SURFACE_BOTTOM:
                    break;
                case Cube::SURFACE_LEFT:
                    break;
                case Cube::SURFACE_RIGHT:
                    break;
                case Cube::SURFACE_FRONT:
                    break;
                case Cube::SURFACE_BACK:
                    break;
                case Cube::SURFACE_MAX:
                    break;
                default:
                    break;
                }
                selectData.y--;
                if (selectData.y == -1) {

                }
                //�S��y-1�ɂȂ�Ƃ��ł���
                //�O�ŏ�ɍs���Ƃ��F���
                //��ŏ�ɍs���Ƃ��F���
                //��ŏ�ɍs���Ƃ��F����
                //���ŏ�ɍs���Ƃ��F�O��
                //���ŏ�ɍs���Ƃ��F���
                //�E�ŏ�ɍs���Ƃ��F���
            }
            break;
        case ModelTestScreen::MODE_ROTATE:
            break;
        case ModelTestScreen::MODE_VIEW:
            break;
        default:
            break;
        }
    }

    if (!isMoving) {
        if (Input::IsKeyDown(DIK_R)) {
            transform_.rotate_.z++;
        }
        //kaiten
        int column = 0;
        if (Input::IsKeyDown(DIK_LSHIFT)) {
            if (Input::IsKey(DIK_LALT))column = 2;
            else column = 1;
        }
        if (Input::IsKeyDown(DIK_Q)) {
            RotateCube(CCW, column, 45);
        }
        if (Input::IsKeyDown(DIK_E)) {
            RotateCube(CW, column, 45);
        }
        if (Input::IsKeyDown(DIK_W)) {
            RotateCube(BACK, column, 45);
        }
        if (Input::IsKeyDown(DIK_S)) {
            RotateCube(FRONT, column, 45);
        }
        if (Input::IsKeyDown(DIK_A)) {
            RotateCube(LEFT, column, 45);
        }
        if (Input::IsKeyDown(DIK_D)) {
            RotateCube(RIGHT, column, 45);
        }
    }
    else {
        ModelTestScreen::CalcCubeTrans();
    }
    UpdateStr();
}

void ModelTestScreen::UpdateStr()
{
    using std::to_string;
    debugStr[0] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
}

void ModelTestScreen::CalcCubeTrans()
{
    rotTime++;
    if (rotTime >= angleOfRotate) {
        rotTime = 90;
        isMoving = false;
    }
    switch (dir)
    {
    case ModelTestScreen::FRONT:
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                //���W�͂��̂܂ܕς���
                cube[rotateNo][y][z]->SetPosition(
                    Easing::Calc(7, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].position_.x, cubeNextTra[rotateNo][y][z].position_.x),
                    Easing::Calc(7, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].position_.y, cubeNextTra[rotateNo][y][z].position_.y),
                    Easing::Calc(7, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].position_.z, cubeNextTra[rotateNo][y][z].position_.z)
                );
                cube[rotateNo][y][z]->SetRotate(
                    Easing::Calc(1, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].rotate_.x, cubeNextTra[rotateNo][y][z].rotate_.x),
                    Easing::Calc(1, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].rotate_.y, cubeNextTra[rotateNo][y][z].rotate_.y),
                    Easing::Calc(1, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].rotate_.z, cubeNextTra[rotateNo][y][z].rotate_.z)
                );
            }
        }
    case ModelTestScreen::BACK:
        break;
    case ModelTestScreen::LEFT:
        break;
    case ModelTestScreen::RIGHT:
        break;
    case ModelTestScreen::CW:
        break;
    case ModelTestScreen::CCW:
        break;
    default:
        break;
    }
    if (isMoving == false) {
        rotTime = 0;

        switch (dir)
        {
        case ModelTestScreen::FRONT:
            //�z��̓���ւ����s���A�^�C���̕������ς���
            //rotate��0�ɖ߂�
            //position������ւ���̍��W�ɂ��� ����͍Ō�ɍ��W�����̈ʒu�֌��������ߔz��ԍ��̈ړ��݂̂ōς�
            //��rotate��0�ɂ��Ă���A�z������ւ���
            //std::rotateM
            break;
        case ModelTestScreen::BACK:
            break;
        case ModelTestScreen::LEFT:
            break;
        case ModelTestScreen::RIGHT:
            break;
        case ModelTestScreen::CW:
            break;
        case ModelTestScreen::CCW:
            break;
        default:
            break;
        }
    }
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
    rotateNo = col;
    dir = rot;
    //�t���O�Ǘ�
    isMoving = true;    //�ړ����t���O

    //���̍��W�w�� ��]�͈ꎞ�I�Ȃ̂ł��Ȃ��A�ړ���ɃL���[�u�����X�V����=�ό`��̃^�C����� ����������Ŏw�肵�Ă�������(�Ƃ肠����������)
    switch (rot)
    {
    case ModelTestScreen::FRONT:
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                cubePrevTra[col][y][z].position_ = cube[col][y][z]->GetPosition();
                //cubePrevTra[col][y][z].position_ = cubeNextTra[col][y][z].position_;    //�������̂ق����s�������������H
                cubeNextTra[col][y][z].position_ = { (float)col - 1,(float)-(z - 1),(float)y - 1 };
                cube[col][y][z]->SetPosition({ (float)col-1,(float)-(z - 1),(float)y - 1 });
                cube[col][y][z]->SetRotate({ value,0,0 });
                
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

void ModelTestScreen::TurnEnd()
{
    if (control == CONTROL_1P) {
        nextTurn = CONTROL_2P;
    }
    if (control == CONTROL_2P) {
        nextTurn = CONTROL_1P;
    }
    control = CONTROL_IDLE;
    
    control = nextTurn; //���̓A�j���[�V������f�B���C�������̂ł����Ŏ��̃^�[���ɂ���
}

void ModelTestScreen::Judge()
{
    if (mode == MODE_SET) {
        switch (selectData.surface)
        {
        case Cube::SURFACE::SURFACE_TOP:
            cube[selectData.x]
        default:
            break;
        }
    }
}

bool Yoko() {
    if()
    return true;
}
bool Tate();
bool Naname() { return true; }
/*
��]�g���K�[���A��]�����Ɖ�]����w�肵�A��]�t���O��L����
��]�t���O���L�������ꂽ��A��]�����Ɖ�]��ɏ]���A��]�@�@      ����]�ɂ͉�]�O�ό`���Ɖ�]��ό`����p����
��]�I����A��]�t���O�𖳌������ACube�I�u�W�F�N�g�����ւ���
*/

/*
3x3��2��0�����ւ̉�](�O(��)�A�E�A�����v)
    vector<vector<int>> arr;
    arr.resize(3, vector<int>(3));

    for (int i = 0; i < 3; i++) {
        swap(arr[2-i][0], arr[0][i]);
    }

    for (int i = 1; i < 3; i++) {
        swap(arr[0][i], arr[3-1][i]);
    }

    swap(arr[0][1], arr[1][2]);

*/

/*
�ЂƂ��ɉ�����Ƃ����Ă����E����z�A����x�Ŕ��肷�邱�ƂɂȂ�
�c���肾�ƑO�㍶�E��y�A�㉺��z
�΂߂��Ƃ���ɖʓ|�ŁA�O���xy�A���E��yz�A�㉺��xz�ł���

�I���ꏊ�ɂ���Ď΂߂̔�������邩�����ƂȂ邪�A
�㉺����x=0,2����z=0,2
���E����y=0,2����z=0,2
�O�ゾ��x=0,2����y=0,2
�Ŏ΂߂�����
����ɁA�E��ɏオ�邩�E���ɉ����邩�����߂�K�v������A
���x,z=0,0 2,2�ŉE�� x,z=0,2 2,0�ŉE��
https://cpprefjp.github.io/lang/cpp11/variadic_templates.html
*/