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
	
	res_t<Font> font = ResourceManager::Instance().Get<Font>("MONIMONI.ttf",12);
	std::unique_ptr<Text> text = std::make_unique<Text>(font);
	text->Create(engine->GetRenderer(), "Hello World!", { 1,0,0,1 });
	

	

	while (!engine->IsQuit()) {
		engine->Update();

		engine->GetRenderer().SetColor(0,0,0,0);
		engine->GetRenderer().BeginFrame();

		engine->GetPS().Draw(engine->GetRenderer());
		engine->GetRenderer().DrawTexture(texture.get(), 300, 100, 0);
		text->Draw(engine->GetRenderer(),400,300);
		
		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();
	return 0;
}
