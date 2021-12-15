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
		// String coeficients
		float cs1;
		float cs2;
		

		float fdragx;
		float fdragy;

		//has fisic enable?
		bool physenable = false;
		//Parachute enable?
		bool parachute = false;
		//Colisions stuff
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

	float walls[16] = { 0,700,1030,100,
						0,300,1030,100,
						900,500,100,500,
						100,500,100,500};

	void integratorVerletBall(Ball& ball, float dt);
	void integratorVerletPlayer(Player_Cannon& player, float dt);
	void DrawColisions();
	void OnColision(float walls[]);

private:

	bool debug;
};