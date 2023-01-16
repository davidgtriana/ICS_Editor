#pragma once
#include "event.h"

class Calendar {

public:
	std::vector<Event*> events;

    Calendar(){}

	bool readICSFile(std::string fileName) {
        std::ifstream fileRead;
        // was the file able to be opened
        fileRead.open(fileName);
        if (!fileRead) return false;

        std::string line, datatype, value;
        while (getline(fileRead, line)) {
            size_t colon_pos = line.find(':');
            std::string datatype = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 1);

            if (datatype == "BEGIN") {
                if (value == "VCALENDAR") {

                }
                if (value == "VEVENT") {
                    Event* event = new Event();
                    while (getline(fileRead, line)) {
                        size_t colon_pos = line.find(':');
                        datatype = line.substr(0, colon_pos);
                        value = line.substr(colon_pos + 1);

                        if (datatype == "DTSTART") {
                            event->start = value;
                        }
                        else if (datatype == "DTEND") {
                            event->end = value;
                        }
                        else if (datatype == "SUMMARY") {
                            event->summary = value;
                        }
                        else if (datatype == "END") {
                            if (value == "VEVENT") {
                                events.push_back(event);
                                break;
                            }
                        }
                        else {

                        }
                    }
                }

            }
            else if (datatype == "VERSION") {


            }
            else if (datatype == "PRODID") {


            }
            else if (datatype == "METHOD") {


            }
            else if (datatype == "TZ") {

            }
            else if (datatype == "END") {
                if (value == "VCALENDAR") {
                    break;
                }
            }
            else {

            }
        }
        fileRead.close();
        return true;
	}


    void printEvents() {
        if (events.size() == 0) return;
        for (Event* e : events) {
            std::cout << " Name: " << e->summary << std::endl;
            std::cout << "Start: " << e->start << std::endl;
            std::cout << "  End: " << e->end << std::endl;
            std::cout << std::endl;
        }
    }

    void updateEventNames(std::string newName) {
        if (events.size() == 0) return;
        for (Event* e : events) {
            e->summary = newName;
        }
    }

    void eraseEvents(int eventsToKeep) {
        std::cout << " ERASING UNDESIRED EVENTS - Events erased: " + (events.size() - eventsToKeep) << std::endl;
        events.erase(events.begin(), events.begin() + events.size() - eventsToKeep);
    }

    bool writeICSFile(std::string nameFile) {
        if (events.size() == 0) return false;
        std::ofstream file;
        file.open(nameFile);
        file << "BEGIN:VCALENDAR" << "\n";
        file << "VERSION:2.0" << "\n";
        file << "PRODID:<Paper//Online Tutoring//EN>" << "\n";
        file << "METHOD:PUBLISH" << "\n";
        file << "TZ:+00" << "\n";

        for (Event* e : events) {
            file << "BEGIN:VEVENT" << "\n";
            file << "DTSTART:" << e->start << "\n";
            file << "DTEND:" << e->end << "\n";
            file << "SUMMARY:" << e->summary << "\n";
            file << "END:VEVENT" << "\n";
        }

        file << "END:VCALENDAR" << "\n";
        file.close();
    }
};