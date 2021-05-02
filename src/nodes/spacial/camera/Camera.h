//
// Created by huguntu on 02/05/21.
//

#ifndef ANT_ENGINE_CAMERA_H
#define ANT_ENGINE_CAMERA_H


#include "../../Node.h"

namespace antEngine {

    class Camera : public Node {
    public:
        SIZE size;
        Camera(const std::string &nodeId, const Position &pos, const SIZE size);

        void ready() override;

        void step() override;

        void physicsStep(const float &delta) override;

        void render(Renderer *renderer) override;

        Position projectWorldPointToCameraCoordinates(int x1, int y1);
        bool pointInsideCamera(int x1, int y1);

        void clean() override;

    };
}


#endif //ANT_ENGINE_CAMERA_H
