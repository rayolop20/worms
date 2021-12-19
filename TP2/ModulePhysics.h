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
	bool shot = false;

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


		//buoyancy
		float buoyancy;
		float Vsub;

		//mass
		float mass;
		float density;

		//aerodinamics
		float surface; // Effective wet surface
		float surfaceRect;
		float cl; // Lift coefficient
		float cd; // Drag coefficient
		// String coeficients
		float cs1;
		float cs2;
		float cb;
		//drag forces
		float fdragx;
		float fdragy;
		//Hydrodynamics
		float buoyancyDragX;
		float buoyancyDragY;

		//has fisic enable?
		bool physenable = false;
		//Parachute enable?
		bool parachute = false;
		bool lock = false;
		//Is on water?
		bool buoyancy_enable = false;
		//prev position
		float prev_positionX;
		float prev_positionY;
		float prev_velocityX;
		float prev_velocityY;
		//Powerup Active P1
		int PowerUp1 = 0;
		//Powerup Active P2
		int PowerUp2 = 0;
		//Powerup Active when touched
		bool PowerUpAct = false;


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
		float fy;

		//impulse force
		float fimpx;
		float fimpy;

		//accel
		float accx;


		//mass
		float mass;

		//DEAD
		bool dead = false;

	}Player;

	class Player_Cannon2 //dont need Y because only is moving on X
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
		float fy;

		//impulse force
		float fimpx;
		float fimpy;

		//accel
		float accx;

		//mass
		float mass;

		//DEAD
		bool dead = false;

	}Player2;
	float walls[24] = { 0,700,1030,100,
						0,0,1030,100,
						600,500,50,500,
						300,500,50,500,
						-50,0,50,1000,
						1024,0,50,1000 };

	float water[4] = { 350,510,250,500 };

	float PowerUPP[4] = { 700,200, 40, 40 };

	float waterDensity;
	

	void integratorVerletBall(Ball& ball, float dt);
	void integratorVerletPlayer(Player_Cannon& player, float dt);
	void integratorVerletPlayer2(Player_Cannon2& player2, float dt);
	void DrawColisions();
	void OnColision(Ball& ball, float walls[]);
	void OnColisionPPup(Ball& ball, float PPups[]);
	void OnColisionPlayers(Player_Cannon& player, Ball& ball, Player_Cannon2& player2, float walls[], float collisionsPlayer[], float collisionsPlayer2[]);

private:

	bool debug;
};