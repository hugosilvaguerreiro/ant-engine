#include "libAntEngine.h"
#include "renderer/NCursesRenderer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

namespace antEngine {

    AntEngine::AntEngine(SIZE window_size, const std::string& title) : inputManager(title) {
       // this->renderer = new SfmlRenderer(window_size, title);
       //this->renderer = new AsciiRenderer();
       this->renderer = new NCursesRenderer(window_size);
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
        this->inputManager.Start();
        while (this->renderer->windowOpen()) {
             this->renderer->checkEvents(); //checks if window has been closed

            //get all events
            while(this->inputManager.HasEvents()) {
                auto ev = this->inputManager.GetEvent();
                app.mainScene->input(*ev);
            }
            this->physicsEngine.physicsUpdate();

            app.mainScene->render(this->renderer);
            this->renderer->renderFrame();
            this->renderer->clearFrame();
        }
        this->physicsEngine.stop();
        this->inputManager.Stop();
        //app.stop();
    }

}
