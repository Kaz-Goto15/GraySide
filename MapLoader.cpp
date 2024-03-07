#include "MapLoader.h"

#include <fstream>
#include "Include/nameof.hpp"

#include "ModelLoader.h"
#include "Field.h"
//�ȉ��ɂ̓Q�[���v���C�I�u�W�F�N�g��Sinclude
#include "Sample.h"
#include "TestEntity.h"
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


void MapLoader::Load(GameObject* pParent, vector<Field::FIELD_DATA>* pFieldData, vector<GameObject*>* pActiveFieldList, vector<Entity*>* pEntityList, MAP mID)
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

	//�n�`�I�u�W�F�N�g����
	for (auto& field : data["mapData"]["field"]) {
		int hModel = ModelLoader::Load(field["obj"]);
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
	for (auto& entity : data["mapData"]["entity"]) {
		Entity* gso = nullptr;

		OBJECT d = entity["obj"].template get<MapLoader::OBJECT>();
		switch (d)
		{
		case MapLoader::NONE:			gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_PLAYER:	gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_HANGER:	gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_BOMB:		gso = Instantiate<TestEntity>(pParent);	break;
		case MapLoader::OBJ_E_MUSHROOM:	gso = Instantiate<TestEntity>(pParent);	break;
		default: MessageBox(NULL, ((string)(NAMEOF_ENUM(d))).c_str(), "Error:Instantiate Entity", MB_OK);
		}

		gso->SetPosition((float)entity["pos"][0], (float)entity["pos"][1], (float)entity["pos"][2]);
		gso->SetRotate((float)entity["rot"][0], (float)entity["rot"][1], (float)entity["rot"][2]);
		gso->SetScale((float)entity["sca"][0], (float)entity["sca"][1], (float)entity["sca"][2]);
		pEntityList->push_back(gso);
	}
	
	//�����`����Load��ɏ���������H
}