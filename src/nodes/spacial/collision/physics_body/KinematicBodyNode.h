//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_KINEMATICBODYNODE_H
#define ANT_ENGINE_KINEMATICBODYNODE_H

#include "../../../Node.h"
#include "../CollisionShape.h"
#include "PhysicsBodyNode.h"
#include <eigen3/Eigen/Dense>

using namespace Eigen;

namespace antEngine {

    class KinematicBodyNode : public PhysicsBodyNode {
    public:
        explicit KinematicBodyNode(std::string id, Position pos, float mass=1.0);

    };
}

#endif //ANT_ENGINE_KINEMATICBODYNODE_H
