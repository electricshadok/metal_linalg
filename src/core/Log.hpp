#ifndef Log_hpp
#define Log_hpp

#include <iostream>
#include <sstream>

class Log {
public:
    enum class Level {
        INFO,
        ERROR,
    };

    class Logger {
    public:
        Logger(Level level) : level(level) {}

        ~Logger() {
            // Output the final log message upon object destruction
            std::ostream& stream = (level == Level::ERROR) ? std::cerr : std::cout;
            stream << ss.str() << std::endl;
        }

        template<typename T>
        Logger& operator<<(const T& value) {
            ss << value;
            return *this;
        }

        // Special handling for manipulators like std::endl
        Logger& operator<<(std::ostream& (*pf)(std::ostream&)) {
            ss << pf;
            return *this;
        }

        // Placeholder to trigger log message processing
        static void end() {}

    private:
        std::stringstream ss;
        Level level;
    };

    static Logger info() {
        return Logger(Level::INFO);
    }

    static Logger error() {
        return Logger(Level::ERROR);
    }
};




#endif /* Log_hpp */
