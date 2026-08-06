#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node
{
public:
    // Basic information
    std::string name;
    bool isFile;

    // NEW: stores file contents
    std::string content;

    // Tree structure
    Node *parent;
    std::vector<Node *> children;

    Node(const std::string &name, bool isFile, Node *parent = nullptr);
    ~Node();

    bool hasChild(const std::string &childName) const;
    Node *findChild(const std::string &childName) const;
};

#endif
