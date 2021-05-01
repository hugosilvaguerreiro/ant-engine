//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_RIGIDBODYNODE_H
#define ANT_ENGINE_RIGIDBODYNODE_H

#include "PhysicsBodyNode.h"

namespace antEngine {

    class RigidBodyNode : public PhysicsBodyNode {
    public:
       explicit RigidBodyNode(std::string id, Position pos, float mass=1.0,
                              Shape* renderingShape=nullptr, CollisionShape* shape= nullptr);

    };
}

#endif //ANT_ENGINE_RIGIDBODYNODE_H
