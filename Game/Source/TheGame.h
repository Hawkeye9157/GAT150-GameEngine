#pragma once
#include "Framework/Game.h"
#include "Event/Observer.h"
#include "Event/Event.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include <memory>

class TheGame : public Game, Observer {
public:

	TheGame() = default;
	TheGame(Engine* engine) : Game{ engine } {}
	

	bool Initialize() override;
	void ShutDown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);

	void EndGame() override;

private:
	std::unique_ptr<class Scene> m_scene;
	int points = 0;

	
};