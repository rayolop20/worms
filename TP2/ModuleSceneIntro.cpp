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
	start = App->textures->Load("Assets/Start.png");
	end = App->textures->Load("Assets/Win.png");
	//Terra = App->textures->Load("Assets/Terra.png");
	//Fondo = App->textures->Load("Assets/Fondo.png");
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

	if (Fscreen == true)
	{
		App->renderer->Blit(start, 0, 0, NULL);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		Fscreen = false;
	}
	if (App->physics->Player.dead == true || App->physics->Player2.dead == true)
	{
		App->renderer->Blit(end, 0, 0, NULL);
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->physics->Player.dead = false;
		App->physics->Player2.dead = false;
	}	

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{

	return UPDATE_CONTINUE;
}
