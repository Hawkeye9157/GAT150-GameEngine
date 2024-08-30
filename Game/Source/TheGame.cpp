#include "TheGame.h"
#include "Engine.h"

#include <memory>

bool TheGame::Initialize()
{

    m_scene = std::make_unique<Scene>(m_engine);
    m_scene->SetGame(this);
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

    std::string text = "Score: " + std::to_string(points);
    
}

void TheGame::OnPlayerDead(const Event& event)
{
    //
}

void TheGame::OnAddPoints(const Event& event)
{
    points += 100;
}

void TheGame::EndGame()
{
    m_scene->RemoveAll();

    m_engine->GetRenderer().SetColor(0,0,0,0);
    
    std::string scenenames[] = {"Scenes/end.json"};
    for (auto sceneName : scenenames) {
        rapidjson::Document doc;
        Json::Load(sceneName, doc);
        m_scene->read(doc);

    }

    m_scene->Initialize();
}
