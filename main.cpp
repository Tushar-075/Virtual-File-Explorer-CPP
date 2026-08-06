#include <iostream>
#include <sstream>
#include <string>
#include "FileSystem.h"

using namespace std;

static void parseInput(const string &line, string &command, string &argument)
{
    istringstream iss(line);
    iss >> command;

    getline(iss, argument);

    if (!argument.empty() && argument[0] == ' ')
        argument.erase(0, 1);
}

int main()
{
    FileSystem fs;

    cout << "===================================================\n";
    cout << " Virtual File Explorer (Terminal-Based, C++17)\n";
    cout << " Type 'help' to see the list of available commands.\n";
    cout << "===================================================\n\n";

    string line;
    string command;
    string argument;

    while (true)
    {
        cout << fs.prompt() << " ";

        getline(cin, line);

        if (cin.eof())
            break;

        if (line.empty())
            continue;

        parseInput(line, command, argument);

        if (command == "help")
        {
            fs.help();
        }

        else if (command == "mkdir")
        {
            fs.mkdir(argument);
        }

        else if (command == "touch")
        {
            fs.touch(argument);
        }

        else if (command == "write")
        {
            fs.write(argument);
        }

        else if (command == "read")
        {
            fs.read(argument);
        }

        else if (command == "append")
        {
            fs.append(argument);
        }

        else if (command == "ls")
        {
            fs.ls();
        }

        else if (command == "cd")
        {
            fs.cd(argument);
        }

        else if (command == "pwd")
        {
            fs.pwd();
        }

        else if (command == "tree")
        {
            fs.tree();
        }

        else if (command == "delete")
        {
            fs.remove(argument);
        }

        else if (command == "exit")
        {
            cout << "Saving filesystem...\n";
            fs.save();
            cout << "Goodbye!\n";
            break;
        }

        else
        {
            cout << "Unknown command.\n";
            cout << "Type 'help' to see all available commands.\n";
        }
    }

    return 0;
}