#include "Engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

int main(int argc, char* argv[]) {

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

#ifdef _DEBUG
	std::cout << "Debug" << std::endl;
#endif

	int i = 5;
	assert(i == 5);
	int* p = nullptr;
	//assert(p);

	while (!engine->IsQuit()) {
		engine->Update();

		engine->GetRenderer().SetColor(0,0,0,0);
		engine->GetRenderer().BeginFrame();

		engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();
	return 0;
}
