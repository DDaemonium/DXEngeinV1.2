#pragma once
#pragma comment (lib, "libfbxsdk-md.lib")
#include "StaticMesh.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <fbxsdk.h>

struct LclTransform {
	float translation[3];
	float rotation[3];
	float scaling[3];
};

class ParseConvert
{
private:
	std::string fileName, mtlName;
	struct Materials;
	std::vector<std::string> useMtl;
	std::map<std::string, std::unique_ptr<Materials>> materials;
	std::vector<PCFLOAT3> verteñis, normals;
	std::vector<PCFLOAT2> textÑoords;
	std::vector<LclTransform> LclTranslation;
	void clearAll();
public:
	std::vector<Vertex> vertex;
	std::vector<int> meshStartPosition, indecis;
	ParseConvert();
	bool LoadOBJ(const std::string &fileName);
	bool LoadMTL();
	bool LoadFBX(const std::string &fileName, std::vector<StaticMesh> &models);
	bool SaveDPM(const std::string &fileName);
	bool LoadDPM(const std::string &fileName);
	void Out();//delete
	~ParseConvert();
};

