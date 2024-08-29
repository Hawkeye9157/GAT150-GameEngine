#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent)


void EnemyComponent::Initialize()
{

	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

}

void EnemyComponent::Update(float dt)
{
	Vector2 direction = { 0,0 };

	//left movement
	 direction.x = -1;
	physics->ApplyForce(direction * speed);



	
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	std::cout << "collision" << std::endl;
	if (actor->tag == "player") {

	}
}

void EnemyComponent::read(const json_t& value)
{
	READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
}