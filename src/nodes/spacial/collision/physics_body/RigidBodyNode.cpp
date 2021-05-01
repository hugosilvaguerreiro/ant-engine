//
// Created by huguntu on 04/04/21.
//

#include "RigidBodyNode.h"

#include <utility>

namespace antEngine {
    RigidBodyNode::RigidBodyNode(std::string id, antEngine::Position pos, float mass,
                                            Shape* renderingShape, CollisionShape* shape) :
                                        PhysicsBodyNode(std::move(id), pos, mass, renderingShape, shape) {
        if(this->renderingShape != nullptr) {
            renderingShape->parent = this;
        }
    }
}
