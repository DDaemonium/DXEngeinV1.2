#pragma once
#include "ParseConvert.h"
#include "Camera.h"

class StaticModel
{
private:
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;

	float scale[3];
	float rotation[3];
	float tranlation[3];
	std::vector<StaticMesh> model;
	std::string modelName;
public:
	StaticModel();
	StaticModel(ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon);
	bool LoadModelFBX(const std::string &fileName);
	bool InitializeModel();
	bool RenderModel(Camera &camera);
	~StaticModel();
};

