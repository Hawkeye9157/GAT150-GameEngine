#include "Engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>


int main(int argc, char* argv[]) {

	//create engine
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	
	//load assets
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::readFile("bread.txt", s);
	//std::cout << s << std::endl;

	rapidjson::Document doc;
	Json::Load("text.txt",doc);

	std::string name;
	int age;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(doc, name);
	READ_DATA(doc, age);
	READ_DATA(doc, isAwake);
	READ_DATA(doc,position);
	READ_DATA(doc,color);

	std::cout << name << std::endl;
	std::cout << age << std::endl;
	std::cout << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << color.g << color.b << color.a << std::endl;


	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("metroid.png", engine->GetRenderer());

		// create font, using shared+ptr so font can be shared
		res_t<Font> font = ResourceManager::Instance().Get<Font>("MONIMONI.ttf", 12);

		//creating text
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), s, { 1,0,0,1 });

		//creating actor
		Transform t{ Vector2{30,30}, 0,0};
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);

		//creating texture component
		//std::unique_ptr<TextureComponent> textureComponent = std::make_unique<TextureComponent>();
		//textureComponent->texture = texture;
		
		//adding texture component to actor
		//actor->AddComponent(std::move(textureComponent));

		while (!engine->IsQuit()) {
			engine->Update();
			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			engine->GetPS().Draw(engine->GetRenderer());
			engine->GetRenderer().DrawTexture(texture.get(), 300, 100, 0);
			text->Draw(engine->GetRenderer(), 1, 1);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}
