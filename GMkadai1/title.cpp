#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "title.h"
#include "titleLogo.h"
#include "game.h"
#include "scene.h"
#include "polygon2D.h"

void Title::Init()
{
	AddGameObject<TitleLogo>(2);
}

void Title::Update()
{
	Scene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Game>();
	}
}