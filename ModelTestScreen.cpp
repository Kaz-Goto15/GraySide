#include "ModelTestScreen.h"
#include "Engine/Input.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "./Engine/Camera.h"
#include "Easing.h"
#include "./Engine/Image.h"
#include <algorithm>
#include "CubeSelectIndicator.h"

#include "./Include/nameof.hpp"
#include "./Engine/Debug.h"

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
    hImgBG = Image::Load("Background\\bg_game.png");
    cube.resize(PIECES, vector<vector<Cube*>>(PIECES, vector<Cube*>(PIECES, nullptr)));
    cubeNextTra.resize(PIECES, vector<vector<Transform>>(PIECES, vector<Transform>(PIECES)));
    cubePrevTra.resize(PIECES, vector<vector<Transform>>(PIECES, vector<Transform>(PIECES)));

    //�L���[�u����
    for (auto& cx : cube) {
        for (auto& cy : cx) {
            for (auto& cz : cy) {
                cz = Instantiate<Cube>(this);
            }
        }
    }

    //�L���[�u���W�w��
    for (int x = 0; x < cube.size();x++) {
        for (int y = 0; y < cube[0].size();y++) {
            for (int z = 0; z < cube[0][0].size();z++) {
                cube[x][y][z]->SetPosition(x - 1, y - 1, z - 1);
                cubeNextTra[x][y][z] = cube[x][y][z]->GetTransform(); //���̏ꏊ�̏�����
            }
        }
    }

    //�C���W�P�[�^�[�����E���W�w��
    indicator = Instantiate<CubeSelectIndicator>(this);
    indicator->SetPosition(selectData.x - 1, selectData.y - 1, selectData.z - 1);
    indicator->SetSurface(selectData.surface);

    //�f�o�b�O
    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
}

//�X�V
void ModelTestScreen::Update()
{

    RotateCamera();     //�J�����̏��� MODE_VIEW�ł̕��������
    MoveSelect();

    //���ǂ�(�f�o�b�O)
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }
    if (Input::IsKeyDown(DIK_0)) {
        if (mode == MODE_SET)mode = MODE_ROTATE;
        else if (mode == MODE_ROTATE)mode = MODE_VIEW;
        else if (mode == MODE_VIEW)mode = MODE_SET;
    }
    if (Input::IsKeyDown(DIK_9)) {
        if (control == CONTROL_IDLE)control = CONTROL_1P;
        else if (control == CONTROL_1P)control = CONTROL_2P;
        else if (control == CONTROL_2P)control = CONTROL_IDLE;
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
                if (cube[selectData.x][selectData.y][selectData.z]->GetMark(selectData.surface) == Cube::MARK_BLANK) {
                    Cube::MARK mark;
                    switch (control)
                    {
                    case ModelTestScreen::CONTROL_1P:   mark = Cube::MARK::MARK_O;  break;
                    case ModelTestScreen::CONTROL_2P:   mark = Cube::MARK::MARK_X;  break;
                    }
                    cube[selectData.x][selectData.y][selectData.z]->SetMark(selectData.surface, mark);
                    Judge();
                    TurnEnd();
                }
                else {
                    //�󔒂łȂ��Ƃ��̃A�j���[�V����������΂����ɏ��� �I����\�����������f�������炷�Ȃ�
                    //Audio::Play("select_fail.wav");
                }
            }
            else if (Input::IsKeyDown(DIK_LSHIFT)) {
                mode = MODE_ROTATE;
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

    //if (!isMoving) {
    //    if (Input::IsKeyDown(DIK_R)) {
    //        transform_.rotate_.z++;
    //    }
    //    //kaiten
    //    int column = 0;
    //    if (Input::IsKeyDown(DIK_LSHIFT)) {
    //        if (Input::IsKey(DIK_LALT))column = 2;
    //        else column = 1;
    //    }
    //    if (Input::IsKeyDown(DIK_Q)) {
    //        RotateCube(CCW, column, 45);
    //    }
    //    if (Input::IsKeyDown(DIK_E)) {
    //        RotateCube(CW, column, 45);
    //    }
    //    if (Input::IsKeyDown(DIK_W)) {
    //        RotateCube(BACK, column, 45);
    //    }
    //    if (Input::IsKeyDown(DIK_S)) {
    //        RotateCube(FRONT, column, 45);
    //    }
    //    if (Input::IsKeyDown(DIK_A)) {
    //        RotateCube(LEFT, column, 45);
    //    }
    //    if (Input::IsKeyDown(DIK_D)) {
    //        RotateCube(RIGHT, column, 45);
    //    }
    //}
    //else {
    //    ModelTestScreen::CalcCubeTrans();
    //}
    UpdateStr();
}

