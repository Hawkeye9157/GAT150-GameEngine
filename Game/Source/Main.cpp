#include "Engine.h"

#include <iostream>
#include <vector>
#include <cstdlib>



using namespace std;

int main(int argc, char* argv[]) {
	g_engine.Initialize();
	bool quit = false;
	while (!quit) {
		g_engine.Update();

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}

	g_engine.Shutdown(); return 0;
}
