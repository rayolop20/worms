#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{

	SDL_Rect ground = { 0, 600, 1100, 400};
	App->renderer->DrawQuad(ground, 255, 255,255);
	
	SDL_Rect plat1 = { 200, 400, 200, 100};
	App->renderer->DrawQuad(plat1, 255, 0,0);
	
	SDL_Rect plat2 = { 600, 400, 200, 100 };
	App->renderer->DrawQuad(plat2, 255, 0,0);

	if (App->player->PlayerX == 200)
	{
		App->player->PlayerX = 650;
	}

	else if(App->player->PlayerX == 650)
	{
		App->player->PlayerX = 200;
	}

	return UPDATE_CONTINUE;
}
