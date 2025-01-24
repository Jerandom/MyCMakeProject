#include "EventLog/EventLogger.h"
#include <filesystem>

EventLogger::EventLogger() :
	SingletonClass(),
{
	
}

EventLogger::~EventLogger()
{
}

void EventLogger::log(std::string& fileName, 
LogPriority priority, 
std::string& message, 
...) {
     // thread safety
    std::lock_guard<std::mutex> lock(logMutex);

    // Check if the file or directory exists
    std::filesystem::path logPath(LOGS_PATH + fileName);
    if (!std::filesystem::exists(logPath.parent_path())) {
        std::filesystem::create_directories(logPath.parent_path());
    }

    std::ofstream logFile(path, std::ios_base::app);
    if (!logFile.is_open()) {
        // Handle error if the file can't be opened
        return;
    }

    logFile << "[" << getTimestamp() << "]" << " <" << logModeToString(priority) << "> "
     << ": " << message << std::endl;

    logFile.close();
}

std::string EventLogger::getLogTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Format to ddmmyyyy hrs:min:sec
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%d/%m/%Y %H:%M:%S");
    return oss.str();
}

std::string EventLogger::getFileTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Format to ddmmyyyy
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%d_%m_%Y");
    return oss.str();
}

std::string EventLogger::logModeToString(LogMode mode) {
    switch (mode) {
        case ERROR: return "ERROR";
        case DEBUG: return "DEBUG";
        case DEFAULT: return "DEFAULT";
        default: return "UNKNOWN";
    }
}