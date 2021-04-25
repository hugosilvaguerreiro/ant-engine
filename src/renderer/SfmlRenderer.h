//
// Created by huguntu on 24/04/21.
//

#ifndef ANT_ENGINE_SFMLRENDERER_H
#define ANT_ENGINE_SFMLRENDERER_H


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

#include "Renderer.h"

namespace antEngine {
    class SfmlRenderer : public Renderer {
    public:
        sf::Image         current_frame;
        sf::Texture       current_frame_texture;
        sf::Sprite        current_frame_sprite;
        MouseHandler* handler;

        WINDOW_SIZE       size;
        sf::RenderWindow  window;

        SfmlRenderer(WINDOW_SIZE window_size, const std::string& title);

        void renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) override;

        void renderLine(int x1, int y1, int x2, int y2, RGBA color) override;

        void checkEvents() override;

        void registerMouseHandler(MouseHandler &handler) override;

        void drawPixel(unsigned int x, unsigned int y, RGBA color) override;

        void renderFrame() override;

        void clearFrame() override;

        bool windowOpen() override;

    };
}

#endif //ANT_ENGINE_SFMLRENDERER_H
