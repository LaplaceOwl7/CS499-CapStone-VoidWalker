#ifndef ERRLOG_ERR_HPP
#define ERRLOG_ERR_HPP

#include <iostream>
#include <fstream>

class ErrLog {

    public:
    /**
     * @brief Appends error codes on a log file to be stored in logs
     * @param t_message, the message to paste after the date.
     * @return nothing
     * @pre The log file must be created
     * @post Do not specify newlines
     */
        void genLogFile(const std::string& t_message);

    private:
        // Helper function generates timestamp
        std::string genTimeStamp();

};

#endif // ERRLOG_ERR_HPP