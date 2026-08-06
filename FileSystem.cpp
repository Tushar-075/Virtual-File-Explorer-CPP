#include "FileSystem.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace
{
    bool isValidName(const std::string &name)
    {
        if (name.empty())
            return false;

        if (name == "." || name == "..")
            return false;

        if (name.find('/') != std::string::npos || name.find('\\') != std::string::npos)
            return false;

        return true;
    }

    // Folders before files, then alphabetical (case-insensitive) within each group.
    bool nodeLessThan(const Node *a, const Node *b)
    {
        if (a->isFile != b->isFile)
            return !a->isFile; // folders (isFile == false) come first

        std::string nameA = a->name;
        std::string nameB = b->name;
        std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
        std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);

        return nameA < nameB;
    }

    std::vector<Node *> sortedChildren(const Node *node)
    {
        std::vector<Node *> children = node->children;
        std::sort(children.begin(), children.end(), nodeLessThan);
        return children;
    }
}

FileSystem::FileSystem() : root(nullptr), current(nullptr)
{
    std::ifstream in("filesystem.txt");
    if (in.is_open())
    {
        in.close();
        load();
    }

    if (root == nullptr)
    {
        root = new Node("C:", false, nullptr);
        current = root;
    }
}

FileSystem::~FileSystem()
{
    delete root;
}

void FileSystem::help() const
{
    std::cout << "Available commands:\n";
    std::cout << "  help                 Show this help message\n";
    std::cout << "  mkdir <name>         Create a new folder\n";
    std::cout << "  touch <name>         Create a new file\n";
    std::cout << "  write <name>         Overwrite file contents\n";
    std::cout << "  read <name>          Print file contents\n";
    std::cout << "  append <name>        Append text to a file\n";
    std::cout << "  ls                   List contents of current folder\n";
    std::cout << "  cd <name|..|/>       Change directory\n";
    std::cout << "  pwd                  Print working directory\n";
    std::cout << "  tree                 Print folder tree\n";
    std::cout << "  delete <name>        Delete a file or folder\n";
    std::cout << "  exit                 Save and quit\n";
}

void FileSystem::mkdir(const std::string &folderName)
{
    if (!isValidName(folderName))
    {
        std::cout << "Invalid folder name. Names cannot be empty, '.', '..', or contain '/' or '\\'.\n";
        return;
    }

    if (current->hasChild(folderName))
    {
        std::cout << "A file or folder named '" << folderName << "' already exists.\n";
        return;
    }

    current->children.push_back(new Node(folderName, false, current));
    save();
}

void FileSystem::touch(const std::string &fileName)
{
    if (!isValidName(fileName))
    {
        std::cout << "Invalid file name. Names cannot be empty, '.', '..', or contain '/' or '\\'.\n";
        return;
    }

    if (current->hasChild(fileName))
    {
        std::cout << "A file or folder named '" << fileName << "' already exists.\n";
        return;
    }

    current->children.push_back(new Node(fileName, true, current));
    save();
}

void FileSystem::ls() const
{
    if (current->children.empty())
    {
        std::cout << "(empty)\n";
        return;
    }

    for (Node *child : sortedChildren(current))
    {
        if (child->isFile)
            std::cout << child->name << "  (" << child->content.size() << " bytes)\n";
        else
            std::cout << child->name << "/\n";
    }
}

void FileSystem::cd(const std::string &target)
{
    if (target.empty())
    {
        std::cout << "Usage: cd <folderName|..|/>\n";
        return;
    }

    if (target == "/")
    {
        current = root;
        return;
    }

    if (target == "..")
    {
        if (current->parent != nullptr)
            current = current->parent;
        else
            std::cout << "Already at root directory.\n";
        return;
    }

    Node *child = current->findChild(target);
    if (child == nullptr)
    {
        std::cout << "No such folder: " << target << "\n";
        return;
    }

    if (child->isFile)
    {
        std::cout << "'" << target << "' is a file, not a folder.\n";
        return;
    }

    current = child;
}

void FileSystem::pwd() const
{
    std::cout << buildPath(current) << "\n";
}

std::string FileSystem::buildPath(Node *node) const
{
    if (node == root)
        return root->name + "\\";

    std::vector<std::string> parts;
    for (Node *cur = node; cur != nullptr && cur != root; cur = cur->parent)
        parts.push_back(cur->name);

    std::string path = root->name + "\\";
    for (auto it = parts.rbegin(); it != parts.rend(); ++it)
    {
        path += *it;
        if (std::next(it) != parts.rend())
            path += "\\";
    }

    return path;
}

void FileSystem::tree() const
{
    std::cout << root->name << "\\\n";

    std::vector<Node *> children = sortedChildren(root);
    for (size_t i = 0; i < children.size(); ++i)
        printTree(children[i], "", i == children.size() - 1);
}

void FileSystem::printTree(Node *node, const std::string &prefix, bool isLast) const
{
    std::cout << prefix << (isLast ? "`-- " : "|-- ") << node->name
              << (node->isFile ? "" : "/") << "\n";

    std::string childPrefix = prefix + (isLast ? "    " : "|   ");
    std::vector<Node *> children = sortedChildren(node);

    for (size_t i = 0; i < children.size(); ++i)
        printTree(children[i], childPrefix, i == children.size() - 1);
}

