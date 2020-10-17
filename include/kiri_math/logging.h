#ifndef _KIRI_MATH_LOGGING_H_
#define _KIRI_MATH_LOGGING_H_

#include <iostream>
#include <sstream>
#include <string>

//#define KIRI_LOGGING

namespace kiri_math
{

    //! Level of the logging.
    //! All < Debug < Info < Warn < Error < Off.
    enum class LoggingLevel : uint8_t
    {
        All = 0,
        Debug = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        Off = 5
    };

    //!
    //! \brief Super simple logger implementation.
    //!
    //! This is a super simple logger implementation that has minimal logging
    //! capability. Currently, the class doesn't support multi-thread logging.
    //!
    class Logger final
    {
    public:
        //! Constructs a logger with logging level.
        explicit Logger(LoggingLevel level);

        //! Destructor.
        ~Logger();

        //! Writes a value to the buffer stream.
        template <typename T>
        const Logger &operator<<(const T &x) const
        {
            _buffer << x;
            return *this;
        }

    private:
        LoggingLevel _level;
        mutable std::stringstream _buffer;
    };

    //! Helper class for logging.
    class Logging
    {
    public:
        //! Sets the output stream for the info level logs.
        static void setInfoStream(std::ostream *strm);

        //! Sets the output stream for the warning level logs.
        static void setWarnStream(std::ostream *strm);

        //! Sets the output stream for the error level logs.
        static void setErrorStream(std::ostream *strm);

        //! Sets the output stream for the debug level logs.
        static void setDebugStream(std::ostream *strm);

        //! Sets the output stream for all the log levelss.
        static void setAllStream(std::ostream *strm);

        //! Returns the header string.
        static std::string getHeader(LoggingLevel level);

        //! Sets the logging level.
        static void setLevel(LoggingLevel level);

        //! Mutes the logger.
        static void mute();

        //! Un-mutes the logger.
        static void unmute();
    };

    //! Info-level logger.
    extern Logger infoLogger;

    //! Warn-level logger.
    extern Logger warnLogger;

    //! Error-level logger.
    extern Logger errorLogger;

    //! Debug-level logger.
    extern Logger debugLogger;

#define KIRI_INFO                                                         \
    (Logger(LoggingLevel::Info) << Logging::getHeader(LoggingLevel::Info) \
                                << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
#define KIRI_WARN                                                         \
    (Logger(LoggingLevel::Warn) << Logging::getHeader(LoggingLevel::Warn) \
                                << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
#define KIRI_ERROR                                                          \
    (Logger(LoggingLevel::Error) << Logging::getHeader(LoggingLevel::Error) \
                                 << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")
#define KIRI_DEBUG                                                          \
    (Logger(LoggingLevel::Debug) << Logging::getHeader(LoggingLevel::Debug) \
                                 << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] ")

} // namespace kiri_math

#endif // _KIRI_MATH_LOGGING_H_
