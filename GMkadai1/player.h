#pragma once
#include "model.h"
#include "gameObject.h"

class Player:public GameObject
{
private:
	Model * m_Model{};

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_Velocity{};

	class Audio* m_ShotSE{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};