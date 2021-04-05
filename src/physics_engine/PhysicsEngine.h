//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_PHYSICSENGINE_H
#define ANT_ENGINE_PHYSICSENGINE_H

#include <string>
#include "../nodes/spacial/collision/physics_body/PhysicsBodyNode.h"

namespace antEngine {

    class PhysicsEngine {
    std::map<std::string, Node*> nodes;
    public:
        void registerPhysicsBody(std::string id, PhysicsBodyNode *node);

    };
}



#endif //ANT_ENGINE_PHYSICSENGINE_H
