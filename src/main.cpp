#include <iostream>
#include <fstream>

#include "../include/utils.h"
#include "../include/interpreter.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Open file
    ifstream file(argv[1]);

    // Check if file is open
    if (!file.is_open())
    {
        cout << "Could not open file " << argv[1] << endl;
        return 2;
    }

    Interpreter interpreter;
    // Read file
    string line;
    while (getline(file, line))
    {
        // strip the line
        line = rstrip(line);

        // ignore empty lines
        if (line.length() == 0)
        {
            continue;
        }

        // ignore comments. comments start with >>>
        if (line.substr(0, 3) == ">>>")
        {
            continue;
        }

        interpreter.set_source(line);
        interpreter.interpret();
    }
    
    return 0;
}