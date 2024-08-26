#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this,std::placeholders::_1);
}

void CharacterComponent::Update(float dt)
{
	Vector2 direction = { 0,0 };

	//left movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1;
	//right movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D) 
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x =  1;

	
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed);
	
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		owner->GetComponent<PhysicsComponent>()->SetVelocity(Vector2{ 0,-500 });
	}
}

void CharacterComponent::OnCollisionEnter(Actor*)
{
	EVENT_NOTIFY("PlayerDead")
	EVENT_NOTIFY_DATA("AddPoints",100)
	//std::cout << "Player Hit\n";
}

void CharacterComponent::read(const json_t& value)
{
	READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
	//
}