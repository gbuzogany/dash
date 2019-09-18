#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <exception>
#include <functional>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#include <sstream>
#include <iomanip>

#include "Renderer.hpp"
#include "Texture.hpp"
#include "Vehicle.hpp"
#include "Dashboard.hpp"

int main(int argc, char* argv[])
{
    Renderer r;
    r.initGraphics();
    r.initShaders();
    
    Dashboard dash(r);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int running = 1;
    
    dash.renderFixed();
    
    while (running) {
        r.startFrame();
        
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
        
        dash.render();

        r.updateScreen();
        r.endFrame();
    }

    SDL_Quit();
    
    return 0;
}
