#pragma once
#include "Components/Component.h"

class EnemyComponent : public Component {
public:
	CLASS_DECLARATION(EnemyComponent)
	CLASS_PROTOTYPE(EnemyComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor*);
public:
	float speed = 1.0f;
	int direction = 0;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};