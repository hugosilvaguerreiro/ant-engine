//
// Created by huguntu on 04/04/21.
//

#include <iostream>
#include <utility>
#include "PhysicsBodyNode.h"

namespace antEngine {

    // Users should implement these
    void PhysicsBodyNode::onCollision(antEngine::PhysicsBodyNode *other) {

    }

    // Users should implement these
    void PhysicsBodyNode::onPhysicsStep(float delta) {
       // std::cout << "On physics step " << this->id << " " << delta << "\n";
        
    }

    PhysicsBodyNode::PhysicsBodyNode(std::string nodeId, Position pos, float mass) : Node(std::move(nodeId), pos), mass(mass) {

    }

}