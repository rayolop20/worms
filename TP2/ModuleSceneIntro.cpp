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
	end1 = App->textures->Load("Assets/Win1.png");
	end2 = App->textures->Load("Assets/Win2.png");
	Fondo = App->textures->Load("Assets/background2.png");
	Techo = App->textures->Load("Assets/Techo.png");
	Terra = App->textures->Load("Assets/Terra.png");
	Wall = App->textures->Load("Assets/Wall.png");
	Agua = App->textures->Load("Assets/Agua.png");
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
	
	//App->renderer->Blit(Fondo, 0, 80, NULL);
	App->renderer->Blit(Techo, 0, -225, NULL);
	App->renderer->Blit(Terra, 0, 370, NULL);
	App->renderer->Blit(Agua, 350, 510, NULL);
	App->renderer->Blit(Wall, 300, 500, NULL);
	App->renderer->Blit(Wall, 600, 500, NULL);
	if (Fscreen == true)
	{
		App->renderer->Blit(start, 0, 0, NULL);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		Fscreen = false;
	}
	if (App->physics->Player.dead == true)
	{
		App->renderer->Blit(end2, 0, 0, NULL);
	}
	if (App->physics->Player2.dead == true)
	{
		App->renderer->Blit(end1, 0, 0, NULL);
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
