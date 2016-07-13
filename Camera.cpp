#include "Camera.h"

Camera::Camera() :rotangles{ 0.0f, 0.0f, 0.0f } {
	//Camera information
	this->camPosition = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
	this->camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	this->camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	/* ↓ for Mesh ↓ */
	this->scale = XMMatrixScaling(1.f, 1.f, 1.f);//default 100% scale
	this->translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);//defaul zero point position

	rotaxeZ = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);//z rotation
	rotaxeY = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);//y rotation
	rotaxeX = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);//x rotation
	//Set the Projection matrix
	this->camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, 1.0f, 1.0f, 1000.f);

}

bool Camera::InitCamera(ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon) {//default camera load
	//Create the buffer to send to the cbuffer in effect file
	this->d3d11DevCon = d3d11DevCon;
	this->d3d11Device = d3d11Device;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	this->d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);

	return true;
}


void Camera::SetCamPosition(float x, float y, float z, float w) {
	this->camPosition = XMVectorSet(x, y, z, w);
}

void Camera::SetCamTarget(float x, float y, float z, float w) {
	this->camTarget = XMVectorSet(x, y, z ,w);
}

void Camera::SetCamUp(float x, float y, float z, float w) {
	this->camUp = XMVectorSet(x, y, z, w);
}

void Camera::SetCamProjection(float FovAngleY, float AspectRatio, float NearZ, float FarZ) {
	this->camProjection = XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);
}

void Camera::SetScale(float ScaleX, float ScaleY, float ScaleZ) {
	this->scale = XMMatrixScaling(ScaleX, ScaleY, ScaleZ);
}

void Camera::SetRotationAngles(float x, float y, float z) {
	this->rotangles[0] = x;
	this->rotangles[1] = y;
	this->rotangles[2] = z;
}

void Camera::SetTranslation(float OffsetX, float OffsetY, float OffsetZ) {
	this->translation = XMMatrixTranslation(OffsetX, OffsetY, OffsetZ);
}

void Camera::SetScale(float *scale) {
	this->scale = XMMatrixScaling(scale[0], scale [1], scale[2]);
}

void Camera::SetRotationAngles(float *angles) {
	this->rotangles[0] = angles[0];
	this->rotangles[0] = angles[1];
	this->rotangles[0] = angles[2];
}

void Camera::SetTranslation(float *offset) {
	this->translation = XMMatrixTranslation(offset[0], offset[1], offset[2]);
}

void Camera::SetWVPMatrix() {
	this->rotation = XMMatrixRotationAxis(rotaxeZ, this->rotangles[0]) * XMMatrixRotationAxis(rotaxeY, this->rotangles[1]) * XMMatrixRotationAxis(rotaxeX, this->rotangles[2]);
	this->World = XMMatrixIdentity();
	this->World = this->rotation * this->translation * this->scale;
	//Set the View matrix
	this->camView = XMMatrixLookAtLH(this->camPosition, this->camTarget, this->camUp);
	this->WVP = this->World * this->camView * this->camProjection;
	this->cbPerObj.World = XMMatrixTranspose(this->WVP);
	this->cbPerObj.WVP = XMMatrixTranspose(this->WVP);
	this->d3d11DevCon->UpdateSubresource(this->cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	this->d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
}


//void Camera::SetWVPMatrix(float rotangle) {
//	this->rotation = XMMatrixRotationAxis(this->rotaxis, rotangle);
//	this->World = XMMatrixIdentity();
//	this->World = this->rotation * this->translation * this->scale;
//	//Set the View matrix
//	this->camView = XMMatrixLookAtLH(this->camPosition, this->camTarget, this->camUp);
//	this->WVP = this->World * this->camView * this->camProjection;
//	/*auto scal = XMMatrixScaling(1.2f, 1.2f, 1.2f);
//	WVP *= scal;
//	↑ ZOOM ↑*/
//	this->cbPerObj.World = XMMatrixTranspose(this->WVP);
//	this->cbPerObj.WVP = XMMatrixTranspose(this->WVP);
//	this->d3d11DevCon->UpdateSubresource(this->cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//	this->d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//}

void Camera::SetTextWVPMatrix() {
	this->WVP = XMMatrixIdentity();
	this->cbPerObj.World = XMMatrixTranspose(this->WVP);
	this->cbPerObj.WVP = XMMatrixTranspose(this->WVP);
	this->d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	this->d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
}

Camera::~Camera()
{
	this->cbPerObjectBuffer->Release();
}
