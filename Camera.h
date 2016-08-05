#pragma once
#include "StdaFx.h"



class Camera
{
private:
	D3D11_BUFFER_DESC cbbd;

	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX camView;
	XMMATRIX camProjection;
	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;

	XMMATRIX rotation;
	XMMATRIX scale;
	XMMATRIX translation;
	XMVECTOR rotaxeX;
	XMVECTOR rotaxeY;
	XMVECTOR rotaxeZ;
	float rotangles[3];//x y z
	ID3D11Buffer* cbPerObjectBuffer;
	struct cbPerObject
	{
		XMMATRIX  WVP;
		XMMATRIX  World;
	} cbPerObj;

	XMVECTOR DefaultForward;
	XMVECTOR DefaultRight;
	XMVECTOR DefaultTop;
	XMVECTOR camForward;
	XMVECTOR camRight;
	XMVECTOR camTop;

	XMMATRIX camRotationMatrix;
	XMMATRIX groundWorld;

	float moveLeftRight;
	float moveBackForward;
	float moveTopBottom;

	float camYaw;
	float camPitch;

public:
	explicit Camera();
	bool InitCamera(ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon);
	void SetCamPosition(float x, float y, float z, float w);
	void SetCamTarget(float x, float y, float z, float w);
	void SetCamUp(float x, float y, float z, float w);
	void SetCamProjection(float FovAngleY, float AspectRatio, float NearZ, float FarZ);

	void SetScale(float ScaleX, float ScaleY, float ScaleZ);
	void SetRotationAngles(float x, float y, float z);
	void SetTranslation(float OffsetX, float OffsetY, float OffsetZ);
	void SetScale(float *scale);
	void SetRotationAngles(float *angles);
	void SetTranslation(float *offset);

	void SetMoveLeftRight(const float &moveLeftRight);
	void SetMoveBackForward(const float &moveBackForward);
	void SetMoveTopBottom(const float &moveTopBottom);
	void SetCamYaw(const float &camYaw);
	void SetCamPitch(const float &camPitch);
	void SetWVPMatrix();
	/*void SetWVPMatrix(float Rotangle);*/
	void SetTextWVPMatrix();
	~Camera();
};

