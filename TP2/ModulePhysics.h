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
	
	bool CleanUp();

	float Delta = 1.0f / 16.0f;

	class Ball
	{
	public:

		float speed(float Fx, float Fy);

		float radi;
		//position
		float X;
		float Y;

		//velocity
		float Vy;
		float Vx;

		//speed
		float sp;

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

	void integratorVerlet(Ball& ball, float dt);

private:

	bool debug;
};