#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"



void TextureComponent::Initialize()
{
	if (!textureName.empty()) {
		
		texture = ResourceManager::Instance().Get<Texture>(textureName,owner->scene->engine->GetRenderer());
	}
}

void TextureComponent::Update(float dt)
{
	//
}

void TextureComponent::Draw(Renderer& renderer)
{
	Transform transform = owner->transform;
	renderer.DrawTexture(texture.get(), transform);
}

void TextureComponent::read(const json_t& value)
{
	READ_DATA_REQUIRED(value, textureName);
}

void TextureComponent::Write(json_t& value)
{

}