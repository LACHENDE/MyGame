#include "main.h"
#include "renderer.h"
#include "main.h"
#include "model.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
#include "enemy.h"
#include "score.h"
#include "manager.h"
#include "explosion.h"

void Bullet::Init()
{
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.3f);


	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");
}

void Bullet::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
void Bullet::Update()
{

	//m_Position += m_Velocity;
	m_Position += GetForward() * m_Velocity.z;

	if (m_Position.z > 10.0f)
	{
		//弾を消す予約をする
		SetDestroy();
		return;
	}

	//敵の衝突判定

	Scene* scene = Manager::GetScene();
	auto enemies=scene->GetGameObjects<Enemy>();


	for (Enemy* enemy:enemies)
	{
		D3DXVECTOR3 enemyPos = enemy->GetPosition();
		D3DXVECTOR3 direction = enemyPos - m_Position;
		float length = D3DXVec3Length(&direction);

		if (length<2.0f)
		{
			scene->AddGameObject<Explosion>(1)->SetPosition(enemyPos);

			SetDestroy();
			enemy->SetDestroy();

			Score* score = scene->GetGameObject<Score>();
			score->AddCount(1);
			return;
		}
	}
		


}
void Bullet::Draw()
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