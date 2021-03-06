/*
 * =====================================================================================
 *
 *    Description:  a tiny library of C++11 for flexible logging to files
 *
 *        Version:  1.0
 *        Created:  2015-01-26
 *       Modified:  2016-01-29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zheng Yuhong , 371582812@qq.com
 *       HOMEPAGE:  zhengyh.com
 *
 * =====================================================================================
 */


#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <map>
#include <mutex>
#include <time.h>



// <=====================================================================================
class Logger {
public:
    enum LogLevel {
        debug = 1, //debug调试信息日志
        notice,    //正常状态信息日志
        warning,  //警告信息日志
        fatal,   //错误信息日志
        other   //其他信息，写入到标准错误输出
    };
private:
    std::mutex m_mtx; //支持多线程日志写入
    std::map<LogLevel, FILE*> m_fpmap;
    Logger();
    ~Logger();

    static Logger s_logger;

public:
    static FILE* set_fp_stream(LogLevel level = other, const std::string& path = "");
    static FILE* get_fp_stream(LogLevel level = other);
    static std::mutex& get_fp_mutex();

};//class Logger
// =====================================================================================>

#ifndef RELEASE

#define DEBUG_LOG(fmt, args...) \
    if (Logger::get_fp_stream(Logger::debug)) {\
        std::unique_lock<std::mutex> __lck__(Logger::get_fp_mutex());\
        time_t __timer__ = time(NULL);\
        struct tm* __tm__ = localtime(&__timer__);\
        fprintf(Logger::get_fp_stream(Logger::debug), "[%d-%d-%d %d:%d:%d %s:%d]", __tm__->tm_year + 1900, __tm__->tm_mon + 1, __tm__->tm_mday, __tm__->tm_hour, __tm__->tm_min, __tm__->tm_sec, __FILE__, __LINE__);\
        fprintf(Logger::get_fp_stream(Logger::debug), fmt, ##args);\
        fprintf(Logger::get_fp_stream(Logger::debug), "%c", '\n');\
}

#else

#define DEBUG_LOG(fmt, args...)

#endif


#define FATAL_LOG(fmt, args...) \
    if (Logger::get_fp_stream(Logger::fatal)) {\
        std::unique_lock<std::mutex> __lck__(Logger::get_fp_mutex());\
        time_t __timer__ = time(NULL);\
        struct tm* __tm__ = localtime(&__timer__);\
        fprintf(Logger::get_fp_stream(Logger::fatal), "[%d-%d-%d %d:%d:%d %s:%d]", __tm__->tm_year + 1900, __tm__->tm_mon + 1, __tm__->tm_mday, __tm__->tm_hour, __tm__->tm_min, __tm__->tm_sec, __FILE__, __LINE__);\
        fprintf(Logger::get_fp_stream(Logger::fatal), fmt, ##args);\
        fprintf(Logger::get_fp_stream(Logger::fatal), "%c", '\n');\
    }

#define WARNING_LOG(fmt, args...) \
    if (Logger::get_fp_stream(Logger::warning)) {\
        std::unique_lock<std::mutex> __lck__(Logger::get_fp_mutex());\
        time_t __timer__ = time(NULL);\
        struct tm* __tm__ = localtime(&__timer__);\
        fprintf(Logger::get_fp_stream(Logger::warning), "[%d-%d-%d %d:%d:%d %s:%d]", __tm__->tm_year + 1900, __tm__->tm_mon + 1, __tm__->tm_mday, __tm__->tm_hour, __tm__->tm_min, __tm__->tm_sec, __FILE__, __LINE__);\
        fprintf(Logger::get_fp_stream(Logger::warning), fmt, ##args);\
        fprintf(Logger::get_fp_stream(Logger::warning), "%c", '\n');\
    }

#define NOTICE_LOG(fmt, args...) \
    if (Logger::get_fp_stream(Logger::notice)) {\
        std::unique_lock<std::mutex> __lck__(Logger::get_fp_mutex());\
        time_t __timer__ = time(NULL);\
        struct tm* __tm__ = localtime(&__timer__);\
        fprintf(Logger::get_fp_stream(Logger::notice), "[%d-%d-%d %d:%d:%d %s:%d]", __tm__->tm_year + 1900, __tm__->tm_mon + 1, __tm__->tm_mday, __tm__->tm_hour, __tm__->tm_min, __tm__->tm_sec, __FILE__, __LINE__);\
        fprintf(Logger::get_fp_stream(Logger::notice), fmt, ##args);\
        fprintf(Logger::get_fp_stream(Logger::notice), "%c", '\n');\
    }

#define STDERR_LOG(fmt, args...) {\
        std::unique_lock<std::mutex> __lck__(Logger::get_fp_mutex());\
        time_t __timer__ = time(NULL);\
        struct tm* __tm__ = localtime(&__timer__);\
        fprintf(stderr, "[%d-%d-%d %d:%d:%d %s:%d]", __tm__->tm_year + 1900, __tm__->tm_mon + 1, __tm__->tm_mday, __tm__->tm_hour, __tm__->tm_min, __tm__->tm_sec, __FILE__, __LINE__);\
        fprintf(stderr, fmt, ##args);\
        fprintf(stderr, "%c", '\n');\
    }

#define STDOUT_LOG(fmt, args...) {\
        std::unique_lock<std::mutex> __lck__(Logger::get_fp_mutex());\
        time_t __timer__ = time(NULL);\
        struct tm* __tm__ = localtime(&__timer__);\
        fprintf(stdout, "[%d-%d-%d %d:%d:%d %s:%d]", __tm__->tm_year + 1900, __tm__->tm_mon + 1, __tm__->tm_mday, __tm__->tm_hour, __tm__->tm_min, __tm__->tm_sec, __FILE__, __LINE__);\
        fprintf(stdout, fmt, ##args);\
        fprintf(stdout, "%c", '\n');\
    }

#endif//LOG_H
