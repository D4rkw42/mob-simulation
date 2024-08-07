/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#pragma once

namespace app {
    // configurações iniciais e quit
    void ApplicationConfigure(void);
    void ApplicationQuit(void);

    // funcionamento geral da aplicação
    void update(int elapsedTime);
    void render(void);
}
