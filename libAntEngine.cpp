#include "libAntEngine.h"

#include <iostream>


Renderer::Renderer(WINDOW_SIZE window_size, std::string title) : window(sf::VideoMode(window_size.width, window_size.height), title) {
    this->size = window_size;
    this->current_frame =  sf::Image();
    this->current_frame.create(window_size.width, window_size.height);
    this->current_frame_sprite = sf::Sprite();
    this->current_frame_texture = sf::Texture();
}


void Renderer::renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) {
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


void Renderer::checkEvents() {

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

void Renderer::registerMouseHandler(MouseHandler &handler) {
    this->handler = &handler;
}


void Renderer::drawPixel(unsigned int x, unsigned int y, RGBA color) {
    sf::Color c = sf::Color(color.R, color.G, color.B, color.A);
    this->current_frame.setPixel(x,  y, c);
}


void Renderer::renderFrame() {
    this->current_frame_texture.loadFromImage(this->current_frame);
    this->current_frame_sprite.setTexture(this->current_frame_texture, true);

    this->window.clear();
    this->window.draw(this->current_frame_sprite);
    this->window.display();
}

void Renderer::clearFrame() {
    this->current_frame.create(this->size.width, this->size.height);
}


bool Renderer::windowOpen() {
    return this->window.isOpen();
}

void Renderer::start(Application& app) {
    while (this->windowOpen()) {
        this->checkEvents(); //checks if window has been closed
        app.execute();
        this->window.clear();
    }
    app.stop();
}