//
// Created by huguntu on 04/04/21.
//

#include "RigidBodyNode.h"

#include <utility>

antEngine::RigidBodyNode::RigidBodyNode(std::string id, antEngine::Position pos, float mass) : PhysicsBodyNode(std::move(id), pos,
                                                                                                               mass) {

}
