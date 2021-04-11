//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_PHYSICSENGINE_H
#define ANT_ENGINE_PHYSICSENGINE_H

#include <string>
#include <ctime>
#include "../nodes/spacial/collision/physics_body/PhysicsBodyNode.h"

namespace antEngine {

    class PhysicsEngine {
    std::map<std::string, PhysicsBodyNode*> nodes;
    clock_t delta;

    void doPhysicsStep(float d);
    void collisionDetection();
    bool colliding(PhysicsBodyNode* node1, PhysicsBodyNode* node2);

    public:
        PhysicsEngine();
        void start();
        void stop();
        void registerPhysicsBody(PhysicsBodyNode *node);
        void physicsUpdate();
    };
}



#endif //ANT_ENGINE_PHYSICSENGINE_H
