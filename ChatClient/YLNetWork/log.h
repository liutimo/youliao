//
// Created by liuzheng on 18-2-7.
//

#ifndef LOG4CXXTEST_LOG_API_H
#define LOG4CXXTEST_LOG_API_H

#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
namespace youliao{
    namespace log
    {
        class LoggerPtr;
        class LogObject
        {
        public:
            LogObject(){}
            virtual ~LogObject(){}

            virtual void Trace(const std::string&) = 0;
            virtual void Debug(const std::string&) = 0;
            virtual void Info(const std::string&) = 0;
            virtual void Warn(const std::string&) = 0;
            virtual void Error(const std::string&) = 0;
            virtual void Fatal(const std::string&) = 0;
        };


        class LogObjectImpl : public LogObject
        {
        public:
            LogObjectImpl(const std::string &);
            virtual ~LogObjectImpl();

            void Trace(const std::string&) override ;
            void Debug(const std::string&) override ;
            void Info(const std::string&) override ;
            void Warn(const std::string&) override ;
            void Error(const std::string&) override ;
            void Fatal(const std::string&) override ;

        private:
            log4cxx::LoggerPtr m_logger;
        };

        class Log
        {
        public:
            Log(const std::string&);
            ~Log();

        public:
            /*C style*/
            void Trace(const char*, ...);
            void Debug(const char*, ...);
            void Info(const char*, ...);
            void Warn(const char*, ...);
            void Error(const char*, ...);
            void Fatal(const char*, ...);

        private:
            LogObject *m_log_object;
        };
    }

}



#endif //LOG4CXXTEST_LOG_API_H
