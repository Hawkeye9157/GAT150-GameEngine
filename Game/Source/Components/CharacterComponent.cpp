#include "CharacterComponent.h"
#include "Engine.h"
#include <string>
#include "EnemyComponent.h"
#include <Components/CircleCollisionComponent.h>

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this,std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

	scoreText = owner->GetComponent<TextComponent>();
}

void CharacterComponent::Update(float dt)
{
	bool groundCount = 1;
	Vector2 direction = { 0,0 };

	//left movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1;
	//right movement
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D) 
		|| owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x =  1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)
		&& !owner->scene->engine->GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE)) physics->SetVelocity(Vector2{ 0,-150 });

	physics->ApplyForce(direction * speed);
	
	if (owner->transform.position.x < 0 || owner->transform.position.x > 800 || owner->transform.position.y < 0 || owner->transform.position.y > 600) {
		owner->scene->GetGame()->EndGame();
	}
	
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	std::cout << "collision" << std::endl;
	if (actor->tag == "enemy") {
		owner->destroyed = true;
		owner->isActive = false;
	}
	if (actor->tag == "soul") {
		score += 100;
		actor->GetComponent<class AudioComponent>()->Play();
	}
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{

}

void CharacterComponent::read(const json_t& value)
{
	READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
	//
}