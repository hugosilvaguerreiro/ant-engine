//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_PHYSICSBODYNODE_H
#define ANT_ENGINE_PHYSICSBODYNODE_H

#include "../../../Node.h"
#include "../CollisionShape.h"
#include "../../../visual/Shape.h"
#include <eigen3/Eigen/Dense>

using namespace Eigen;

namespace antEngine {

    class PhysicsBodyNode : public Node {
        float accumulatedDelta = 0;
    public:
        CollisionShape *shape = nullptr;
        float mass;
        Array22f velocity;
        Shape *renderingShape= nullptr;

        explicit PhysicsBodyNode(std::string id, Position pos, float mass=1.0,
                                 Shape* renderingShape=nullptr, CollisionShape* shape= nullptr);

        void onCollision(PhysicsBodyNode* other);
        void onPhysicsStep(float delta);

        void render(Renderer *renderer) override;
        void input(Event event) override;
    };
}

#endif //ANT_ENGINE_PHYSICSBODYNODE_H
