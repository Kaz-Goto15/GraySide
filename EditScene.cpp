#include "EditScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include <string>
using std::string;
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene"),
	queue_(-1),
	mapSize({5,5,5})
{}
void EditScene::Initialize() {
	//pView = new StageView();
	//pTheme = new StageTheme();
	//pView->SetTheme(pTheme);
	//pEditGUI = new StageEditGUI();
	//pEditGUI->SetTheme(pTheme);
	mapData_.resize(mapSize.x);
	for (size_t x = 0; x < mapSize.x; x++) {
		mapData_[x].resize(mapSize.y);
		for (size_t y = 0; y < mapSize.y; y++) {
			mapData_[x][y].resize(mapSize.z, 0);
		}
	}
}
void EditScene::Update() {
}
void EditScene::Draw() {

}
void EditScene::Release() {}

void EditScene::EditStart()
{
	//drawTime_ = 0;
	//queue_++;
	//isDisplaying = true;
	//state_ = S_Edit;
}

void EditScene::EditMain()
{
	
	//drawTime_++;

	//if (isDisplaying) {

	//}
	//else {
	//	queue_++;
	//	isDisplaying = true;
	//	if (!(queue_ < LOGO_COUNT)) {
	//		state_ = S_NEXT_SCENE;
	//	}
	//}

}

void EditScene::EditEnd()
{
	//if(que)
}

void EditScene::NextScene()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_TEST);
}

bool EditScene::LoadStageData()
{
	string ext = "hnsg";
	char fileName[MAX_PATH] = "����.hnsg";  //�t�@�C����������ϐ�

	//�u�t�@�C�����J���v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	string categoryStr = "�X�e�[�W�f�[�^(*." + ext + ")\0 * ." + ext + "\0";

	ofn.lpstrFilter = TEXT(categoryStr.c_str())			//�����t�@�C���̎��
		,TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");                     //����
	ofn.lpstrFile = fileName;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = "hnsg";                  	//�f�t�H���g�g���q

	//�u�t�@�C�����J���v�_�C�A���O
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return false;

	//if (!ConfirmDestruct())return false;
	HANDLE hFile;
	//�t�@�C�����J��
	hFile = CreateFile(
		fileName,  //�t�@�C����
		GENERIC_READ,              //�A�N�Z�X���[�h�i�������ݗp�j
		0,                          //���L�i�Ȃ��j
		NULL,                       //�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_EXISTING,              //�쐬���@
		FILE_ATTRIBUTE_NORMAL,      //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);                      //�g�������i�Ȃ��j

	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, ("CANNOT OPEN FILE: " + (string)fileName).c_str(), "Error", MB_OK);
		return false;
	}

	//�t�@�C���T�C�Y�擾
	DWORD fileSize = GetFileSize(hFile, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu
	BOOL res = ReadFile(
		hFile,     //�t�@�C���n���h��
		data,      //�f�[�^������ϐ�
		fileSize,  //�ǂݍ��ރT�C�Y
		&dwBytes,  //�ǂݍ��񂾃T�C�Y
		NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

	if (res == FALSE) {
		MessageBox(NULL, ("FAILED TO READ: " + (string)fileName).c_str(), "Error", MB_OK);
		return false;
	}

	CloseHandle(hFile);

	//�����Ɏ����Ă����f�[�^�ǂݍ��ރR�[�h
	//�Ǎ��f�[�^�����z��
	std::vector<std::vector<std::string>> data_;

	//LoadData(fileSize, data, &data_);

	//�ǂݍ��񂾃f�[�^���J��
	delete[] data;

	//�f�[�^�����݂̃v���W�F�N�g�t�@�C���ɓǍ�
	//for (int l = 0; l < data_.size(); l++) {
	//	table_[atoi(data_[l][0].c_str())][atoi(data_[l][1].c_str())].height = atoi(data_[l][2].c_str());
	//	table_[atoi(data_[l][0].c_str())][atoi(data_[l][1].c_str())].bType = (BLOCKTYPE)atoi(data_[l][3].c_str());
	//}

	//�S�f�[�^�J��
	for (int y = 0; y < data_.size(); y++)
		for (int x = 0; x < data_[y].size(); x++)
			data_[y][x].clear();

	//isEdited_ = false;
}
