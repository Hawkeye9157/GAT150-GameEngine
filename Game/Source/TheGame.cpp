#include "TheGame.h"
#include "Engine.h"

#include <memory>

bool TheGame::Initialize()
{

    m_scene = std::make_unique<Scene>(m_engine);
    std::string scenenames[] = { "scenes/tilemap.json","Scenes/scene.json","Scenes/game.json"};
    for (auto sceneName : scenenames) {
        rapidjson::Document doc;
        Json::Load(sceneName, doc);
        m_scene->read(doc);

    }

    m_scene->Initialize();

    //ADD_OBSERVER(PlayerDead, TheGame::OnPlayerDead)
    //ADD_OBSERVER(AddPoints, TheGame::OnAddPoints)
    
    

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
    std::cout << "Player Dead\n";
}

void TheGame::OnAddPoints(const Event& event)
{
    //
}
