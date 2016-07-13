#pragma once
#include "StdaFx.h"
#include "Vertex.h"

class StaticMesh {
private:
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA iinitData;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexBufferData;
	D3D11_RASTERIZER_DESC wfdesc;
	D3D11_VIEWPORT viewport;

	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;

	ID3D11Buffer* squareIndexBuffer;
	ID3D11Buffer* squareVertBuffer;
	ID3D11VertexShader* VS;
	ID3D10Blob* VS_Buffer;
	ID3D10Blob* D2D_PS_Buffer;
	ID3D11PixelShader* D2D_PS;
	ID3D11InputLayout* vertLayout;
	D3D11_INPUT_ELEMENT_DESC layout[3];
	UINT numElements;
	const int Width = 300;
	const int Height = 300;
	ID3D11RasterizerState* WireFrame;
	ID3D11BlendState* Transparency;

	ID3D11ShaderResourceView* CubesTexture;
	ID3D11SamplerState* CubesTexSamplerState;

	float scale[3];//100%
	float rotangles[3];//default no rotation
	float translation[3];//default no translation
	std::string name;
	LPCTSTR texture_name;
	struct Material;
public:
	std::vector<Vertex> vertex;
	std::vector<int> indecis;

	explicit StaticMesh();
	bool InitScene(ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon);

	void SetScale(float ScaleX, float ScaleY, float ScaleZ);
	void SetRotationAngles(float x, float y, float z);
	void SetTranslation(float OffsetX, float OffsetY, float OffsetZ);
	void SetName(const std::string &name);
	float *GetScale();
	float *GetRotationAngles();
	float *GetTranslation();
	void SetTextureName(const TCHAR *texture_name);
	void Draw();
	~StaticMesh();
};