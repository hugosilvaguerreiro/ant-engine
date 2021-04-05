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
        CollisionShape *shape;
        float mass;
        Array22f velocity;
    };
}

#endif //ANT_ENGINE_PHYSICSBODYNODE_H
