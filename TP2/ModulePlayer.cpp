#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{

}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	SDL_Rect player{ PlayerX,PlayerY,50,50 };
	App->renderer->DrawQuad(player, 0, 0, 255);

	if (App->input->GetKey(SDL_SCANCODE_D) ==  KEY_REPEAT)
	{
		PlayerX += 4;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		PlayerX -= 4;
	}
	return UPDATE_CONTINUE;
}



