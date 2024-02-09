#include "Transform.h"



Transform::Transform(): pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}


Transform::~Transform()
{
}

void Transform::Calclation()
{
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//��]�s��
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//�g��k��
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	if (pParent_)
	{
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}

void Transform::ConvDrawPos(float x, float y)
{
	position_.x = x / 40 * 0.062f;
	position_.y = y / -40 * 0.110f;
	position_.z = 0;
}

void Transform::SetScale(float all, float oX, float oY, float oZ)
{
	XMFLOAT3 oPos = { 0,0,0 };
	XMVECTOR oVec = XMLoadFloat3(&oPos);
	XMFLOAT3 pointPos = { oX,oY,oZ };
	XMVECTOR pointVec = XMLoadFloat3(&pointPos);
	XMFLOAT3 nowPos = position_;
	XMVECTOR nowVec = XMLoadFloat3(&nowPos);
	XMFLOAT3 nextPos;
	XMVECTOR tmpVec, tmpVec2;
	XMFLOAT3 tmpFloat;

	//�ړ��@�\(to�Ώ̓_)���g��@�\���ړ��ꏊ�v�Z���ړ��@�\(to�V�z�u�_)
	SetPosition(oPos);
	SetScale(all);

	tmpVec = nowVec - pointVec;
	XMStoreFloat3(&tmpFloat, tmpVec);
	tmpFloat.x *= all;
	tmpFloat.y *= all;
	tmpFloat.z *= all;
	tmpVec2 = XMLoadFloat3(&tmpFloat);
	tmpVec = pointVec + tmpVec2;
	XMStoreFloat3(&nextPos, tmpVec);
	SetPosition(nextPos);
}

