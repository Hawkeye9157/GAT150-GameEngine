#include "TheGame.h"
#include "Engine.h"

#include <memory>

bool TheGame::Initialize()
{

    m_scene = std::make_unique<Scene>(m_engine);
    std::string scenenames[] = {"scenes/game.json", "scenes/enemy.json"};
    for (auto sceneName : scenenames) {
        rapidjson::Document doc;
        Json::Load(sceneName, doc);
        m_scene->read(doc);

    }

    m_scene->Initialize();
  
    return true;
}

void TheGame::ShutDown()
{
    m_scene->RemoveAll();
}

void TheGame::Update(float dt)
{
    m_scene->Update(dt);
}

void TheGame::Draw(Renderer& renderer)
{
    m_scene->Draw(renderer);
}

void TheGame::OnPlayerDead(const Event& event)
{
    //
}

void TheGame::OnAddPoints(const Event& event)
{
    //
}
