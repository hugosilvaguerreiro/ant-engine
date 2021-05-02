//
// Created by huguntu on 02/05/21.
//

#include "Camera.h"

namespace antEngine {

    void Camera::ready() {
        Node::ready();
    }

    void Camera::step() {
        Node::step();
    }

    void Camera::physicsStep(const float &delta) {
        Node::physicsStep(delta);
    }

    void Camera::render(Renderer *renderer) {
        Node::render(renderer);
    }

    void Camera::clean() {
        Node::clean();
    }

    Camera::Camera(const std::string &nodeId, const Position &pos, const SIZE size) :
            Node(nodeId, pos), size(size) {

    }

    Position Camera::projectWorldPointToCameraCoordinates(int x1, int y1) {
        /*
         * ^ y
         * |
         * |  0 (x1, y1)
         * |
         * |       (cx, cy) = origin (0,0) in camera coordinates
         * |           0 ----------+
         * |           |           |
         * |           |           |
         * |           |           |
         * |           +-----------+
         * |
         * + ------------------------------>
         * (0,0)  WORLD COORDINATES        x
         *
         * Both (x1, y1) and (cx, cy) are in world coordinates.
         * This function return the position of (x1, y1) relative to
         * the origin of the camera coordinate system (cx, cy) in world coordinates.
         * */
        return Position(x1-this->pos.x, this->pos.y - y1);
    }

    // Returns true if the point is inside the current camera, false otherwise
    // (x1, y1) are expected to be in camera coordinates
    bool Camera::pointInsideCamera(int x1, int y1) {
        return x1 >= 0 && x1 <= this->size.width &&
               y1 >= 0 && y1 <= this->size.height;
    }
}
