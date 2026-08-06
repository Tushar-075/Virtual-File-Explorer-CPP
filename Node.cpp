#include "Node.h"

Node::Node(const std::string &name, bool isFile, Node *parent)
    : name(name),
      isFile(isFile),
      content(""),
      parent(parent)
{
}

Node::~Node()
{
    for (Node *child : children)
    {
        delete child;
    }

    children.clear();
}

bool Node::hasChild(const std::string &childName) const
{
    return findChild(childName) != nullptr;
}

Node *Node::findChild(const std::string &childName) const
{
    for (Node *child : children)
    {
        if (child->name == childName)
        {
            return child;
        }
    }

    return nullptr;
}