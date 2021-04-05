//
// Created by huguntu on 04/04/21.
//

#ifndef ANT_ENGINE_NODE_H
#define ANT_ENGINE_NODE_H


#include <map>
#include <string>
namespace antEngine {
    class Position {
    public:
        int x, y;
        Position(int x, int y);
    };

    class Node {
    public:
        std::string name;
        Node* parent;
        std::map<std::string, Node*> children;

        Position pos;

        // METHODS
        explicit Node(std::string name="");
        explicit Node(Node* parent, std::string name="");
        ~Node();

        void registerNode(const std::string& name, Node* node);
        Node* getNode(const std::string& name);

        void setPosition(int x, int y);

        // Called the first time the node is loaded/enters the scene
        virtual void ready();

        // Called every frame
        virtual void step();

        // Called every physics calculation
        virtual void physicsStep(const float& delta);

        // Called when the node leaves the scene/ is deleted
        virtual void clean();
    };

}

#endif //ANT_ENGINE_NODE_H
