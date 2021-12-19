#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

//player iniciation:
	{
		//player 1
		Player.mass = 20;
		//position
		Player.X = 150;
		Player.Y = 650;
		Player.Vx = 0;

		//player 2
		Player2.mass = 20;
		//position
		Player2.X = 800;
		Player2.Y = 650;
		Player2.Vx = 0;
	}
//ball iniciation:
	{
		ball.radi = 5;
		ball.surface = ball.radi*2; // m^2
		ball.mass = ball.surface * 5; // kg
		ball.density = ball.mass * ball.surface;
		ball.cd = 0.4;
		ball.cl = 0.1;
		ball.cs1 = 0.85;
		ball.cs2 = 0.7;
		ball.cb = 0.001;
		waterDensity = 1.0;
		

		//position
		
		ball.Vx = 0;
		ball.Vy = 0;
		
		ball.surfaceRect = ball.radi * 5;
	}
	return true;
}

//
update_status ModulePhysics::PreUpdate()
{
		/*1->Forces->Fg, Fd, Fc, Fb, Fk
	2->2a LL Newton -> SumF = m*a
	3-> INTEGRADOR
		-Euler:
			-BWD Xt = v*dt
			-FWD Vt = a*dt
		-Verlet -> Veloc
				Xt = v*dt + 1/2 adt^2
				Vt = a*dt
	4-> COLISIONS*/
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update() {
	if (Player.dead == false && Player2.dead == false && App->scene_intro->Fscreen == false)
	{
		float collisionsPlayer[4] = { Player.X, Player.Y ,50,50 };
		float collisionsPlayer2[4] = { Player2.X, Player2.Y, 50, 50};
								

		ball.fx = ball.fy = 0.0;
		ball.accx = ball.accy = 0.0;
		ball.fdragx = 0.0;
		ball.fdragy = 0.0;
		ball.buoyancy = 0.0;
		ball.Vsub = 0;
		ball.buoyancyDragX = 0.0;
		ball.buoyancyDragY = 0.0;
		if (ball.physenable == true && ball.physenableF2 == true) {
			ball.fimpx = 0.0;
			ball.fimpy = 0.0;
		}

		if (ball.physenable == false && ball.physenableF2 == true) {
			if (App->player->players == false)
			{
				ball.X = Player.X + 60;
				ball.Y = Player.Y + 10;
			}
			if (App->player->players == true)
			{
				ball.X = Player2.X - 10;
				ball.Y = Player2.Y + 10;
			}

		}
		//1#compute forces
		{

			//init grav
			float fgx = ball.mass * 0.0;
			float fgy = ball.mass * 10.0; // Let's assume gravity is constant and downwards

			ball.fx += fgx;
			ball.fy += fgy;
		}

		//2# Llei newton F=m*a
		{
			ball.accx = ball.fx / ball.mass;
			ball.accy = ball.fy / ball.mass;
		}

		//3#integrate

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && ball.lock == false) {

			ball.fimpx += 50;
			//ball.fimpx = 1000;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && ball.lock == false) {

			ball.fimpx -= 50;
			//ball.fimpx = 1000;
		}
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && ball.lock == false) {
			ball.fimpy -= 50;
			if (App->player->players == false)
			{
				if (Player.Angle > -60)
				{
					Player.Angle--;
				}
			}

			if (App->player->players == true)
			{
				if (Player2.Angle < 60)
				{
					Player2.Angle++;
				}

			}
			//ball.fimpy = -1000;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && ball.lock == false) {
			ball.fimpy += 50;
			if (App->player->players == false)
			{
				if (Player.Angle < 20)
				{
					Player.Angle++;
				}
			}

			if (App->player->players == true)
			{
				if (Player2.Angle > -20)
				{
					Player2.Angle--;
				}
			}

			//ball.fimpy = -1000;
		}
		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN || ball.parachute == true) && (ball.Y > ball.prev_positionY)) {

			ball.parachute = true;
			SDL_Rect parachueRect = { ball.X - 2.5 * ball.radi,ball.Y - 4.5 * ball.radi,ball.radi * 5,ball.radi };
			if (ball.rectenable == true) {
				App->renderer->DrawQuad(parachueRect, 0, 255, 0);
			}
			

			ball.fdragy = ball.surfaceRect / 5 - ball.mass * 0.3;

			if (ball.X < ball.prev_positionX) {
				ball.fdragx = ball.surfaceRect / 50 + ball.mass * 0.1;
			}
			if (ball.X > ball.prev_positionX) {
				ball.fdragx = -ball.surfaceRect / 50 - ball.mass * 0.1;
			}
			/*if(ball.Vy <= ball.prev_velocityX) {
				App->renderer->DrawCircle(400, 200, 100, 255, 255, 255);
			}*/


		}

		//Add impulse force
		ball.accx += ball.fimpx;
		ball.accy += ball.fimpy;
		//add drag force
		ball.accx += ball.fdragx;
		ball.accy += ball.fdragy;

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			shot = true;
			ball.physenable = true;
			ball.lock = false;
	
		}
		if (ball.rectenable == true) {
			DrawColisions();
		}

		OnColision(ball, walls);
		OnColisionPlayers(Player, ball, Player2, walls, collisionsPlayer, collisionsPlayer2);
		if (ball.PowerUpAct == false)
		{
			OnColisionPPup(ball, PowerUPP);
		}
	

		if (ball.buoyancy_enable == true) {
			ball.buoyancy = -(ball.mass * 10.0 * waterDensity * ball.Vsub * ball.cb);
			ball.buoyancyDragX = 10.0;
			if (ball.prev_positionY < ball.Y) {
				ball.buoyancyDragY = -50;

			}
			if (ball.prev_positionX < ball.X) {
				ball.buoyancyDragX = -20;
			}
			else {
				ball.buoyancyDragX = 20;

			}
			//gravetat * volum submergit * densitat fluid * coeficient
		}

		ball.accy += ball.buoyancy + ball.buoyancyDragY;
		ball.accx += ball.buoyancyDragX;

		if (ball.physenable == true && ball.physenableF2 == true)
		{
			ball.prev_positionX = ball.X;
			ball.prev_positionY = ball.Y;
			ball.prev_velocityX = ball.Vx;
			ball.prev_velocityY = ball.Vy;
			integratorVerletBall(ball, Delta);

		}

		//player update
		{
			Player.fx = 0.0;
			Player.accx = 0.0;

			Player2.fx = 0.0;
			Player2.accx = 0.0;
			//2# Llei newton F=m*a
			{
				Player.accx = Player.fx / Player.mass;
				Player2.accx = Player2.fx / Player2.mass;
			}
		}

		//reset ball
		if (shot == true)
		{
			if (ball.X > 1000 || ball.X < 0 || ball.Y < 0 || ball.Y > 758 || App->player->Explosion == true)
			{
				//Block Ball when you throw it
				//ball.lock = false;
				if (ball.PowerUpAct == true) {
					ball.PowerUp1++;
				}
				Player.Angle = 0;
				Player2.Angle = 0;
				ball.fimpx = 0;
				ball.fimpy = 0;
				ball.physenable = false;
				if (App->player->players == true ) {//Canviar de jugador
					App->player->players = false;
					shot = false;
					App->player->Explosion_Count = 0;
				}
				else if (App->player->players == false) {//Canviar de jugador
					App->player->players = true;
					shot = false;
					App->player->Explosion_Count = 0;
				}
				App->player->Explosion = false;
			}

		}
		if (App->player->Explosion_Count > 20)
		{
			App->player->Explosion = true;
		}
		if (ball.PowerUp1 == 2) {
			LOG("%d", ball.PowerUp1);
			ball.radi = 15;
			ball.mass = 30;
			ball.surface = ball.radi * 2 / 3;
			ball.surfaceRect = ball.radi * 5 / 3;
			App->renderer->DrawCircle(200, 100, 100, 250, 250, 250);
		}
		if (ball.PowerUp1 == 3) {
			LOG("%d", ball.PowerUp1);
			ball.radi = 5;
			ball.surface = ball.radi * 2; // m^2
			ball.mass = ball.surface * 5; // kg
			ball.surfaceRect = ball.radi * 5;
			ball.PowerUpAct = false;
			ball.PowerUp1 = 0;
		}


	}
	return UPDATE_CONTINUE;
}
PhysBody* ModulePhysics::CreateCircle(float x, float y, float radius)
{
	App->renderer->DrawCircle(x,y,radius, 0,255,0);
	return nullptr;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, float rotation)
{
	SDL_Rect player{x,y, 50,50};
	App->renderer->DrawQuad(player, 0,255,0);

	return nullptr;
}


