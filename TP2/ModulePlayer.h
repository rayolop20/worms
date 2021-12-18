#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody;

struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;

	Object() : graphic(NULL), body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	int rondacompt = 0;
	int rondacompt2 = 0;
	int Explosion_Count = 0;
	bool players = false;
	bool Explosion = false;
	SDL_Texture* Cannon = nullptr;
	SDL_Texture* Tank = nullptr;
	SDL_Texture* Cannon2 = nullptr;
	SDL_Texture* ball = nullptr;
	SDL_Texture* Tank2 = nullptr;

};