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
	Tank = App->textures->Load("Assets/tanque1.png");
	Cannon = App->textures->Load("Assets/cano_tanque1.png");
	Tank2 = App->textures->Load("Assets/tanque2.png");
	Cannon2 = App->textures->Load("Assets/cano_tanque2.png");
	ball = App->textures->Load("Assets/granada.png");

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
			if (players == false)
			{
				App->physics->Player.fx -= 10;
			}
			
			if (players == true)
			{
				App->physics->Player2.fx -= 10;
			}
		
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			if (players == false)
			{
				App->physics->Player.fx += 10;
			}
			
			if (players == true)
			{
				App->physics->Player2.fx += 10;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP) {
			App->physics->Player.Vx = 0;
			App->physics->Player2.Vx = 0;
		}

		//add impulse force Player
		App->physics->Player.accx += App->physics->Player.fx;
		App->physics->Player2.accx += App->physics->Player2.fx;
		App->physics->integratorVerletPlayer(App->physics->Player, App->physics->Delta);
		App->physics->integratorVerletPlayer2(App->physics->Player2, App->physics->Delta);
	}

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (App->scene_intro->Fscreen == false && App->physics->Player.dead == false && App->physics->Player2.dead == false)
	{
		App->physics->CreateCircle(App->physics->ball.X, App->physics->ball.Y, App->physics->ball.radi);
		App->physics->CreateRectangle(App->physics->Player.X, App->physics->Player.Y, App->physics->Player.Angle);
		App->physics->CreateRectangle(App->physics->Player2.X, App->physics->Player2.Y, App->physics->Player2.Angle);
		//textures
		App->renderer->Blit(Cannon, App->physics->Player.X + 23, App->physics->Player.Y + 23, NULL, 1.0f, App->physics->Player.Angle);
		App->renderer->Blit(Tank, App->physics->Player.X, App->physics->Player.Y, NULL);
		App->renderer->Blit(Cannon2, App->physics->Player2.X + 5, App->physics->Player2.Y + 23, NULL, 1.0f, App->physics->Player2.Angle);
		App->renderer->Blit(Tank2, App->physics->Player2.X, App->physics->Player2.Y, NULL);
		App->renderer->Blit(ball, App->physics->ball.X - 10, App->physics->ball.Y - 10, NULL);

	}

	return UPDATE_CONTINUE;
}