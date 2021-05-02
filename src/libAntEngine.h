#ifndef ANT_ENGINE_LIBANTENGINE_H
#define ANT_ENGINE_LIBANTENGINE_H


#include <bits/stdc++.h>
#include "nodes/Scene.h"
#include "physics_engine/PhysicsEngine.h"
#include "renderer/Renderer.h"
#include "renderer/SfmlRenderer.h"
#include "renderer/AsciiRenderer.h"

namespace antEngine {


    class Application;
    class AntEngine {
    private:
        PhysicsEngine physicsEngine;
        Renderer *renderer;

        void loadSceneTree(Scene *scene);
    public:

        AntEngine(SIZE size, const std::string& title="window");

        //starts
        void start(Application& app);
    };


    class Application {
    public:
        Scene *mainScene = nullptr;
        AntEngine* engine;

        Application(const Application&) = delete;
        Application(AntEngine& engine) : engine(&engine) {}

    };


}

#endif //ANT_ENGINE_LIBANTENGINE_H
