#pragma once
#include "gameObject.h"

class Camera :public GameObject
{
private:

	D3DXVECTOR3 m_Position{};
	D3DXVECTOR3 m_Target{};
	D3DXMATRIX m_ViewMatrix{};

public:
	void Init() override;
	void Update() override;
	void Draw() override;

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }

};