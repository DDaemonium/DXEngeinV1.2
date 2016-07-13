#pragma once

struct PCFLOAT3 {
	float x;
	float y;
	float z;
	PCFLOAT3(const float &x = 0.f, const float &y = 0.f, const float &z = 0.f) :x(x), y(y), z(z) {}
	bool operator==(const PCFLOAT3 &xmlfloat3) const {
		return (this->x == xmlfloat3.x) && (this->y == xmlfloat3.y) && (this->z == xmlfloat3.z);
	}
};

struct PCFLOAT2 {
	float x;
	float y;
	PCFLOAT2(const float &x = 0.f, const float &y = 0.f) :x(x), y(y) {}
	bool operator==(const PCFLOAT2 &xmlfloat3) const {
		return (this->x == xmlfloat3.x) && (this->y == xmlfloat3.y);
	}
};

struct Vertex {

	PCFLOAT3 pos;
	PCFLOAT2 textCoord;
	PCFLOAT3 normals;
	Vertex(const PCFLOAT3 &pos = PCFLOAT3(), const PCFLOAT3 &normals = PCFLOAT3(), const PCFLOAT2 &textCoord = PCFLOAT2())
		:pos(pos), normals(normals), textCoord(textCoord) {}
	bool operator==(const Vertex &vertex)const {
		return (vertex.normals == this->normals) && (vertex.pos == this->pos) && (vertex.textCoord == this->textCoord);
	}
};
