#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <fstream>
#include "Node.h"

class FileSystem
{
private:
    Node *root;
    Node *current;

    // Existing helpers
    void printTree(Node *node, const std::string &prefix, bool isLast) const;
    std::string buildPath(Node *node) const;

    // Save / Load helpers
    void saveHelper(Node *node, std::ofstream &out);
    Node *loadHelper(std::ifstream &in, Node *parent);

public:
    FileSystem();
    ~FileSystem();

    // Existing Commands
    void help() const;
    void mkdir(const std::string &folderName);
    void touch(const std::string &fileName);
    void ls() const;
    void cd(const std::string &target);
    void pwd() const;
    void tree() const;
    void remove(const std::string &name);

    // ===== NEW COMMANDS =====

    // Overwrite file contents
    void write(const std::string &fileName);

    // Print file contents
    void read(const std::string &fileName) const;

    // Append to an existing file
    void append(const std::string &fileName);

    // Save / Load entire filesystem
    void save();
    void load();

    // Prompt
    std::string prompt() const;
};

#endif