//
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!

	return true;
}

void ModulePhysics::integratorVerletBall(Ball& ball, float dt)
{
		ball.X += ball.Vx * dt + 0.5 * ball.accx * dt * dt;
		ball.Y += ball.Vy * dt + 0.5 * ball.accy * dt * dt;
		ball.Vx += ball.accx * dt;
		ball.Vy += ball.accy * dt;
}

void ModulePhysics::integratorVerletPlayer(Player_Cannon& player, float dt)
{
	player.X += player.Vx * dt + 0.5 * player.accx * dt * dt;
	player.Vx += player.accx * dt;
}

void ModulePhysics::integratorVerletPlayer2(Player_Cannon2& player2, float dt)
{
	player2.X += player2.Vx * dt + 0.5 * player2.accx * dt * dt;
	player2.Vx += player2.accx * dt;
}


void ModulePhysics::DrawColisions()
{
	
	SDL_Rect rect1 = { 0,700,1030,100 };
	App->renderer->DrawQuad(rect1, 255, 0, 0);
	SDL_Rect rect2 = { 0,-5,1030,100 };
	App->renderer->DrawQuad(rect2, 255, 0, 0);
	SDL_Rect rect3 = { 600,500,50,500 };
	App->renderer->DrawQuad(rect3, 255, 0, 0);
	SDL_Rect rect4 = { 300,500,50,500 };
	App->renderer->DrawQuad(rect4, 255, 0, 0);
	SDL_Rect rect5 = { -10,0,10,1000 };
	App->renderer->DrawQuad(rect5, 25, 25, 0);
	SDL_Rect rect6 = { 1024,0,10,1000 };
	SDL_Rect PPup = { 700,200, 40, 40 };
	App->renderer->DrawQuad(PPup, 0, 0, 255);

		SDL_Rect water = { 350,510,250,500 };
		App->renderer->DrawQuad(water, 0, 0, 255);
	

}

