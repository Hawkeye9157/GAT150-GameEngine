#pragma once
#include "RenderComponent.h"
#include <string>

class Text;

class TextComponent : public RenderComponent {
public:
	void Initialize() override;

	CLASS_DECLARATION(TextComponent)

	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	void SetText(const std::string& text);

public:
	std::string text;
	std::string fontName;
	int fontSize = 12;
	Color color{ 1,1,1,1 };

private:
	std::unique_ptr<Text> m_text;
	bool textChanged = true;
};