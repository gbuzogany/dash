#include <exception>
#include <functional>
#include <vector>
#include <iostream>
#include <unistd.h>

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#include <sstream>
#include <iomanip>

#include "Renderer.hpp"
#include "Texture.hpp"
#include "Vehicle.hpp"
#include "Dashboard.hpp"
#include "Splash.hpp"

int main(int argc, char* argv[])
{
    Renderer r;
    r.initGraphics();
    r.initShaders();
    
    std::queue<Scene*> sceneQueue;
    sceneQueue.push((Scene*) new Splash(r));
    sceneQueue.push((Scene*) new Dashboard(r));
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    while (!sceneQueue.empty()) {
        bool running = true;
        
        Scene *currentScene = sceneQueue.front();
        currentScene->renderFixed();
        
        float delta;
        
        while (running) {
            delta = r.startFrame();
            
            SDL_Event ev;
            while (SDL_PollEvent(&ev))
            {
                if (ev.type == SDL_QUIT)
                {
                    running = 0;
                    break;
                }
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            running = currentScene->render(delta);
            
            r.updateScreen();
            r.endFrame();
        }
        sceneQueue.pop();
    }
    SDL_Quit();
    
    return 0;
}
