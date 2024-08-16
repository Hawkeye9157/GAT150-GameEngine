#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
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

