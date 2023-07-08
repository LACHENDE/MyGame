#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "gameObject.h"
#include "component.h"

void Polygon2D::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	//Sprite* sprite = AddComponent<Sprite>();
	AddComponent<Sprite>()->Init(100.0f, 100.0f, 300.0f, 200.0f, "asset\\texture\\field.jpg");
}
void Polygon2D::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
void Polygon2D::Update()
{
}
void Polygon2D::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	// �}�g���b�N�X�ݒ�
	Renderer::SetWorldViewProjection2D();
	
}