void ModelTestScreen::UpdateStr()
{
    using std::to_string;
    debugStr[0] = "control:" + (std::string)NAMEOF_ENUM(control) + "(Press '9' to change)";
    debugStr[1] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
    debugStr[2] = "mode:" + (std::string)NAMEOF_ENUM(mode)+ "(Press '0' to change)";
    debugStr[3] = "select:" + std::to_string(selectData.x) + "," + std::to_string(selectData.y) + "," + std::to_string(selectData.z) + "," + (std::string)NAMEOF_ENUM(selectData.surface);
    debugStr[4] = "camTra:" + std::to_string(camTra.rotate_.x) + ", " + std::to_string(camTra.rotate_.y);
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

void ModelTestScreen::MoveSelectParts(DIR dir, bool plus, Cube::SURFACE outSurface) {

    int* target = nullptr;
    switch (dir)
    {
    case ModelTestScreen::X:target = &selectData.x; break;
    case ModelTestScreen::Y:target = &selectData.y; break;
    case ModelTestScreen::Z:target = &selectData.z; break;
    }

    if (plus) {
        *target += 1;
        if (*target >= PIECES) {
            *target = PIECES - 1;
            selectData.surface = outSurface;
        }
    }
    else {
        *target -= 1;
        if (*target < 0) {
            *target = 0;
            selectData.surface = outSurface;
        }
    }
    indicator->SetPosition(selectData.x - 1, selectData.y - 1, selectData.z - 1);
    indicator->SetSurface(selectData.surface);
}
void ModelTestScreen::MoveSelect()
{
    using SURFACE = Cube::SURFACE;
    vector<int> keys = {DIK_W,DIK_A,DIK_S,DIK_D};

    switch (selectData.surface)
    {
    case SURFACE::SURFACE_TOP:
        if (Between(camTra.rotate_.y, -45.0f, 45.0f)) {}
        else if (Between(camTra.rotate_.y, 45.0f, 135.0f)) {
            //WASD��ASDW��
            int tmp = keys.front();
            keys.erase(keys.begin());
            keys.push_back(tmp);
        }
        else if (Between(camTra.rotate_.y, -135.0f, -45.0f)) {
            //WASD��DWAS��
            int tmp = keys.back();
            keys.pop_back();
            keys.insert(keys.begin(), tmp);
        }
        else {
            //WASD��SDWA��
            for (int i = 0; i < 2; i++) {
                int tmp = keys.back();
                keys.pop_back();
                keys.insert(keys.begin(), tmp);
            }
        }
        if (Input::IsKeyDown(keys[0]))  MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
        if (Input::IsKeyDown(keys[1]))  MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
        if (Input::IsKeyDown(keys[2]))  MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
        if (Input::IsKeyDown(keys[3]))  MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
        break;
    case SURFACE::SURFACE_BOTTOM:
        if (Between(camTra.rotate_.y, -45.0f, 45.0f)) {}
        else if (Between(camTra.rotate_.y, 45.0f, 135.0f)) {
            //WASD��DWAS��
            int tmp = keys.back();
            keys.pop_back();
            keys.insert(keys.begin(), tmp);
        }
        else if (Between(camTra.rotate_.y, -135.0f, -45.0f)) {
            //WASD��ASDW��
            int tmp = keys.front();
            keys.erase(keys.begin());
            keys.push_back(tmp);
        }
        else {
            //WASD��SDWA��
            for (int i = 0; i < 2; i++) {
                int tmp = keys.back();
                keys.pop_back();
                keys.insert(keys.begin(), tmp);
            }
        }

        if (Input::IsKeyDown(keys[0]))  MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
        if (Input::IsKeyDown(keys[1]))  MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
        if (Input::IsKeyDown(keys[2]))  MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
        if (Input::IsKeyDown(keys[3]))  MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
        break;
    case SURFACE::SURFACE_LEFT:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(Z, true,  SURFACE::SURFACE_BACK);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false,  SURFACE::SURFACE_BOTTOM);
        break;
    case SURFACE::SURFACE_RIGHT:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(Z, true,  SURFACE::SURFACE_BACK);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false,  SURFACE::SURFACE_BOTTOM);
        break;
    case SURFACE::SURFACE_FRONT:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(X, true,  SURFACE::SURFACE_RIGHT);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
        break;
    case SURFACE::SURFACE_BACK:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(X, true,  SURFACE::SURFACE_RIGHT);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
        break;
    }

}

