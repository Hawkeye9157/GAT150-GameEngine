#pragma once
#include "Components/Component.h"

class CharacterComponent : public Component{
public:
	CLASS_DECLARATION(CharacterComponent)
	CLASS_PROTOTYPE(CharacterComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor*);
	void OnCollisionExit(Actor*);



public:
	float speed = 0.0f;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
	class TextComponent* scoreText{ nullptr };

	int score = 0;
	bool gameover = false;
};