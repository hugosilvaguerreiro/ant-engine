//
// Created by huguntu on 04/04/21.
//

#include "Scene.h"

#include <utility>

namespace antEngine {
    Scene::Scene(std::string nodeId, Position pos) : Node(std::move(nodeId), pos) {}
}