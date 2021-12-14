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

	
	ball.surface = 2; // m^2
	ball.mass = ball.surface * 5; // kg
	ball.cd = 0.4;
	ball.cl = 1.2;

	//position
	ball.X = 50.0;
	ball.Y = 700.0;
	ball.Vx = 0;
	ball.Vy = 0;
	ball.radi = 5;
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
	if (ball.physenable == true) {
		ball.fimpx = 0.0;
		ball.fimpy = 0.0;
	}
	//1#compute forces
	{
		
		//init grav
		float fgx = ball.mass * 0.0;
		float fgy = ball.mass * 2.0; // Let's assume gravity is constant and downwards

		//add grav
		ball.fx += fgx;
		ball.fy += fgy;

	}
	
	//2# Llei newton F=m*a
	{
		ball.accx = ball.fx / ball.mass;
		ball.accy = ball.fy / ball.mass;
	}
	
	//3#integrate
	{
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

			ball.fimpx += 50;
		}
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {

			ball.fimpy -= 50;
		}

		//add impulse force
		ball.accx += ball.fimpx;
		ball.accy += ball.fimpy;

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

		

		if (ball.physenable == true)
			{
				integratorVerlet(ball, Delta);
			}
	}


	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(float x, float y, float radius)
{
	App->renderer->DrawCircle(x,y,radius, 0,255,0);
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

void ModulePhysics::integratorVerlet(Ball& ball, float dt)
{
	ball.X += ball.Vx * dt + 0.5 * ball.accx * dt * dt;
	ball.Y += ball.Vy * dt + 0.5 * ball.accy * dt * dt;
	ball.Vx += ball.accx * dt;
	ball.Vy += ball.accy * dt;
}
