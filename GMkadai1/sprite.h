#pragma once
#include "component.h"

class Sprite:public Component
{
protected:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};

public:
	void Init(float x,float y,float Width,float Height,const char*TextureName);
	void Uninit();
	void Update();
	void Draw();


};