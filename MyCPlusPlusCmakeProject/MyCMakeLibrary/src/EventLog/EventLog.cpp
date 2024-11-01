#include "EventLog/EventLogger.h"

EventLogger::EventLogger() :
	SingletonClass(),
    ThreadInterface(),
{
	
}

EventLogger::~EventLogger()
{
}

void EventLogger::log(std::string& path, LogPriority priority, std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety

    std::ofstream logFile(path, std::ios_base::app);
    if (!logFile.is_open()) {
        // Handle error if the file can't be opened
        return;
    }

    logFile << "[" << getTimestamp() << "]" << " <" << priorityToString(priority) << "> "
            << __func__ << ": " << message << std::endl;

    logFile.close();  // Optional but explicit
}

std::string EventLogger::getTimestamp() {
    std::ostringstream oss;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    oss << std::put_time(&tm, "%d%m%Y %H:%M:%S");
    return oss.str();
}

std::string EventLogger::priorityToString(LogPriority priority) {
    switch (priority) {
        case SEVERE: return "SEVERE";
        case NORMAL: return "NORMAL";
        case LOW: return "LOW";
        default: return "UNKNOWN";
    }
}


void EventLogger::run(void)
{
    //insert func here for thread operation
}