#include "RivalObject.h"
#include "Engine/Model.h"
#include "Ground.h"
#include "GameData.h"
#include "ceiling.h"
#include "Engine/Debug.h"
#include <sstream>
//�߂��Ƃ��ɐj������
//time�t���[�����ɐj��3�ݒu
//�A�C�e����
//�R���X�g���N�^
RivalObject::RivalObject(GameObject* parent)
	: GameObject(parent, "RivalObject"), hModel_(-1)
{
}

//������
void RivalObject::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<ceiling>(this);
	std::fill(pNeedle, pNeedle + 30, nullptr);
}

//�X�V
void RivalObject::Update()
{
	if (nowPlaying) {

		//���Ɛj�̈ړ��ƃ��[�v30�s������߂�
		if (transform_.position_.x > -30)
		{
			transform_.position_.x -= GameData::GetSpeed() * 0.05f;
		}
		else
		{
			transform_.position_.x = -30 * -1;
		}
	}
}

//�`��
void RivalObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void RivalObject::Release()
{
}

void RivalObject::SpawnNeedle() {

	//���������g�Q�̂��肩��
	int bornNeedleCnt = 3 + (GameData::GetMeters() / 1000);
	if (bornNeedleCnt > 7)bornNeedleCnt = 7;
	Debug::Log("Meter = ");
	Debug::Log(std::to_string(GameData::GetMeters()));
	Debug::Log("�g�Q���� ������: "); Debug::Log(bornNeedleCnt, true);

	int tmp = rand() % 10; //0-9�̗�������
	for (int i = 0; i < 10; i++) {
		int tmp2 = i - tmp;
		if (tmp2 < 0)tmp2 += 10;
		if (tmp2 >= 0 && tmp2 < bornNeedleCnt) {
				pNeedle[setNeedlePtr] = Instantiate<Needle>(GetParent());
				pNeedle[setNeedlePtr]->SetPositionY((float)(i+1));
				setNeedlePtr++;
				if (setNeedlePtr == LOOP_NEEDLE_ARRAY)setNeedlePtr = 0;
		}
	}
}

void RivalObject::SpawnItem() {
	//���Ȃ����� ��{3+1000m����+1���� �e��GameScene
	Debug::Log("Meter = ");
	Debug::Log(std::to_string(GameData::GetMeters()));
	Debug::Log("���x�㏸�𐶐� ", true);
	pItem = Instantiate<Item>(GetParent());
	pItem->SetPositionY((float)(rand() % 10 + 1));
}