#include "Engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>


int main(int argc, char* argv[]) {

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// create texture, using shared_ptr so texture can be shared
	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("metroid.png", engine->GetRenderer());
	res_t<Texture> texture2 = ResourceManager::Instance().Get<Texture>("metroid.png", engine->GetRenderer());
	

	

	while (!engine->IsQuit()) {
		engine->Update();

		engine->GetRenderer().SetColor(0,0,0,0);
		engine->GetRenderer().BeginFrame();

		engine->GetPS().Draw(engine->GetRenderer());
		for (int i = 0; i < 100; i++) {
			engine->GetRenderer().DrawTexture(texture.get(), randomf(800), randomf(600), randomf(360));
		}
		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();
	return 0;
}
