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
		Player.mass = 20;
		//position
		Player.X = 450;
		Player.Y = 650;
		Player.Vx = 0;
	}
//ball iniciation:
	{
		ball.surface = 2; // m^2
		ball.mass = ball.surface * 5; // kg
		ball.cd = 0.4;
		ball.cl = 0.1;
		ball.cs1 = 0.85;
		ball.cs2 = 0.7;
		

		//position
		
		ball.Vx = 0;
		ball.Vy = 0;
		ball.radi = 5;
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

	ball.fx = ball.fy = 0.0;
	ball.accx = ball.accy = 0.0;
	ball.fdragx = 0.0;
	ball.fdragy = 0.0;
	if (ball.physenable == true) {
		ball.fimpx = 0.0;
		ball.fimpy = 0.0;
	}
	if (ball.physenable == false) {
		ball.X = Player.X + 50;
		ball.Y = Player.Y;
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

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

		ball.fimpx += 50;
		//ball.fimpx = 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

		ball.fimpx -= 50;
		//ball.fimpx = 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		ball.fimpy -= 50;
		//ball.fimpy = -1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN || ball.parachute == true) {

		ball.parachute = true;
		ball.fdragy = ball.radi * ball.Vy * 0.1;
		ball.fdragx = ball.radi * ball.Vx * 0.1;
	}

	//Add impulse force
	ball.accx += ball.fimpx;
	ball.accy += ball.fimpy;
	//add drag force
	ball.accx -= ball.fdragx;
	ball.accy -= ball.fdragy;
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (ball.physenable == false)
		{
			ball.physenable = true;
		}
		else
		{
			ball.physenable = false;
		}
	}
	DrawColisions();
	OnColision(ball, walls);
	if (ball.physenable == true)
	{
		integratorVerletBall(ball, Delta);
	}
	
	//player update
	{
		Player.fx = 0.0;
		Player.accx = 0.0;

		//2# Llei newton F=m*a
		{
			Player.accx = Player.fx / Player.mass;
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

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	/*
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}*/

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

void ModulePhysics::DrawColisions()
{
	SDL_Rect rect1 = { 0,700,1030,100 };
	App->renderer->DrawQuad(rect1, 255, 0, 0);
	SDL_Rect rect2 = { 0,300,1030,100 };
	App->renderer->DrawQuad(rect2, 255, 0, 0);
	SDL_Rect rect3 = { 900,500,100,500 };
	App->renderer->DrawQuad(rect3, 255, 0, 0);
	SDL_Rect rect4 = { 100,500,100,500 };
	App->renderer->DrawQuad(rect4, 255, 0, 0);

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
			}
		}
	}
}
