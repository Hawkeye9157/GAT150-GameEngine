#include "Engine.h"
#include <crtdbg.h>


bool Engine::Initialize()
{
	//eneble memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//create unique system objects
	m_renderer = std::make_unique<Renderer>();
	m_input = std::make_unique<Input>();
	m_audio = std::make_unique<Audio>();
	m_time = std::make_unique<Time>();
	m_ps = std::make_unique<ParticleSystem>();
	m_physics = std::make_unique<Physics>();

	//render window
	m_renderer->Initialize();
	m_renderer->CreateWindow("Game Engine", 800, 600);

	//initialize system objects
	m_input->Initialize();
	m_audio->Initialize();
	m_physics->Initialize();
	return true;
}

void Engine::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		//close app
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			quit = true;
		}
	}
	//update systems
	m_input->Update();
	m_audio->Update();
	m_time->Tick();
	m_ps->Update(m_time->GetDeltaTime());
	m_physics->Update(m_time->GetDeltaTime());

}

bool Engine::IsQuit()
{
	return quit;
}

void Engine::Shutdown()
{
	//close unique system objects
	m_renderer->Shutdown();
	m_input->Shutdown();
	m_audio->Shutdown();
	m_physics->Shutdown();

	//display memory leaks
	_CrtMemDumpAllObjectsSince(NULL);
}