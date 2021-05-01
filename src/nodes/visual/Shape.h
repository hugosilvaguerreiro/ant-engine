//
// Created by huguntu on 17/04/21.
//

#ifndef ANT_ENGINE_SHAPE_H
#define ANT_ENGINE_SHAPE_H

#include "../Node.h"

namespace antEngine {
    struct vertex {
        int x;
        int y;
    };

    class Shape : public Node {
        /**
         * Shapes are assigned to other Nodes in order to give them a visual aspect
         * Shapes will be locked to the parent object and will move with it
         * TODO: Be able to move the shape relative to the parent node
         **/
    public:
        Shape(const std::string &nodeId, const Position &pos);

        void ready() override;
        void step() override;
    };

    class SquareShape : public Shape {
    public:
        int size;

        SquareShape(const std::string &nodeId, const Position &pos, int size);

        void ready() override;
        void step() override;

        void render(Renderer *renderer) override;


    };
}


#endif //ANT_ENGINE_SHAPE_H
