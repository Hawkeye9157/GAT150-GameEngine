#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent)

void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this,std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{

	float rotate = 0;
	float thrust = 0;

	//left movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -1;
	//right movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D) 
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) rotate =  1;
	//up movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W) 
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = 1;
	//down movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S) 
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust =  -1;

	owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	Vector2 direction = Vector2{ 0,-1 }.Rotate(Math::DegToRad(owner->transform.rotation));
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);


	//shoot
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		auto rocket = Factory::Instance().Create<Actor>("rocket");

		rocket->transform.position = owner->transform.position;
		rocket->transform.rotation = owner->transform.rotation;

		owner->scene->AddActor(std::move(rocket),true);
		
	}
	
}

void PlayerComponent::OnCollisionEnter(Actor*)
{
	EVENT_NOTIFY("PlayerDead")
	EVENT_NOTIFY_DATA("AddPoints",100)
	//std::cout << "Player Hit\n";
}

void PlayerComponent::read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}