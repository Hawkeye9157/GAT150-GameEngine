#include "Engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>


int main(int argc, char* argv[]) {

	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	
	//auto a = Factory::Instance().Create<Actor>("Actor");



	//create engine
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	
	//load assets
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::readFile("bread.txt", s);
	std::cout << s << std::endl;

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
	std::cout << color.r <<  " " << color.g << " " <<  color.b << " " << color.a << std::endl;


	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("metroid.png", engine->GetRenderer());

		// create font, using shared+ptr so font can be shared
		res_t<Font> font = ResourceManager::Instance().Get<Font>("MONIMONI.ttf", 12);

		//creating text
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), s, { 1,0,0,1 });

		//creating actor
		Transform t{ Vector2{30,30}, 0,0 };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(t);

		//creating texture component
		auto textureComponent = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		textureComponent->texture = texture;

		//adding texture component to actor
		actor->AddComponent(std::move(textureComponent));

		while (!engine->IsQuit()) {
			//input

			//update
			engine->Update();
			actor->Update(engine->GetTime().GetDeltaTime());

			//draw
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();


			
			engine->GetRenderer().DrawTexture(texture.get(), 300, 100, 0);
			actor->Draw(engine->GetRenderer());
			text->Draw(engine->GetRenderer(), 1, 1);

			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}
