//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_SCENE_H
#define ANT_ENGINE_SCENE_H

#include "Node.h"

namespace antEngine {

    class Scene : public Node {
    public:
        Scene(std::string nodeId, Position pos);
    };
}

#endif //ANT_ENGINE_SCENE_H
