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
	PowerUp = App->textures->Load("Assets/Granada_Bonus.png");
	paracaigudes = App->textures->Load("Assets/parachute1.png");
	explosion1 = App->textures->Load("Assets/explosion2.png");
	explosion2 = App->textures->Load("Assets/explosion3.png");
	explosion3 = App->textures->Load("Assets/water_explosion1.png");
	explosion4 = App->textures->Load("Assets/water_explosion2.png");
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
	if (App->physics->ball.rectenable == false) {
		App->renderer->Blit(Fondo, 0, 80, NULL);
		App->renderer->Blit(Techo, 0, -225, NULL);
		App->renderer->Blit(Terra, 0, 370, NULL);
		App->renderer->Blit(Agua, 350, 510, NULL);
		App->renderer->Blit(Wall, 300, 500, NULL);
		App->renderer->Blit(Wall, 600, 500, NULL);
		if (App->physics->ball.PowerUpAct == false)
		{
			App->renderer->Blit(PowerUp, 500, 200, NULL);
		}
		if (App->physics->ball.parachute == true) {
			App->renderer->Blit(paracaigudes, App->physics->ball.X - 17, App->physics->ball.Y - 50, NULL);
		}
		if (App->player->Explosion == true && App->physics->ball.radi == 5) {
			App->renderer->Blit(explosion1, App->physics->ball.X - 15, App->physics->ball.Y - 20, NULL);
		}
		if (App->player->Explosion == true && App->physics->ball.radi == 5 && App->physics->ball.buoyancy_enable == true) {
			App->renderer->Blit(explosion3, App->physics->ball.X - 25, App->physics->ball.Y - 30, NULL);
		}
		if (App->player->Explosion == true && App->physics->ball.radi != 5) {
			App->renderer->Blit(explosion2, App->physics->ball.X - 25, App->physics->ball.Y - 30, NULL);
		}
		if (App->player->Explosion == true && App->physics->ball.radi != 5 && App->physics->ball.buoyancy_enable == true) {
			App->renderer->Blit(explosion4, App->physics->ball.X - 45, App->physics->ball.Y - 70, NULL);
		}
	}
	
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
		App->physics->ball.parachute = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {//Disenable all the forces (pause)
		if (App->physics->ball.physenableF2 == false) {
			App->physics->ball.physenableF2 = true;
		}
		else {
			App->physics->ball.physenableF2 = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {//Draw colisions
		if (App->physics->ball.rectenable == false) {
			App->physics->ball.rectenable = true;
		}
		else {
			App->physics->ball.rectenable = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		if (App->physics->ball.F4 == false) {
			App->physics->ball.F4 = true;
			App->physics->ball.radi = 15;
			App->physics->ball.mass = 30;
			App->physics->ball.surface = App->physics->ball.radi * 2 / 3;
			App->physics->ball.surfaceRect = App->physics->ball.radi * 5 / 3;
			
		}
		else {
			App->physics->ball.F4 = false;
			App->physics->ball.radi = 5;
			App->physics->ball.surface = App->physics->ball.radi * 2; // m^2
			App->physics->ball.mass = App->physics->ball.surface * 5; // kg
			App->physics->ball.surfaceRect = App->physics->ball.radi * 5 / 3;
			App->renderer->DrawCircle(200, 100, 100, 250, 250, 250);
		}		
	}
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {//enable/disable gravity
		if (App->physics->grav == false) {
			App->physics->grav = true;
		}
		else {
			App->physics->grav = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {//enable/disable impulse force
		if (App->physics->ball.fimp == false) {
			App->physics->ball.fimp = true;
		}
		else {
			App->physics->ball.fimp = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {//enable/disable buoyancy forces
		if (App->physics->ball.buoyancy_ == false) {
			App->physics->ball.buoyancy_ = true;
		}
		else {
			App->physics->ball.buoyancy_ = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {//enable/disable drag forces
		if (App->physics->ball.fdrag == false) {
			App->physics->ball.fdrag = true;
		}
		else {
			App->physics->ball.fdrag = false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {//enable/disable drag forces
		if (App->player->moveControl == true) {
			App->player->moveControl = false;
		}
		else {
			App->player->moveControl = true;
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{

	return UPDATE_CONTINUE;
}
