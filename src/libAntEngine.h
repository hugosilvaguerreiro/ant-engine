#ifndef ANT_ENGINE_LIBANTENGINE_H
#define ANT_ENGINE_LIBANTENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#include <bits/stdc++.h>

namespace antEngine {

    typedef struct {
        unsigned int width;
        unsigned int height;

    } WINDOW_SIZE;

    typedef struct {
        unsigned short int R;
        unsigned short int G;
        unsigned short int B;
        unsigned short int A;
    } RGBA;


    class MouseHandler {
    public:
        virtual void onLeftClick(int mousex, int mousey) {}
        virtual void onRightClick(int mousex, int mousey) {}
    };

    class Application;
    class Renderer {
        sf::Image         current_frame;
        sf::Texture       current_frame_texture;
        sf::Sprite        current_frame_sprite;
        MouseHandler* handler;

    public:
        WINDOW_SIZE       size;
        sf::RenderWindow  window;

        Renderer(WINDOW_SIZE size, std::string title="window");


        /*
            Renders a square
        */
        void renderSquare(int x, int y, int size, RGBA color, bool stroke=false, int stroke_size=1);

        /*
            Checks if any relevant event has happened
        */
        void checkEvents();

        void registerMouseHandler(MouseHandler& handler);

        /*
            Used to set the color of a pixel in the current frame
        */
        void drawPixel(unsigned int x, unsigned int y, RGBA color);

        // renders the current frame
        void renderFrame();

        //clears the pixels of the current frame;
        void clearFrame();

        // returns true if the window is still open, false otherwise
        bool windowOpen();

        //starts
        void start(Application& app);
    };


    class Application {
    public:
        Application(const Application&) = delete;
        Application(Renderer& renderer) { this->renderer = &renderer; }

        Renderer* renderer;
        virtual void execute() = 0;
        virtual void stop() = 0;
    };

}

#endif //ANT_ENGINE_LIBANTENGINE_H
