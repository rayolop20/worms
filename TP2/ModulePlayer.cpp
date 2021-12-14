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
	//3# integrate

	//player move
	{
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {

				App->physics->Player.fx -= 10;
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
				App->physics->Player.fx += 10;
			}
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP|| App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP) {
				App->physics->Player.Vx = 0;
			}
			//add impulse force Player
			App->physics->Player.accx += App->physics->Player.fx;

			App->physics->integratorVerletPlayer(App->physics->Player, App->physics->Delta);
		}

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	App->physics->CreateCircle(App->physics->ball.X, App->physics->ball.Y, App->physics->ball.radi);
	App->physics->CreateRectangle(App->physics->Player.X, App->physics->Player.Y, App->physics->Player.Angle);
	
	return UPDATE_CONTINUE;
}



