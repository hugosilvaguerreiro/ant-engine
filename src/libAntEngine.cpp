#include "libAntEngine.h"
#include "renderer/NCursesRenderer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

namespace antEngine {

    AntEngine::AntEngine(WINDOW_SIZE window_size, const std::string& title) {
       // this->renderer = new SfmlRenderer(window_size, title);
       //this->renderer = new AsciiRenderer();
       this->renderer = new NCursesRenderer();
    }

    void AntEngine::loadSceneTree(Scene *scene) {

        std::map<std::string, Node*>::iterator it;

        for (it = scene->children.begin(); it != scene->children.end(); it++) {
            // for now we only have physics objects, so all should end up registered
            if (dynamic_cast<PhysicsBodyNode*>(it->second) != nullptr) {
                this->physicsEngine.registerPhysicsBody(dynamic_cast<PhysicsBodyNode*>(it->second));
            } else if (dynamic_cast<Scene*>(it->second) != nullptr) {
                this->loadSceneTree(dynamic_cast<Scene *>(it->second));
            } else {
                // do nothing for now
            }
        }
    }

    void AntEngine::start(Application& app) {
        if(app.mainScene == nullptr) {
            std::cerr << "Application does not have a main scene\n";
            exit(0);
        }
        // load the main scene
        this->loadSceneTree(app.mainScene);
        this->physicsEngine.start();
        while (this->renderer->windowOpen()) {
            //this->renderer->renderSquare(10,10, 600, RGBA{0,0,0,50});
            //this->renderer->renderSquare(100,100, 50, RGBA{0,0,0,200});
            //this->renderer->renderLine(10, 10, 500, 300,  RGBA{0,0,0,200});

            this->renderer->checkEvents(); //checks if window has been closed
            this->physicsEngine.physicsUpdate();
            app.mainScene->render(this->renderer);
            this->renderer->renderFrame();
            this->renderer->clearFrame();
        }
        this->physicsEngine.stop();
        //app.stop();
    }

}
