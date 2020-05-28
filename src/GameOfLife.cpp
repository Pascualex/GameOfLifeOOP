#include "Engine/Engine.h"
#include "Engine/Spawner.h"
#include "Engine/Agents/GrassAgent.h"
#include "Engine/Agents/FireAgent.h"
#include "Auxiliar/Debug.h"
#include <iostream>
#include <string>
#include <signal.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Engine *engine = NULL;

void signal_handler(int signum) {
    if (engine == NULL) return;
    engine->stop();
}

using namespace std::chrono_literals;

int main() {
#ifdef _DEBUG
    // Prints the unfreed memory at the end of the execution
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // Avoids flushing with each line break
    std::setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);

    // Processes the interruption signal for safe interruption
    signal(SIGINT, signal_handler);

    try {
        srand((unsigned int) time(NULL));

        engine = new Engine(30, 20, 50ms);

        engine->add_spawner(new Spawner(new GrassAgent(13,  8), 100, 1, true, false));
        engine->add_spawner(new Spawner(new GrassAgent(16,  8), 100, 1, true, false));
        engine->add_spawner(new Spawner(new GrassAgent(13, 11), 100, 1, true, false));
        engine->add_spawner(new Spawner(new GrassAgent(16, 11), 100, 1, true, false));

        engine->add_spawner(new Spawner(new FireAgent(13,  8), 100, 50, true, true));
        engine->add_spawner(new Spawner(new FireAgent(16,  8), 100, 50, true, true));
        engine->add_spawner(new Spawner(new FireAgent(13, 11), 100, 50, true, true));
        engine->add_spawner(new Spawner(new FireAgent(16, 11), 100, 50, true, true));

        engine->run();

        delete engine;
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}