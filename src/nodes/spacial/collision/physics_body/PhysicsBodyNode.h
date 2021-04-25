//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_PHYSICSBODYNODE_H
#define ANT_ENGINE_PHYSICSBODYNODE_H

#include "../../../Node.h"
#include "../CollisionShape.h"
#include <eigen3/Eigen/Dense>

using namespace Eigen;

namespace antEngine {

    class PhysicsBodyNode : public Node {
    public:
        CollisionShape *shape{};
        float mass;
        Array22f velocity;

        explicit PhysicsBodyNode(std::string id, Position pos, float mass=1.0);

        void onCollision(PhysicsBodyNode* other);
        void onPhysicsStep(float delta);
    };
}

#endif //ANT_ENGINE_PHYSICSBODYNODE_H
