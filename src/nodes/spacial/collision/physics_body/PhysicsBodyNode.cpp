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
        this->accumulatedDelta += delta;

        /*if (this->accumulatedDelta > 0.25) {
            this->pos.y += 1;
            this->accumulatedDelta = 0;
            //this->rotation += 0.25;
        }*/
    }

    void PhysicsBodyNode::render(Renderer *renderer) {
        if(this->renderingShape != nullptr) {
            this->renderingShape->render(renderer);
        }
    }

    PhysicsBodyNode::PhysicsBodyNode(std::string id, Position pos, float mass, Shape *renderingShape,
                                     CollisionShape *shape) :  Node(std::move(id), pos), mass(mass),
                                     renderingShape(renderingShape), shape(shape), accumulatedDelta(0) {
        if(this->renderingShape != nullptr) {
            renderingShape->parent = this;
        }
    }

    void PhysicsBodyNode::input(Event event) {

    }

}