void ModelTestScreen::MoveIndicator()
{
}

//�`��
void ModelTestScreen::Draw()
{
    Image::Draw(hImgBG);
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
    /*
    SET���[�h�Ȃ��r�͎����̃}�[�N����
    ROTAET���[�h�Ȃ玩���Ƒ���̃}�[�N

    �������Ƃ��Ƀ}�[�N��Ԃ��֐����A
    ���P���ɂQ�񔻒肷��H
    �}�[�N��n���đ����������肷��֐���
    */

    //�΂ߏ����֐�
    //����󔒏���������̂͏璷���������߁A�t���O�ŊǗ����ăZ�b�g����悤�ɂ���
    // ����vector�őS��blank�Ȃ�blank���A
    // �ǂ��炩��������΂��������A
    //���������Ă��瑊��̃^�[����Ԃ��֐���ʂō��΂����̂ł͂Ȃ���
    vector<Cube::MARK> result;
    auto test = [=](XMINT3 xyz, Cube::SURFACE surface, WinFlag& winFlag) {
//���@�@�@�@��
//���������@�O�E�㍶
//���@�@�@�@���@�@�@
        switch (surface)
        {
        case Cube::SURFACE_TOP:     //������0,-,0
            //�T�����W2����v �E��
            if (xyz.x == xyz.z)
                winFlag.Set(CheckMarkD(DIAG_VAR::UP, PIECES - 1, DIAG_VAR::UP, surface));
            //�T�����W2������ �E��
            if (PIECES - 1 - xyz.x == xyz.z)
                winFlag.Set(CheckMarkD(DIAG_VAR::UP, PIECES - 1, DIAG_VAR::DOWN, surface));
            break;
        case Cube::SURFACE_BOTTOM:  //���オ0,-,0
            if (xyz.x == xyz.z) {   //�����W��v���� �E��
                winFlag.Set(CheckMarkD(DIAG_VAR::UP, 0, DIAG_VAR::UP, surface));
            }
            if (PIECES - 1 - xyz.x == xyz.z) {  //�������� �E��
                winFlag.Set(CheckMarkD(DIAG_VAR::UP, 0, DIAG_VAR::DOWN, surface));
            }
            break;
        case Cube::SURFACE_LEFT:    //�E����-,0,0
            if (xyz.y == xyz.z) {   //�����W��v���� �E��
                winFlag.Set(CheckMarkD(0, DIAG_VAR::DOWN, DIAG_VAR::DOWN, surface));
            }
            if (PIECES - 1 - xyz.y == xyz.z) {  //�������� �E��
                winFlag.Set(CheckMarkD(0, DIAG_VAR::UP, DIAG_VAR::DOWN, surface));
            }
            break;
        case Cube::SURFACE_RIGHT:   //������-,0,0
            if (xyz.y == xyz.z) {   //�����W��v���� �E��
                winFlag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::UP, DIAG_VAR::UP, surface));
            }
            if (PIECES - 1 - xyz.y == xyz.z) {  //�������� �E��
                winFlag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::DOWN, DIAG_VAR::UP, surface));
            }
            break;
        case Cube::SURFACE_FRONT:   //������0,0,-
            if (xyz.x == xyz.y) {   //�����W��v���� �E��
                winFlag.Set(CheckMarkD(DIAG_VAR::UP, DIAG_VAR::UP, 0, surface));
            }
            if (PIECES - 1 - xyz.x == xyz.y) {  //�������� �E��
                winFlag.Set(CheckMarkD(DIAG_VAR::UP, DIAG_VAR::DOWN, 0, surface));
            }
            break;
        case Cube::SURFACE_BACK:    //�E����0,0,-
            if (xyz.x == xyz.y) {   //�����W��v���� �E��
                winFlag.Set(CheckMarkD(DIAG_VAR::DOWN, DIAG_VAR::DOWN, PIECES - 1, surface));
            }
            if (PIECES - 1 - xyz.x == xyz.y) {  //�������� �E��
                winFlag.Set(CheckMarkD(DIAG_VAR::DOWN, DIAG_VAR::UP, PIECES - 1, surface));
            }
            break;
        }
        };

    switch (mode)
    {
    case ModelTestScreen::MODE_SET:
        //�΂ߔ���
        test(selectData.GetPos(), selectData.surface, winFlag);
        //�K���c�������͌���
        switch (selectData.surface) {
        case Cube::SURFACE::SURFACE_FRONT:
        case Cube::SURFACE::SURFACE_BACK:
            winFlag.Set(CheckMarkVH(selectData.GetPos(), selectData.surface, X));
            winFlag.Set(CheckMarkVH(selectData.GetPos(), selectData.surface, Y));
        case Cube::SURFACE::SURFACE_LEFT:
        case Cube::SURFACE::SURFACE_RIGHT:
            winFlag.Set(CheckMarkVH(selectData.GetPos(), selectData.surface, Y));
            winFlag.Set(CheckMarkVH(selectData.GetPos(), selectData.surface, Z));
            break;
        case Cube::SURFACE::SURFACE_TOP:
        case Cube::SURFACE::SURFACE_BOTTOM:
            winFlag.Set(CheckMarkVH(selectData.GetPos(), selectData.surface, X));
            winFlag.Set(CheckMarkVH(selectData.GetPos(), selectData.surface, Z));
            break;
        }
        break;
    case ModelTestScreen::MODE_ROTATE:
        for (Cube::SURFACE surface = static_cast<Cube::SURFACE>(0); surface < Cube::SURFACE_MAX; surface = static_cast<Cube::SURFACE>(surface + 1)) {
            //selectData.rotate
            /*
            0,0,0��X���ŏ㉺�����Ɉړ������ꍇ
            X�ʒu���Œ�
            000front 010front 020front
            020top 021top 022top
            002back 012back 022back
            000bottom 001bottom 002bottom
            0,0,0��Y���ō��E�����Ɉړ������ꍇ
            Y�ʒu���Œ�
            000front 100front 200front
            000left 001left 002left
            002back 102back 202back
            200right 201right 202right
            0,0,0��Z���Ŏ��v�����v�����Ɉړ������ꍇ
            Z�ʒu���Œ�
            000left 010left 020left
            020top 120top 220top
            200right 210right 220right
            000bottom 100bottom 200bottom
            */
        }
        break;
    }

    auto win = [=](CONTROL control) {
        switch (control)
        {
        case ModelTestScreen::CONTROL_1P:
            debugStr[5] = "1p syouri";
            break;
        case ModelTestScreen::CONTROL_2P:
            debugStr[5] = "2p syouri";
            break;
        default:
            break;
        }
    };
    //�i�i������
    test(selectData.GetPos(), selectData.surface, winFlag);

    //��������
    if (control == CONTROL_1P) {
        if (winFlag.p2) {
            win(CONTROL_2P);
        }
        else if (winFlag.p1) {
            win(CONTROL_1P);
        }
    }
    if (control == CONTROL_2P) {
        if (winFlag.p1) {
            win(CONTROL_1P);
        }
        else if (winFlag.p2) {
            win(CONTROL_2P);
        }
    }
    //rotate�Ȃ��]�������̃}�X�S�Ă𔻒肷��
    //set�Ȃ�u�����}�X�̂ݔ��肷��
    //���莩�͕̂ʏ���(CheckMarkVH,D)
}

