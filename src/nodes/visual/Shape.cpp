//
// Created by huguntu on 17/04/21.
//

#include <iostream>
#include <cmath>
#include "Shape.h"



namespace antEngine {

    Position rotate_point(Position point, Position pivot, float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);

        // translate point back to origin:
        point.x -= pivot.x;
        point.y -= pivot.y;

        // rotate point
        float xnew = (float)point.x * c - (float)point.y * s;
        float ynew = (float)point.x * s + (float)point.y * c;

        // translate point back:
        point.x = (int)xnew + pivot.x;
        point.y = (int)ynew + pivot.y;
        return point;
    }


    void antEngine::SquareShape::ready() {
        Node::ready();
    }

    void antEngine::SquareShape::step() {
        // use the position of the parent
        this->pos = this->parent->pos;
    }

    void antEngine::SquareShape::render(Renderer *renderer) {
        /**
         *   v1 --------- v2
         *   |            |
         *   |            |
         *   |            |
         *   v3 --------- v4
         *
         **/
        Position v1 = this->parent->pos;
        Position v2 = Position(v1.x + size, v1.y);
        Position v3 =Position(v1.x, v1.y + size);
        Position v4 = Position(v1.x + size, v1.y + size);

        Position pivot = Position(v1.x+size/2, v2.y+size/2);
        v1 = rotate_point(v1, pivot, this->parent->rotation);
        v2 = rotate_point(v2, pivot, this->parent->rotation);
        v3 = rotate_point(v3, pivot, this->parent->rotation);
        v4 = rotate_point(v4, pivot, this->parent->rotation);

        RGBA color = RGBA{0,0,0,200};

        renderer->renderLine(v1.x, v1.y, v2.x, v2.y, color);
        renderer->renderLine(v1.x, v1.y, v3.x, v3.y, color);
        renderer->renderLine(v2.x, v2.y, v4.x, v4.y, color);
        renderer->renderLine(v3.x, v3.y, v4.x, v4.y, color);
        renderer->drawWorldPixel(v4.x+1, v4.y+1, color);
    }

    SquareShape::SquareShape(const std::string &nodeId, const Position &pos, int size) : Shape(nodeId, pos), size(size){

    }

    void Shape::ready() {
        Node::ready();
    }

    void Shape::step() {
        Node::step();
    }

    Shape::Shape(const std::string &nodeId, const Position &pos) : Node(nodeId, pos) {

    }
}