void ModulePhysics::OnColision(Ball& ball, float walls[])
{//0,600,1100,400
	for (int i = 0; i < 16; i += 4) {
		if (ball.X > walls[i] && ball.X  < walls[i] + walls[i+2] && ball.Y > walls[i + 1] - 10 && ball.Y < walls[i + 1] + walls[i + 3] - 10
			|| ball.X > walls[i] && ball.X < walls[i] + walls[i + 2] && ball.Y > walls[i + 1] && ball.Y < walls[i + 1] + walls[i + 3]) {
			
			if ((ball.X > walls[i] + 10 && ball.X < walls[i] + walls[i + 2] - 10 && ball.Y - ball.radi > walls[i + 1] - 10 && ball.Y + ball.radi < walls[i + 1] + walls[i + 3] +  10)
				|| (ball.X > walls[i] + 10 && ball.X < walls[i] + walls[i + 2] - 10 && ball.Y > walls[i + 1] - 10 && ball.Y < walls[i + 1] + walls[i + 3] + 10)) {
				if (ball.Y > walls[i+1] + walls[i+3] -10) {
					ball.Y += 2;
				}
				else {
					ball.Y -= 2;
				}
				
				ball.Vy *= -ball.cs2;
				ball.Vx *= ball.cs1;
				App->renderer->DrawCircle(100, 100, 50, 250, 250, 250);
				App->player->Explosion_Count++;
			}
			
		if (ball.X > walls[i] -10 && ball.X < walls[i] + walls[i+2] +10 && ball.Y > walls[i+1] && ball.Y < walls[i+1] + walls[i+3] - 10) {
			if (ball.X > walls[i] + walls[i+2]-10) {
				ball.X += 2;
			}
			else {
				ball.X -= 2;
			}
			
			ball.Vx *= -ball.cs2;
			ball.Vy *= ball.cs1;
			App->renderer->DrawCircle(200, 100, 100, 250, 250, 250);
			App->player->Explosion_Count++;
		}
	
	}
		for(int i = 0; i < 4; i += 4) {
			if (ball.X > water[i] && ball.X  < water[i] + water[i + 2] && ball.Y > water[i + 1] && ball.Y < water[i + 1] + water[i + 3]) {
				App->renderer->DrawCircle(100, 300, 50, 0, 0, 255);
				ball.buoyancy_enable = true;
				if (ball.Y - ball.radi < water[i + 1] && ball.Y <= water[i+1]) {
					ball.Vsub = (ball.Y + ball.radi - water[i + 1]) * 2 * ball.radi;
					
				}
				if (ball.Y - 2*ball.radi >= water[i + 1]) {
					ball.Vsub = ((ball.Y + ball.radi - water[i + 1]) - (ball.Y - ball.radi - water[i+1])) * 2 * ball.radi;
				}	
				if (ball.Y > 510 && ball.Y < 512)
				{
					App->player->Explosion_Count++;
				}
			}
			else {
				ball.buoyancy_enable = false;
			}

		
		}
}

}void ModulePhysics::OnColisionPPup(Ball& ball, float PPup[])
{//0,600,1100,400
	for (int i = 0; i < 4; i += 4) {
		if (ball.X > PPup[i] && ball.X  < PPup[i] + PPup[i + 2] && ball.Y > PPup[i + 1] - 10 && ball.Y < PPup[i + 1] + PPup[i + 3] - 10
			|| ball.X > PPup[i] && ball.X < PPup[i] + PPup[i + 2] && ball.Y > PPup[i + 1] && ball.Y < PPup[i + 1] + PPup[i + 3]) {
			ball.PowerUpAct = true;
			//LOG("%d", ball.PowerUp1);250, 250);
		}
	}
}

