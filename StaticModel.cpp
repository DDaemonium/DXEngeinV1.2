#include "StaticModel.h"



StaticModel::StaticModel(){
}

StaticModel::StaticModel(ID3D11Device * d3d11Device, ID3D11DeviceContext * d3d11DevCon):d3d11Device(d3d11Device), d3d11DevCon(d3d11DevCon){
}

bool StaticModel::LoadModelFBX(const std::string &fileName){
	ParseConvert obj;
	int lastSlash = fileName.find_last_of('\\');
	int lastDot = fileName.find_last_of('.');
	this->modelName = fileName.substr(lastSlash + 1, lastDot - lastSlash - 1);
	if (obj.LoadFBX(fileName, model)) {//get model name
		return true;
	}
	else {
		return false;
	}
}
bool StaticModel::InitializeModel() {
		for (auto &mesh : model) {
			mesh.InitScene(this->d3d11Device, this->d3d11DevCon);
		}
	return true;
}

bool StaticModel::RenderModel(Camera &camera){
		for (auto &mesh : model) {
			camera.SetScale(mesh.GetScale());
			camera.SetRotationAngles(mesh.GetRotationAngles());
			camera.SetTranslation(mesh.GetTranslation());
			camera.SetWVPMatrix();
			mesh.Draw();
		}
	return true;
}


StaticModel::~StaticModel(){
}
