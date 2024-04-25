#ifndef _TIME_UTIL_H
#define _TIME_UTIL_H

#include <time.h>
#include <sstream>
#include <iomanip>

namespace TimeUtil
{
    inline time_t getEpochTime()
    {
        return time(0);
    }

    inline std::string epochTimeToStr(time_t epochTime,
        const char* format = "%d %b %Y %X")
    {
        struct tm sTime = {};
#if defined _MSC_VER
        localtime_s(&sTime, &epochTime);
#else
        localtime_r(&epochTime, &sTime);
#endif

        std::stringstream ssFmtDt;
        ssFmtDt << std::put_time(&sTime, format);
        return ssFmtDt.str();
    }
}
#endif