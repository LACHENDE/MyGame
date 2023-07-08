#include "main.h"
#include "renderer.h"
#include "main.h"
#include "model.h"
#include "input.h"
#include "enemy.h"
void Enemy::Init()
{


	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,	"shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,		"shader\\vertexLightingPS.cso");
}
void Enemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
void Enemy::Update()
{



}
void Enemy::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	// マトリックス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();

}