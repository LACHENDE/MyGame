#include "main.h"
#include "scene.h"

#include "renderer.h"


#include "manager.h"

#include "game.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include"explosion.h"
#include "bullet.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "input.h"
#include "result.h"
#include "score.h"



void Game::Init()
{
	AddGameObject<Polygon2D>(0);
	AddGameObject<Camera>(0);
	AddGameObject<Field>(1);
	AddGameObject<Player>(1);
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(1.0f, 1.0f, 4.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(4.0f, 1.0f, 0.0f));

	Cylinder* cylinder = AddGameObject<Cylinder>(1);
	cylinder->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	cylinder->SetScale(D3DXVECTOR3(4.0f, 2.0f, 4.0f));

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 10.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 2.0f, 4.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-5.0f, 0.0f, 15.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 2.0f, 4.0f));
	}

	AddGameObject<Score>(2);

	//BGMçƒê∂
	Audio* bgm;
	bgm =AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\audio\\sample000.wav");
	bgm->Play(true);


}

void Game::Update()
{
	Scene::Update();
	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Result>();
	}
}