void ModelTestScreen::RotateCamera() {
    //�J����(��X�����F�f�o�b�O)

    bool moveFlag = false;
    //�r���[���[�h�̏ꍇ�A�ړ�������
    if (mode == MODE_VIEW) {
        //���N���b�N���Ƀh���b�O�ňړ�����(��)
        if (Input::IsMouseButton(0)) {
            rotSpdY = Input::GetMouseMove().x * AT_RATIO;   //�}�E�Xx�ړ��ʂ�y����]
            rotSpdX = Input::GetMouseMove().y * AT_RATIO;   //�}�E�Xy�ړ��ʂ�x����]
            moveFlag = true;
        }
    }

    //�J�����ړ����Ȃ������瑬�x����
    if (!moveFlag) {
        //�e���x��0�łȂ��ꍇ�������� ���ȉ���0�ɂ���
        if (rotSpdX != DEFAULT_SPEED) {
            rotSpdX /= DC_RATIO;
            if (std::abs(rotSpdX) < TH_ZEROSPEED)rotSpdX = DEFAULT_SPEED;
        }
        if (rotSpdY != DEFAULT_SPEED) {
            rotSpdY /= DC_RATIO;
            if (std::abs(rotSpdY) < TH_ZEROSPEED)rotSpdY = DEFAULT_SPEED;
        }
    }
    //�Œ�l���� �ߋ��̃J�����̑Ώۂ̊��炩�Ȉړ�������R�[�h���痬�p�������J������]���Ǝv���������ɂȂ�Ȃ����ߖv
    //if (rotSpdX > 0) {
    //    rotSpdX -= decSpd;
    //    if (rotSpdX < 0)rotSpdX = 0;
    //}
    //else if (rotSpdX < 0) {
    //    rotSpdX += decSpd;
    //    if (rotSpdX > 0)rotSpdX = 0;
    //}
    //if (rotSpdY > 0) {
    //    rotSpdY -= decSpd;
    //    if (rotSpdY < 0)rotSpdY = 0;
    //}
    //else if (rotSpdY < 0) {
    //    rotSpdY += decSpd;
    //    if (rotSpdY > 0)rotSpdY = 0;
    //}

    //��]���ɉ��Z
    camTra.rotate_.y += rotSpdY;
    camTra.rotate_.x += rotSpdX;

    //�͈͓�����(y���͐����Ȃ������ɉ�]����Ēl���ӂ�Ă�����̂ŃR���o�[�g ���ڑ���ɂ���ƈ�u�ł܂邽�߉�������)
    camTra.rotate_.x = std::clamp(camTra.rotate_.x, MIN_CAM_ROTATE_X, MAX_CAM_ROTATE_X);
    if (camTra.rotate_.y > LIMIT_CAM_ROTATE_Y) {
        camTra.rotate_.y -= 2 * LIMIT_CAM_ROTATE_Y;
    }
    if (camTra.rotate_.y < -LIMIT_CAM_ROTATE_Y) {
        camTra.rotate_.y += 2 * LIMIT_CAM_ROTATE_Y;
    }

    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(camTra.rotate_.y));   //Y����Y��]�ʕ���]������s��
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(camTra.rotate_.x));   //X����X��]�ʕ���]������s��

    //�J�����ݒ� �ʒu->�Ώۂ̌��
    XMVECTOR vCam = { 0,0,-CAM_DISTANCE,0 };                  //�����w��
    vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //�ό`:��]
    Camera::SetPosition(vCam);            //�Z�b�g

    /*
    �E�ړ��n�͑Ώۂ�0, 0, 0�ŌŒ�Ȃ̂ŏ����Ȃ��Ă���
    �E�ΏۂƂ̋���������͕ς���K�v���܂������Ȃ��̂Ŏ������Ȃ�
    */
}

