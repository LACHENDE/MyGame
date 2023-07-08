#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include"title.h"
#include"audio.h"

Scene* Manager::m_Scene{};
Scene* Manager::m_NextScene{};

void Manager::Init()
{
	Renderer::Init();
	CInput::Init();
	Audio::InitMaster();
	//m_Scene = new Title();
	//m_Scene->Init();
	SetScene<Title>();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Renderer::Uninit();
	CInput::Uninit();
	Audio::UninitMaster();
}

void Manager::Update()
{
	CInput::Update();
	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}

	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();
	Renderer::End();
}
