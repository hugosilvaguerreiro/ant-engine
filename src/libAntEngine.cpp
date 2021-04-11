#include "libAntEngine.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

namespace antEngine {

    AntEngine::AntEngine(WINDOW_SIZE window_size, std::string title) : window(sf::VideoMode(window_size.width, window_size.height), title) {
        this->size = window_size;
        this->current_frame =  sf::Image();
        this->current_frame.create(window_size.width, window_size.height);
        this->current_frame_sprite = sf::Sprite();
        this->current_frame_texture = sf::Texture();
    }

    void AntEngine::renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) {
        RGBA border = {0,0,0,255};//TODO: add option to method
        for(int i=0; i<size; i++) {
            for(int j=0; j<size; j++) {
                unsigned int x1= i+x;
                unsigned int y1= j+y;

                if(x1 < 0) { x1 = 0; } if(x1 > this->size.height) { x1 = this->size.height; }
                if(y1 < 0) { y1 = 0; } if(y1 > this->size.width)  { y1 = this->size.width; }

                if(stroke && (i - stroke_size < 0 || i +stroke_size > size
                              || j - stroke_size < 0 || j + stroke_size > size)) {
                    this->drawPixel(x1, y1, border);
                } else {
                    this->drawPixel(x1, y1, color);
                }
            }
        }
    }


    void AntEngine::checkEvents() {

        sf::Event event;
        while (this->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i position = sf::Mouse::getPosition(this->window);
            this->handler->onLeftClick(position.x, position.y);

        }
    }

    void AntEngine::registerMouseHandler(MouseHandler &handler) {
        this->handler = &handler;
    }


    void AntEngine::drawPixel(unsigned int x, unsigned int y, RGBA color) {
        sf::Color c = sf::Color(color.R, color.G, color.B, color.A);
        this->current_frame.setPixel(x,  y, c);
    }


    void AntEngine::renderFrame() {
        this->current_frame_texture.loadFromImage(this->current_frame);
        this->current_frame_sprite.setTexture(this->current_frame_texture, true);

        this->window.clear();
        this->window.draw(this->current_frame_sprite);
        this->window.display();
    }

    void AntEngine::clearFrame() {
        this->current_frame.create(this->size.width, this->size.height);
    }


    bool AntEngine::windowOpen() {
        return this->window.isOpen();
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
        while (this->windowOpen()) {

            this->checkEvents(); //checks if window has been closed
            this->physicsEngine.physicsUpdate();

            this->renderFrame();
            this->window.clear();
        }
        this->physicsEngine.stop();
        //app.stop();
    }

}
