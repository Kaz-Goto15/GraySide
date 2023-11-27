#include <xaudio2.h>
#include <vector>
#include <cmath>
#include "Audio.h"

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

namespace Audio
{
	//XAudio�{��
	IXAudio2* pXAudio = nullptr;

	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;

	//�t�@�C�����ɕK�v�ȏ��
	struct AudioData
	{
		//�T�E���h���
		XAUDIO2_BUFFER buf = {};

		//�\�[�X�{�C�X
		IXAudio2SourceVoice** pSourceVoice = nullptr;

		//�����Đ��ő吔
		int svNum;

		//�t�@�C����
		std::string fileName;
	};
	std::vector<AudioData>	audioDatas;
}

//������
void Audio::Initialize()
{
	Confirm(CoInitializeEx(0, COINIT_MULTITHREADED), "Initialize");

	XAudio2Create(&pXAudio);
	pXAudio->CreateMasteringVoice(&pMasteringVoice);

}

//�T�E���h�t�@�C��(.wav�j�����[�h
int Audio::Load(std::string fileName, bool isLoop, int svNum)
{
	//���łɓ����t�@�C�����g���ĂȂ����`�F�b�N
	for (int i = 0; i < audioDatas.size(); i++)
	{
		if (audioDatas[i].fileName == fileName)
		{
			return i;
		}
	}

	//�`�����N�\����
	struct Chunk
	{
		char	id[5] = ""; 		// ID
		unsigned int	size = 0;	// �T�C�Y
	};

	//�t�@�C�����J��
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwBytes = 0;

	Chunk riffChunk = { 0 };
	Confirm(ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL), "open");
	Confirm(ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL), "open");

	char wave[4] = "";
	Confirm(ReadFile(hFile, &wave, 4, &dwBytes, NULL), "wave");

	Chunk formatChunk = { 0 };
	while (formatChunk.id[0] != 'f') {
		Confirm(ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL), "format chunk id");
	}
	Confirm(ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL), "format chunk size");


	//�t�H�[�}�b�g��ǂݎ��
	//https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
	WAVEFORMATEX fmt;
	Confirm(ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL), "format tag");		//�`��
	Confirm(ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL), "format channel");			//�`�����l���i���m����/�X�e���I�j
	Confirm(ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL), "foamat sps");	//�T���v�����O��
	Confirm(ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL), "format byte per sec");	//1�b������̃o�C�g��
	Confirm(ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL), "format block align");		//�u���b�N�z�u
	Confirm(ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL), "bit per sample");	//�T���v��������̃r�b�g��



	//�g�`�f�[�^�̓ǂݍ���
	Chunk data = { 0 };
	while (true)
	{
		//���̃f�[�^��ID�𒲂ׂ�
		ReadFile(hFile, &data.id, 4, &dwBytes, NULL);

		//�udata�v�������烋�[�v�𔲂��Ď��ɐi��
		if (strcmp(data.id, "data") == 0)
			break;

		//����ȊO�̏��Ȃ�T�C�Y���ׂēǂݍ��ށ��g��Ȃ�
		else
		{
			//�T�C�Y���ׂ�
			ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
			char* pBuffer = new char[data.size];

			//���ʂɓǂݍ���
			ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
		}
	}

	//�f�[�^�`�����N�̃T�C�Y���擾
	ReadFile(hFile, &data.size, 4, &dwBytes, NULL);

	//�g�`�f�[�^��ǂݍ���
	char* pBuffer = new char[data.size];
	ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
	CloseHandle(hFile);


	AudioData ad;

	ad.fileName = fileName;

	ad.buf.pAudioData = (BYTE*)pBuffer;
	ad.buf.Flags = XAUDIO2_END_OF_STREAM;

	if (isLoop)	ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;

	ad.buf.AudioBytes = data.size;


	ad.pSourceVoice = new IXAudio2SourceVoice * [svNum];

	for (int i = 0; i < svNum; i++)
	{
		pXAudio->CreateSourceVoice(&ad.pSourceVoice[i], &fmt);
	}
	ad.svNum = svNum;
	audioDatas.push_back(ad);

	//SAFE_DELETE_ARRAY(pBuffer);

	return (int)audioDatas.size() - 1;
}

//�Đ�
void Audio::Play(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			audioDatas[ID].pSourceVoice[i]->SubmitSourceBuffer(&audioDatas[ID].buf);
			audioDatas[ID].pSourceVoice[i]->Start();
			break;
		}
	}
}


void Audio::Stop(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		audioDatas[ID].pSourceVoice[i]->Stop();
		audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
	}
}

//�V�[�����Ƃ̉��
void Audio::Release()
{
	for (int i = 0; i < audioDatas.size(); i++)
	{
		for (int j = 0; j < audioDatas[i].svNum; j++)
		{
			audioDatas[i].pSourceVoice[j]->DestroyVoice();
		}
		SAFE_DELETE_ARRAY(audioDatas[i].buf.pAudioData);
	}
	audioDatas.clear();
}

//�{�̂̉��
void Audio::AllRelease()
{
	CoUninitialize();
	if (pMasteringVoice)
	{
		pMasteringVoice->DestroyVoice();
	}
	pXAudio->Release();
}



void Audio::SetPitch(int ID, float pitch)
{
	float convertPitch = std::pow(2.0f,pitch);

	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			audioDatas[ID].pSourceVoice[i]->SetFrequencyRatio(convertPitch);
			break;
		}
	}
}

bool Audio::Confirm(BOOL b, std::string msg = "fail")
{
	if (b == FALSE) {
		MessageBox(NULL, msg.c_str(), "Audio Error", MB_OK);
		return false;
	}
	return true;
}
