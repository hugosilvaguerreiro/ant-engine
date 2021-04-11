//
// Created by huguntu on 04/04/21.
//

#include <iostream>
#include "PhysicsBodyNode.h"

namespace antEngine {

    // User implementation
    void PhysicsBodyNode::onCollision(antEngine::PhysicsBodyNode *other) {

    }

    // User implementation
    void PhysicsBodyNode::onPhysicsStep(float delta) {
        std::cout << "On physics step " << this->id << " " << delta << "\n";
    }
}