void ModelTestScreen::FinishCamera()
{
    //doonce����ăJ������]����������
    Transform toTra;
    //toTra.rotate_.x 
}

Cube::MARK ModelTestScreen::CheckMarkVH(int x, int y, int z, SURFACE surface, DIR dir)
{
    vector<XMINT3> checkMarks;
    for (int i = 0; i < PIECES; i++) {
        switch (dir)
        {
        case ModelTestScreen::X:
            checkMarks.push_back({ i,y,z });
            break;
        case ModelTestScreen::Y:
            checkMarks.push_back({ x,i,z });
            break;
        case ModelTestScreen::Z:
            checkMarks.push_back({ x,y,i });
            break;
        }
    }
    return CheckMark(checkMarks, surface);
}

Cube::MARK ModelTestScreen::CheckMarkVH(XMINT3 xyz, SURFACE surface, DIR dir)
{
    return CheckMarkVH(xyz.x, xyz.y, xyz.z, surface, dir);
}

Cube::MARK ModelTestScreen::CheckMarkD(int x, int y, int z, SURFACE surface) {

    vector<XMINT3> checkMarks;
    for (int i = 0; i < PIECES; i++) {
        XMINT3 check;
        if (x < 0) {
            if (x == DIAG_VAR::UP)check.x = i;
            if (x == DIAG_VAR::DOWN)check.x = PIECES - 1 - i;
        }
        else {
            check.x = x;
        }
        if (y < 0) {
            if (y == DIAG_VAR::UP)check.y = i;
            if (y == DIAG_VAR::DOWN)check.y = PIECES - 1 - i;
        }
        else {
            check.y = y;
        }
        if (z < 0) {
            if (z == DIAG_VAR::UP)check.z = i;
            if (z == DIAG_VAR::DOWN)check.z = PIECES - 1 - i;
        }
        else {
            check.z = z;
        }
        checkMarks.push_back(check);
    }
    return CheckMark(checkMarks, surface);
}

