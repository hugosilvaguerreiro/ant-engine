//
// Created by huguntu on 04/04/21.
//

#include "Node.h"

#include <utility>

namespace antEngine {

    Node::Node(std::string nodeId, Position pos) : children(), id(std::move(nodeId)), pos(pos), rotation(0) {}

    Node::Node(Node *parent, std::string  nodeId) : parent(parent), children(), id(std::move(nodeId)),
                                                    pos(Position(0,0)) {

    }

    void Node::registerNode(const std::string& name, Node *node) {
        std::pair<std::string ,Node*> p(name, node);
        this->children.insert(p);
        node->parent = this;
    }

    Node *Node::getNode(const std::string& name) {
        const std::map<std::string, Node *>::iterator &node = this->children.find(name);
        if (node  == this->children.end() ) {
            return nullptr;
        } else {
           return node->second;
        }
    }

    void Node::ready() {}

    void Node::step() {}

    void Node::physicsStep(const float &delta) {}

    void Node::clean() {}

    void Node::input(Event event) {}

    void Node::setPosition(int x, int y) {
        this->pos.x = x;
        this->pos.y = y;
    }

    void Node::render(Renderer *renderer) {

    }


    Node::~Node() = default;

    Position::Position(int x, int y) : x(x), y(y){

    }
}