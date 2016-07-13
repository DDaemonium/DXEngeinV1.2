﻿#include "StaticMesh.h"


StaticMesh::StaticMesh() : scale{ 1.f, 1.f, 1.f }, rotangles{ 0.0f, 0.0f, 0.0f}, translation{ 0.0f, 0.0f, 0.0f } {
	this->layout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	this->layout[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	this->layout[2] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	this->numElements = ARRAYSIZE(this->layout);
	/*if (!this->InitScene())	//Initialize our scene
	{
		MessageBox(0, L"Scene Initialization - Failed", L"Error", MB_OK);
	}*/
}

/*struct StaticMesh::Material
{
	Material() { ZeroMemory(this, sizeof(this)); }
	bool hasTexture;
	bool hasNormMap;
	float specularFactor;
	float reflectionFactor;
	std::string diffuseMap;
	std::string normalMap;
	PCFLOAT3 ambient;
	PCFLOAT3 diffuse;
	PCFLOAT3 specular;
	PCFLOAT3 transparency;
};*/


bool StaticMesh::InitScene(ID3D11Device* d3d11Device, ID3D11DeviceContext* d3d11DevCon){
	this->d3d11Device = d3d11Device;
	this->d3d11DevCon = d3d11DevCon;

	D3DX11CompileFromFile(L"Effects.fx", 0, 0, "VS", "vs_4_0", 0, 0, 0, &VS_Buffer, 0, 0);

	D3DX11CompileFromFile(L"Effects.fx", 0, 0, "D2D_PS", "ps_4_0", 0, 0, 0, &D2D_PS_Buffer, 0, 0);
	this->d3d11Device->CreatePixelShader(D2D_PS_Buffer->GetBufferPointer(), D2D_PS_Buffer->GetBufferSize(), NULL, &D2D_PS);
	//Create the Shader Objects
	this->d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	
	//Set Vertex and Pixel Shaders
	this->d3d11DevCon->VSSetShader(VS, 0, 0);

	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * this->indecis.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	
	iinitData.pSysMem = &(this->indecis[0]);
	this->d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);

	this->d3d11DevCon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * this->vertex.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &(this->vertex[0]);

	this->d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &squareVertBuffer);

	//Set the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	this->d3d11DevCon->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);

	//Create the Input Layout
	this->d3d11Device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertLayout);

	//Set the Input Layout
	this->d3d11DevCon->IASetInputLayout(vertLayout);

	//Set Primitive Topology
	this->d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create the Viewport
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Width;
	viewport.Height = Height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	this->d3d11DevCon->RSSetViewports(1, &viewport);
	this->SetTextureName(L"56.jpg");

	// Describe the Sample State
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the Sample State
	this->d3d11Device->CreateSamplerState(&sampDesc, &CubesTexSamplerState);

	/* ↓ render states ↓ */
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	d3d11Device->CreateBlendState(&blendDesc, &Transparency);

	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.FillMode = D3D11_FILL_SOLID;//SOLID for normal
	wfdesc.CullMode = D3D11_CULL_NONE;//FRONT /BACK скрываем отображение
	wfdesc.FrontCounterClockwise = false;
	/* ↓ сглаживание ↓ */
	wfdesc.MultisampleEnable = false;
	wfdesc.AntialiasedLineEnable = true;
	this->d3d11Device->CreateRasterizerState(&wfdesc, &WireFrame);
	return true;
}

void StaticMesh::SetScale(float ScaleX, float ScaleY, float ScaleZ) {
	this->scale[0] = ScaleX;
	this->scale[1] = ScaleY;
	this->scale[2] = ScaleZ;
}

void StaticMesh::SetRotationAngles(float x, float y, float z) {
	this->rotangles[0] = x;
	this->rotangles[1] = y;
	this->rotangles[2] = z;
}

void StaticMesh::SetTranslation(float OffsetX, float OffsetY, float OffsetZ) {
	this->translation[0] = OffsetX;
	this->translation[1] = OffsetY;
	this->translation[2] = OffsetZ;
}

void StaticMesh::SetName(const std::string & name) {
	this->name = name;
}


float *StaticMesh::GetScale() {
	return this->scale;
}

float *StaticMesh::GetRotationAngles() {
	return this->rotangles;
}

float *StaticMesh::GetTranslation() {
	return this->translation;
}

void StaticMesh::Draw(){
	//Update Pixel shaders
	this->d3d11DevCon->VSSetShader(VS, 0, 0);
	//"fine-tune" the blending equation
	float blendFactor[] = { 0.f, 0.f, 0.f, 1.0f };
    
	//Set the default blend state (no blending) for opaque objects
	this->d3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
	this->d3d11DevCon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//Set the cubes vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	this->d3d11DevCon->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);
	//Render opaque objects//

	//Set the blend state for transparent objects
	this->d3d11DevCon->OMSetBlendState(Transparency, blendFactor, 0xffffffff);

	this->d3d11DevCon->PSSetShaderResources(0, 1, &CubesTexture);
	this->d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
	this->d3d11DevCon->RSSetState(WireFrame);

	this->d3d11DevCon->DrawIndexed(this->indecis.size(), 0, 0);

}

void StaticMesh::SetTextureName(const TCHAR* texture_name){
	this->texture_name = texture_name;
	D3DX11CreateShaderResourceViewFromFile(this->d3d11Device, this->texture_name, NULL, NULL, &CubesTexture, NULL);
}

StaticMesh::~StaticMesh() {
	squareVertBuffer->Release();
	squareIndexBuffer->Release();
	D2D_PS->Release();
	D2D_PS_Buffer->Release();
	VS->Release();
	VS_Buffer->Release();
	vertLayout->Release();
	WireFrame->Release();
	Transparency->Release();
}