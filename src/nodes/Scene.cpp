//
// Created by huguntu on 04/04/21.
//

#include "Scene.h"

#include <utility>

namespace antEngine {
    Scene::Scene(std::string nodeId, Position pos) : Node(std::move(nodeId), pos) {}

    void Scene::render(Renderer *renderer) {
        std::map<std::string, Node*>::iterator it;
        for (it = this->children.begin(); it != this->children.end(); it++) {
            it->second->render(renderer);
        }
    }
}