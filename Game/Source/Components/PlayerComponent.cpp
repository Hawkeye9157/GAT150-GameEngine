#include "PlayerComponent.h"
#include "Engine.h"

void PlayerComponent::Initialize()
{

}

void PlayerComponent::Update(float dt)
{
	Vector2 direction{ 0,0 };
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A) || owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D) || owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x =  1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W) || owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_UP)) direction.y = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S) || owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) direction.y =  1;
	
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed);
}

void PlayerComponent::read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}