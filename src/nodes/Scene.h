//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_SCENE_H
#define ANT_ENGINE_SCENE_H

#include "Node.h"
#include "spacial/camera/Camera.h"

namespace antEngine {

    class Scene : public Node {
    public:
        Camera* camera;
        Scene(std::string nodeId, Position pos, Camera* camera= nullptr);

        void render(Renderer *renderer) override;
        void input(Event event) override;
    };
}

#endif //ANT_ENGINE_SCENE_H