Cube::MARK ModelTestScreen::CheckMarkD(XMINT3 xyz, SURFACE surface)
{
    return CheckMarkD(xyz.x, xyz.y, xyz.z, surface);
}

Cube::MARK ModelTestScreen::CheckMark(vector<XMINT3> points, SURFACE surface)
{
    /*
    �������Ƃ��A���̃}�[�N��Ԃ�
    ����Ȃ���΋󔒂�Ԃ�
    �󔒂ő����Ă��󔒂�Ԃ�
    */

    Cube::MARK mark = cube[points[0].x][points[0].y][points[0].z]->GetMark(surface);   //�������Ƃ��ɕԂ��}�[�N
    assert(points.size() > 0);  //��Ⴂ�ŋ�̔z�񂪗�������assert
    Debug::Log("����F["+ std::to_string(points[0].x) + std::to_string(points[0].y) + std::to_string(points[0].z) +"]:" + (std::string)NAMEOF_ENUM(mark) +", ", false);
    for (int i = 1; i < points.size(); i++) { 
        Debug::Log("[" + std::to_string(points[i].x) + std::to_string(points[i].y) + std::to_string(points[i].z) + "]:" + (std::string)NAMEOF_ENUM(cube[points[i].x][points[i].y][points[i].z]->GetMark(surface)) + ", ", false);
        if (cube[points[i].x][points[i].y][points[i].z]->GetMark(surface) != mark) {
            Debug::Log((std::string)NAMEOF_ENUM(mark) + "�͂����Ȃ�����", true);
            return Cube::MARK_BLANK;    //����Ȃ��������
        }
    }
    Debug::Log((std::string)NAMEOF_ENUM(mark) + "���������", true);
    return mark;
}

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

�ړ����
�J�����ɂ������Ȃ��ړ�
�O�㍶�E��WS��Y-+�A�͈͊O�ŏ㉺��SURFACE�]���ŗǂ�
�O��AD��X-+�A�͈͊O�ō��E
�E��AD��Z-+�A�͈͊O�őO��
����AD��Z+-�A�͈͊O�Ō�O
���AD��X+-�A�͈͊O�ŉE��
�J�����ɂ������ړ�
Y���ŕς��ړ�
��
WS��Z+-�AAD��X-+

���W�n���Ȃ��
 +
- +
 -
*/