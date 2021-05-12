//
// Created by huguntu on 04/04/21.
//

#include "Scene.h"

#include <utility>

namespace antEngine {
    Scene::Scene(std::string nodeId, Position pos, Camera* camera) : Node(std::move(nodeId), pos), camera(camera) {}

    void Scene::render(Renderer *renderer) {
        renderer->setCamera(this->camera);

        std::map<std::string, Node*>::iterator it;
        for (it = this->children.begin(); it != this->children.end(); it++) {
            it->second->render(renderer);
        }
    }

    void Scene::input(Event event) {
        std::map<std::string, Node*>::iterator it;
        for (it = this->children.begin(); it != this->children.end(); it++) {
            it->second->input(event);
        }
    }
}