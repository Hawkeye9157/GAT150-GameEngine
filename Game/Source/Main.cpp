#include "Engine.h"
#include "Components/PlayerComponent.h"

#include <iostream>
#include <vector>
#include <cstdlib>

void func1(int i) { std::cout << "func" << i << ":\n"; }
void func2(int i) { std::cout << "!func" << i << ":\n"; }


int main(int argc, char* argv[]) {

	void(*fp)(int);

	fp = &func1;
	fp(5);

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
