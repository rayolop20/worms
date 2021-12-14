#pragma once
#include "Module.h"
#include "Globals.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	update_status Update();
	PhysBody* CreateCircle(float x, float y, float radius);
	PhysBody* CreateRectangle(int x, int y, float rotation);
	
	bool CleanUp();

	float Delta = 1.0f / 16.0f;

	class Ball
	{
	public:
		float radi;
		//position
		float X;
		float Y;

		//velocity
		float Vy;
		float Vx;

		//force
		float fx;
		float fy;

		//impulse force
		float fimpx;
		float fimpy;

		//accel
		float accx;
		float accy;

		//mass
		float mass;

		//aerodinamics
		float surface; // Effective wet surface
		float cl; // Lift coefficient
		float cd; // Drag coefficient

		//has fisic enable?
		bool physenable = false;
	}ball;


	class Player_Cannon //dont need Y because only is moving on X
	{
	public:
		//position
		float X;
		float Y;
		float Angle;

		//velocity
		float Vx;

		//force
		float fx;

		//impulse force
		float fimpx;

		//accel
		float accx;

		//mass
		float mass;

	}Player;

	void integratorVerletBall(Ball& ball, float dt);
	void integratorVerletPlayer(Player_Cannon& player, float dt);

private:

	bool debug;
};