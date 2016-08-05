#pragma once
#include "ParseConvert.h"
#include "Camera.h"

class StaticModel
{
private:
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	std::vector<StaticMesh> model;
	std::string modelName;
public:
	StaticModel();
	StaticModel(ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon);
	bool LoadModelFBX(const std::string &fileName);
	bool InitializeModel();
	bool RenderModel(Camera &camera);
	void SetScale(float ScaleX, float ScaleY, float ScaleZ);
	void SetRotationAngles(float x, float y, float z);
	void SetTranslation(float OffsetX, float OffsetY, float OffsetZ);
	~StaticModel();
};

