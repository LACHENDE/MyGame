#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "main.h"
#include "model.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "gameObject.h"
#include "scene.h"
#include "game.h"
#include "result.h"
#include "cylinder.h"
#include "box.h"
#include "title.h"
#include "audio.h"


void Player::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\player.obj");


	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	m_ShotSE = AddComponent<Audio>();
	m_ShotSE->Load("asset\\audio\\sample001.wav");
}

void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	D3DXVECTOR3 oldPosition = m_Position;

	if (CInput::GetKeyPress('A'))
		m_Position -= GetRight() * 0.1f;


	if (CInput::GetKeyPress('D'))
		m_Position += GetRight() * 0.1f;


	if (CInput::GetKeyPress('W'))
		m_Position +=GetForward()* 0.1f;

	if (CInput::GetKeyPress('S'))
		m_Position -= GetForward() * 0.1f;

	Scene* scene = Manager::GetScene();


	//bullet
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
 		bullet->SetPosition(m_Position);

		m_ShotSE->Play();

	}

	if (CInput::GetKeyPress('R'))
		m_Rotation.x -= 0.1f;
	if (CInput::GetKeyPress('F'))
		m_Rotation.x += 0.1f;

	if (CInput::GetKeyPress('Q'))
		m_Rotation.y -= 0.1f;
	if (CInput::GetKeyPress('E'))
		m_Rotation.y += 0.1f;

	if (CInput::GetKeyPress('J'))
	{
		m_Velocity.y += 0.02f;
	}


	//重力
	m_Velocity.y -= 0.015f;
  
	//移動
	m_Position += m_Velocity;

	float groundHeight = 0.0f;


	//敵の衝突判定
	std::vector<Cylinder*>cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();

		D3DXVECTOR3 direction = m_Position - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);

		if (length < scale.x)
		{
			if (m_Position.y < position.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y;
			}

			break;
		}

	}
	
	std::vector<Box*>boxes = scene->GetGameObjects<Box>();

	for (Box* box : boxes)
	{
		D3DXVECTOR3 position = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();

		if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f && position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f)
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}

			break;
		}

	}

	//接地
	if (m_Position.y < groundHeight&&m_Velocity.y<0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

}


void Player::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	// マトリックス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y+D3DX_PI, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);
	
	m_Model->Draw();
	
}