void FileSystem::remove(const std::string &name)
{
    if (name.empty())
    {
        std::cout << "Usage: delete <name>\n";
        return;
    }

    Node *child = current->findChild(name);
    if (child == nullptr)
    {
        std::cout << "No such file or folder: " << name << "\n";
        return;
    }

    if (!child->isFile && !child->children.empty())
    {
        std::cout << "'" << name << "' is a non-empty folder. Delete it and all "
                  << child->children.size() << " item(s) inside? (y/n): ";

        std::string answer;
        std::getline(std::cin, answer);

        if (answer != "y" && answer != "Y")
        {
            std::cout << "Delete cancelled.\n";
            return;
        }
    }

    auto it = std::find(current->children.begin(), current->children.end(), child);
    if (it != current->children.end())
        current->children.erase(it);

    delete child;
    std::cout << "'" << name << "' deleted.\n";
    save();
}

void FileSystem::write(const std::string &fileName)
{
    if (fileName.empty())
    {
        std::cout << "Usage: write <fileName>\n";
        return;
    }

    Node *file = current->findChild(fileName);
    if (file == nullptr)
    {
        std::cout << "No such file: " << fileName << "\n";
        return;
    }

    if (!file->isFile)
    {
        std::cout << "'" << fileName << "' is a folder, not a file.\n";
        return;
    }

    std::cout << "Enter file contents.\n";
    std::cout << "Type :wq on a new line to save.\n";

    std::string content;
    std::string line;
    bool first = true;

    while (std::getline(std::cin, line))
    {
        if (line == ":wq")
            break;

        if (!first)
            content += "\n";

        content += line;
        first = false;
    }

    file->content = content;
    std::cout << "File saved.\n";
    save();
}

void FileSystem::read(const std::string &fileName) const
{
    if (fileName.empty())
    {
        std::cout << "Usage: read <fileName>\n";
        return;
    }

    Node *file = current->findChild(fileName);
    if (file == nullptr)
    {
        std::cout << "No such file: " << fileName << "\n";
        return;
    }

    if (!file->isFile)
    {
        std::cout << "'" << fileName << "' is a folder, not a file.\n";
        return;
    }

    std::cout << "-------------------------\n";
    if (file->content.empty())
        std::cout << "(empty file)\n";
    else
        std::cout << file->content << "\n";
    std::cout << "-------------------------\n";
}

void FileSystem::append(const std::string &fileName)
{
    if (fileName.empty())
    {
        std::cout << "Usage: append <fileName>\n";
        return;
    }

    Node *file = current->findChild(fileName);
    if (file == nullptr)
    {
        std::cout << "No such file: " << fileName << "\n";
        return;
    }

    if (!file->isFile)
    {
        std::cout << "'" << fileName << "' is a folder, not a file.\n";
        return;
    }

    std::cout << "Enter text to append.\n";
    std::cout << "Type :wq on a new line to save.\n";

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == ":wq")
            break;

        if (!file->content.empty())
            file->content += "\n";

        file->content += line;
    }

    std::cout << "Content appended.\n";
    save();
}

void FileSystem::saveHelper(Node *node, std::ofstream &out)
{
    if (node->isFile)
    {
        out << "F " << node->name << "\n";
        out << "CONTENT\n";
        out << node->content << "\n";
        out << "ENDCONTENT\n";
    }
    else
    {
        out << "D " << node->name << "\n";
        for (Node *child : node->children)
            saveHelper(child, out);
        out << "#\n";
    }
}

Node *FileSystem::loadHelper(std::ifstream &in, Node *parent)
{
    std::string line;
    if (!std::getline(in, line))
        return nullptr;

    if (line == "#")
        return nullptr;

    if (line.rfind("D ", 0) == 0)
    {
        std::string name = line.substr(2);
        Node *node = new Node(name, false, parent);

        try
        {
            while (Node *child = loadHelper(in, node))
                node->children.push_back(child);
        }
        catch (...)
        {
            delete node;
            throw;
        }

        return node;
    }

    if (line.rfind("F ", 0) == 0)
    {
        std::string name = line.substr(2);
        Node *node = new Node(name, true, parent);

        std::string marker;
        if (!std::getline(in, marker) || marker != "CONTENT")
        {
            delete node;
            throw std::runtime_error("Malformed save file: expected CONTENT marker after file '" + name + "'");
        }

        std::string content;
        std::string contentLine;
        bool first = true;
        bool closed = false;

        while (std::getline(in, contentLine))
        {
            if (contentLine == "ENDCONTENT")
            {
                closed = true;
                break;
            }

            if (!first)
                content += "\n";

            content += contentLine;
            first = false;
        }

        if (!closed)
        {
            delete node;
            throw std::runtime_error("Malformed save file: missing ENDCONTENT for file '" + name + "'");
        }

        node->content = content;
        return node;
    }

    throw std::runtime_error("Malformed save file: unrecognized line '" + line + "'");
}

void FileSystem::save()
{
    std::ofstream out("filesystem.txt");
    if (!out.is_open())
    {
        std::cout << "Error: could not save filesystem.\n";
        return;
    }

    saveHelper(root, out);
}

void FileSystem::load()
{
    std::ifstream in("filesystem.txt");
    if (!in.is_open())
        return;

    Node *newRoot = nullptr;

    try
    {
        newRoot = loadHelper(in, nullptr);
    }
    catch (const std::exception &e)
    {
        std::cout << "Warning: save file is corrupted (" << e.what() << "). Starting with a fresh filesystem.\n";
        delete newRoot;
        return;
    }

    if (newRoot == nullptr)
        return;

    delete root;
    root = newRoot;
    current = root;
}

std::string FileSystem::prompt() const
{
    return buildPath(current) + ">";
}