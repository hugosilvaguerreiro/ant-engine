//
// Created by huguntu on 04/04/21.
//

#include "PhysicsEngine.h"
namespace antEngine {
    PhysicsEngine::PhysicsEngine() : delta(clock()), nodes() {}

    void PhysicsEngine::registerPhysicsBody(antEngine::PhysicsBodyNode *node) {
        this->nodes.insert(std::pair<std::string, antEngine::PhysicsBodyNode*>(node->id, node));
    }

    void PhysicsEngine::start() {
        this->delta = clock();
    }
    void PhysicsEngine::stop() {}

    bool PhysicsEngine::colliding(PhysicsBodyNode *node1, PhysicsBodyNode *node2) {
        // TODO implement
        return false;
    }

    void PhysicsEngine::collisionDetection() {
        // Naive implementation: compare all pairs o(n²)
        std::map<std::string, PhysicsBodyNode*>::iterator it;
        for (it = this->nodes.begin(); it != this->nodes.end(); it++) {
            std::map<std::string, PhysicsBodyNode*>::iterator it2;
            for (it2 = this->nodes.begin(); it2 != this->nodes.end(); it2++) {
                PhysicsBodyNode* node1 = it->second;
                PhysicsBodyNode* node2 = it2->second;
                if(node1 != node2 && this->colliding(node1, node2)) {
                    node1->onCollision(node2);
                    node2->onCollision(node1);
                }
            }
        }
    }

    void PhysicsEngine::doPhysicsStep(float d) {
        std::map<std::string, PhysicsBodyNode*>::iterator it;
        for (it = this->nodes.begin(); it != this->nodes.end(); it++) {
            it->second->onPhysicsStep(d);
        }
    }

    void PhysicsEngine::physicsUpdate() {
        float dt = (float)(clock() - this->delta)/CLOCKS_PER_SEC;

        // update all physics nodes
        this->doPhysicsStep(dt);
        // compute collisions and correct object positions
        this->collisionDetection();

        this->delta = clock();
    }

}
