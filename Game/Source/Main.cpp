#include "Engine.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <vector>
#include <cstdlib>


int main(int argc, char* argv[]) {

	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	Factory::Instance().Register<EnginePhysicsComponent>(EnginePhysicsComponent::GetTypeName());
	Factory::Instance().Register<PlayerComponent>(PlayerComponent::GetTypeName());
	Factory::Instance().Register<TextComponent>(TextComponent::GetTypeName());

	//create engine
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	//create scene

	//load assets
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	rapidjson::Document doc;
	Json::Load("Scenes/scene.json",doc);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->read(doc);
	scene->Initialize();


	{

		while (!engine->IsQuit()) {
			//input

			//update
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			auto* actor = scene->GetActor<Actor>();
			if (actor) {

				actor->transform.scale = 1.0f + Math::Sin(engine->GetTime().GetTime());

				actor->transform.rotation += 60.0f;
				//actor->transform.rotation += 90 * engine->GetTime().GetDeltaTime();
			}

			//draw
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			//stop drawing
			engine->GetRenderer().EndFrame();
		}
	}
	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}
