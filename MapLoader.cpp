#include "MapLoader.h"

#include <fstream>
#include "Include/nameof.hpp"

#include "Engine/Image.h"
#include "ModelLoader.h"
#include "Field.h"
//�ȉ��ɂ̓Q�[���v���C�I�u�W�F�N�g��Sinclude
#include "Sample.h"
#include "TestEntity.h"
#include "Player.h"

using json = nlohmann::json;
using namespace nameof;

void MapLoader::Init()
{
	//GameObject* maploadRoot = Instantiate<GameObject>(nullptr);
	//vector<GameObject*> objectList;
	//
	////�I�u�W�F�N�g�̎�ޒǉ����邽�тɒǉ�
	////objectList.push_back(Instantiate<GameSceneObject>(maploadRoot));
	//
	//for (auto& it : objectList) {
	//	objNameList.push_back(it->GetObjectName());
	//}
	//maploadRoot->ReleaseSub();
	//objectList.clear();
}


void MapLoader::Load(GameObject* pParent, int& hBackground, vector<Field::FIELD_DATA>* pFieldData, vector<GameObject*>* pActiveFieldList, vector<GameObject*>* pEntityList, MAP mID)
{
	//�}�b�vjson�J��
	std::ifstream f;
	switch (mID)
	{
	case MapLoader::M_001:	f.open("Data\\map1.json");	break;
	case MapLoader::M_002:	f.open("Data\\map2.json");	break;
	default: MessageBox(NULL, ((string)(NAMEOF_ENUM(mID))).c_str(), "Error:Open map json", MB_OK);
	}
	json data = json::parse(f);

	//�w�i����
	//�Ƃ肠����ImageLoader���\�肪�������߂����Ńt�@�C�������w�肷��
	//������Ȃ��Ɗ����� �����ł����摜��������t�H���_�������̂�Loader�܂ŗv�邩�Ƃ��������
	//�ł����ǂ����Ńt�@�C�����𕶎���ŋL�q���Ă��v���O�����I���܂Ŏc��̂ŔY�܂��� �܂�������
	//�ǂ��Ă������΂Ȃ��̂�json�Ƀt�@�C�����𒼏������܂���
	string file = "Background\\" + (string)data["mapData"]["background"];
	hBackground = Image::Load(file);
	
	//�n�`�I�u�W�F�N�g����
	for (auto& field : data["mapData"]["field"]) {
		int hModel = ModelLoader::Load(field["obj"]);	//str to enum���Ȃ��Ƃ���
		Transform modelTra;
		modelTra.position_ = { (float)field["pos"][0], (float)field["pos"][1], (float)field["pos"][2] };
		modelTra.rotate_   = { (float)field["rot"][0], (float)field["rot"][1], (float)field["rot"][2] };
		modelTra.scale_    = { (float)field["sca"][0], (float)field["sca"][1], (float)field["sca"][2] };

		pFieldData->push_back({ hModel, modelTra });
	}

	//���n�`�I�u�W�F�N�g����
	for (auto& entity : data["mapData"]["ativeField"]) {
		GameObject* gso = nullptr;

		OBJECT d = entity["obj"].template get<MapLoader::OBJECT>();
		switch (d)
		{
		case MapLoader::NONE:			gso = Instantiate<Sample>(pParent);	break;
		case MapLoader::OBJ_F_CUBE:		gso = Instantiate<Sample>(pParent);	break;
		case MapLoader::OBJ_F_RTP:		gso = Instantiate<Sample>(pParent);	break;
		case MapLoader::OBJ_F_CYLINDER:	gso = Instantiate<Sample>(pParent);	break;
		case MapLoader::OBJ_F_WATER:	gso = Instantiate<Sample>(pParent);	break;
		default: MessageBox(NULL, ((string)(NAMEOF_ENUM(d))).c_str(), "Error:Instantiate ActiveField", MB_OK);
		}

		gso->SetPosition((float)entity["pos"][0], (float)entity["pos"][1], (float)entity["pos"][2]);
		gso->SetRotate((float)entity["rot"][0], (float)entity["rot"][1], (float)entity["rot"][2]);
		gso->SetScale((float)entity["sca"][0], (float)entity["sca"][1], (float)entity["sca"][2]);
		pActiveFieldList->push_back(gso);
	}

	//�ʃI�u�W�F�N�g���� 
	json locate = data["mapData"]["entity"];
	for (int i = 0; i < locate.size();i++) {
		GameObject* gso = nullptr;

		OBJECT d = locate[i]["obj"].template get<MapLoader::OBJECT>();
		switch (d)
		{
		case MapLoader::NONE:			gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_PLAYER:	gso = Instantiate<Player>(pParent);	break;
		case MapLoader::OBJ_E_HANGER:	gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_BOMB:		gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_MUSHROOM:	gso = Instantiate<TestEntity>(pParent);	break;
		default: MessageBox(NULL, ((string)(NAMEOF_ENUM(d))).c_str(), "Error:Instantiate Entity", MB_OK);
		}

		gso->SetPosition((float)locate[i]["pos"][0], (float)locate[i]["pos"][1], (float)locate[i]["pos"][2]);
		gso->SetRotate((float)locate[i]["rot"][0], (float)locate[i]["rot"][1], (float)locate[i]["rot"][2]);
		gso->SetScale((float)locate[i]["sca"][0], (float)locate[i]["sca"][1], (float)locate[i]["sca"][2]);
		//�R���C�_�[�֘A�̏���
		// �Ȃ�
		///////////////////////////

		pEntityList->push_back(gso);
	}
	
	//�����`����Load��ɏ���������H
}