void ModulePhysics::OnColisionPlayers(Player_Cannon& player, Ball& ball, Player_Cannon2& player2, float walls[], float collisionsPlayer[], float collisionsPlayer2[]) {
		for (int i = 0; i < 24; i += 4) {
			/*0, 700, 1030, 100,
				0, 0, 1030, 100,
				600, 500, 50, 500,
				300, 500, 50, 500*/
			if (player.X + 50 > walls[i] && player.X < walls[i] + walls[i + 2] && player.Y + 50 > walls[i + 1] && player.Y < walls[i + 1] + walls[i + 3]) {
				player.Vx = 0;
				if (player.X < walls[i]) {
					player.X -= 2;
				}
				if (player.X + 50 > walls[i] + walls[i + 2]) {
					player.X += 2;
				}
			}
			if (player2.X + 50 > walls[i] && player2.X < walls[i] + walls[i + 2] && player2.Y + 50 > walls[i + 1] && player2.Y < walls[i + 1] + walls[i + 3]) {
				player2.Vx = 0;
				if (player2.X < walls[i]) {
					player2.X -= 2;
				}
				if (player2.X + 50 > walls[i] + walls[i + 2]) {
					player2.X += 2;
				}
			}
		}	

		if (shot == true && App->player->players == true)
		{
			for (int i = 0; i < 4; i += 4) {
				if (ball.X > collisionsPlayer[i] && ball.X  < collisionsPlayer[i] + collisionsPlayer[i + 2] && ball.Y > collisionsPlayer[i + 1] - 10 && ball.Y < collisionsPlayer[i + 1] + collisionsPlayer[i + 3] - 10
					|| ball.X > collisionsPlayer[i] && ball.X < collisionsPlayer[i] + collisionsPlayer[i + 2] && ball.Y > collisionsPlayer[i + 1] && ball.Y < collisionsPlayer[i + 1] + collisionsPlayer[i + 3]) {
					//count++;//Collisions de pilota amb player
					//Boom();
					ball.physenable = false;
					//Explosion_ = true;
					//Canviar de jugador i destruir l'altre
					player.dead = true;
					shot = false;
					player.Angle = 0;
					player2.Angle = 0;
					ball.fx = 0;
					ball.fy = 0;
					ball.radi = 5;
					ball.surface = ball.radi * 2; // m^2
					ball.mass = ball.surface * 5; // kg
					ball.surfaceRect = ball.radi * 5;
					ball.PowerUpAct = false;
					ball.PowerUp1 = 0;

				}
			}
		}

		if (shot == true && App->player->players == false)
		{
			for (int i = 0; i < 4; i += 4) {
				if (ball.X > collisionsPlayer2[i] && ball.X  < collisionsPlayer2[i] + collisionsPlayer2[i + 2] && ball.Y > collisionsPlayer2[i + 1] - 10 && ball.Y < collisionsPlayer2[i + 1] + collisionsPlayer2[i + 3] - 10
					|| ball.X > collisionsPlayer2[i] && ball.X < collisionsPlayer2[i] + collisionsPlayer2[i + 2] && ball.Y > collisionsPlayer2[i + 1] && ball.Y < collisionsPlayer2[i + 1] + collisionsPlayer2[i + 3]) {
					//count++;//Collisions de pilota amb player
					//Boom();
					ball.physenable = false;
					//Explosion_ = true;
				
				  //Canviar de jugador i destruir l'altre
					player2.dead = true;
					shot = false;
					player.Angle = 0;
					player2.Angle = 0;
					ball.fx = 0;
					ball.fy = 0;
					ball.radi = 5;
					ball.surface = ball.radi * 2; // m^2
					ball.mass = ball.surface * 5; // kg
					ball.surfaceRect = ball.radi * 5;
					ball.PowerUpAct = false;
					ball.PowerUp1 = 0;

				}
			}
		}

}
