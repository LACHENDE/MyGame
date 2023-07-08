#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "result.h"
#include "titleLogo.h"
#include "game.h"
#include "scene.h"
#include "polygon2D.h"
#include "resultLogo.h"
#include "title.h"

void Result::Init()
{
	AddGameObject<ResultLogo>(2);
}

void Result::Update()
{
	Scene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
}