// command_line_arguments.cpp
// compile with: /EHsc
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "calendar.h"
#include "event.h"

Calendar* calendar;

bool is_number(const std::string& s);

int main(int argc, char* argv[])
{

    // was the program run with the proper arguments?
    if (argc < 3) {
        std::cout << "file must be called with at least 2 arguments:\n - Name of the file\n - No. of events to not erase" << std::endl;
        system("pause");
        return 0;
    }

    // was the second argument a number?
    if (!is_number(argv[2])) {
        std::cout << "the second argument is not a number " << std::endl;
        system("pause");
        return 0;
    }
    
    std::string fileName = argv[1];
    calendar = new Calendar();
    if (!calendar->readICSFile(fileName)) {
        std::cout << "ERROR: It couldn't be opened" << std::endl;
        system("pause");
        return 0;
    };

    int eventsToKeep = std::stoi(argv[2]);
    std::cout << "name of the file: " << fileName << std::endl;
    std::cout << "Amount of events to keep: " << eventsToKeep << std::endl;
    std::cout << "number of events read: " << calendar->events.size() << std::endl;

    if (argc == 4) calendar->updateEventNames(argv[3]);

    //calendar->printEvents();

    calendar->eraseEvents(eventsToKeep);

    //calendar->printEvents();

    if (!calendar->writeICSFile("updated_" + fileName)) {
        std::cout << "ERROR: File couldn't be saved" << std::endl;
    }
    
    system("pause");
    return 0;
}


bool is_number(const std::string& s)
{
    return std::find_if(s.begin(), s.end(), [](unsigned char c) {
            return !std::isdigit(c); 
        }) == s.end();
}