#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent)


void EnemyComponent::Initialize()
{

	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

	speed = (float)random(5);

}

void EnemyComponent::Update(float dt)
{
	Vector2 direction = { 0,0 };

	//left movement
	 direction.x = -1;
	physics->ApplyForce(direction * speed);

	speed += randomf(0.25f);

	owner->transform.position.x = Math::Wrap(owner->transform.position.x, (float)owner->scene->engine->GetRenderer().GetWidth());
	owner->transform.position.y = Math::Wrap(owner->transform.position.y, (float)owner->scene->engine->GetRenderer().GetWidth());
	
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	std::cout << "collision" << std::endl;
	if (actor->tag == "player") {
		actor->Deactivate();
	}
}

void EnemyComponent::read(const json_t& value)
{
	READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
}