#pragma once
#include "component.h"
#include <vector>

class TilemapComponent : public Component {
public:
	TilemapComponent() = default;

	CLASS_DECLARATION(TilemapComponent)
	CLASS_PROTOTYPE(TilemapComponent)

	void Initialize() override;
	void Update(float dt) override;
public:
	int numColums = 0;
	int numRows = 0;
	Vector2 tileSize{ 0,0 };

	std::vector<std::string> tileNames;
	std::vector<int> tiles;
};