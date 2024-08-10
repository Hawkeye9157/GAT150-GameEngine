#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
class TextureComponent : public RenderComponent {
public:

	CLASS_DECLARATION(TextureComponent)

	TextureComponent() = default;

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

public:
	std::string textureName;
	res_t<Texture> texture;
};
