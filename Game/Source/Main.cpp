#include "Engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>


int main(int argc, char* argv[]) {

	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());

	//create engine
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	//create scene

	//load assets
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string buffer;
	File::readFile("Scenes/scene.json", buffer);
	std::cout << buffer << std::endl;

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

			//draw
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			//stop drawing
			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}
