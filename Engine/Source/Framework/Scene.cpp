#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Components/CollisionComponent.h"
#include <algorithm>


void Scene::Initialize()
{
	for (auto& actor : actors) {
		actor->Initialize();
	}
}


void Scene::Update(float dt)
{
	//update
	for (auto& actor : actors) {
		if (actor->isActive) {
			actor->Update(dt);
		}
	}
	//collision
	for (auto& actor1 : actors) {
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		//checks if collidible
		if (collision1 == nullptr) continue;

		for (auto& actor2 : actors) {
			//don't collide with itself
			if (actor1 == actor2) continue;
			
			//checks if collidible
			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if (collision2 == nullptr) continue;

			if (collision1->CheckCollision(collision2)) {
				if(actor1->OnCollisionEnter) actor1->OnCollisionEnter(actor2.get());
				if(actor2->OnCollisionEnter) actor2->OnCollisionEnter(actor1.get());
			}

		}
	}

	//destroy
	std::_Erase_remove_if(actors, [](auto& actor) { return actor->destroyed; });
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors) {
		if (actor->isActive) {
			actor->Draw(renderer);
		}
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	actors.clear();
}

void Scene::read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value,actors).IsArray()) {
		for (auto& actorValue : GET_DATA(value, actors).GetArray()) {
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->read(actorValue);
			AddActor(move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}

