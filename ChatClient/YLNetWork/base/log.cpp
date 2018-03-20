//
// Created by liuzheng on 18-2-7.
//

#include "log.h"
#include <stdarg.h>
#include <iostream>
using namespace log4cxx;
using namespace youliao::log;

#define MAX_LOG_LENGTH  1024 * 10

LogObjectImpl::LogObjectImpl(const std::string &module_name)
{
    PropertyConfigurator::configure("log4cxx.properties");
    m_logger = Logger::getLogger(module_name);
}

LogObjectImpl::~LogObjectImpl()
{

}


void LogObjectImpl::Trace(const std::string& msg)
{
    m_logger->trace(msg);
}

void LogObjectImpl::Debug(const std::string& msg)
{
    m_logger->debug(msg);
}

void LogObjectImpl::Info(const std::string& msg)
{
    m_logger->info(msg);
}

void LogObjectImpl::Warn(const std::string& msg)
{
    m_logger->warn(msg);
}

void LogObjectImpl::Error(const std::string& msg)
{
    m_logger->error(msg);
}

void LogObjectImpl::Fatal(const std::string& msg)
{
    m_logger->fatal(msg);
}


Log::Log(const std::string &module_name)
{
    std::cout << "初始化" << module_name << std::endl;
    m_log_object = new LogObjectImpl(module_name);
}

Log::~Log()
{
    delete m_log_object;
}

void Log::Trace(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char szBuffer[MAX_LOG_LENGTH];
    vsnprintf(szBuffer, sizeof(szBuffer), format, args);
    va_end(args);

    m_log_object->Trace(szBuffer);
}

void Log::Debug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char szBuffer[MAX_LOG_LENGTH];
    vsnprintf(szBuffer, sizeof(szBuffer), format, args);
    va_end(args);

    m_log_object->Debug(szBuffer);
}

void Log::Info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char szBuffer[MAX_LOG_LENGTH];
    vsnprintf(szBuffer, sizeof(szBuffer), format, args);
    va_end(args);

    m_log_object->Info(szBuffer);
}

void Log::Warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char szBuffer[MAX_LOG_LENGTH];
    vsnprintf(szBuffer, sizeof(szBuffer), format, args);
    va_end(args);

    m_log_object->Warn(szBuffer);
}

void Log::Error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char szBuffer[MAX_LOG_LENGTH];
    vsnprintf(szBuffer, sizeof(szBuffer), format, args);
    va_end(args);

    m_log_object->Error(szBuffer);
}

void Log::Fatal(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char szBuffer[MAX_LOG_LENGTH];
    vsnprintf(szBuffer, sizeof(szBuffer), format, args);
    va_end(args);

    m_log_object->Fatal(szBuffer);
}
