#ifndef MARGINAL_LOG_HPP_INCLUDED
#define MARGINAL_LOG_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <ctime>

class C_Log
{
    public:
        static C_Log *GetSingleton()
        {
            if (_singleton == NULL)
            {
                _singleton =  new C_Log;

                _singleton->AddMessage("Creating singleton Log.");
            }

            return _singleton;
        }

        static void kill()
        {
            if (_singleton != NULL)
            {
                _singleton->AddMessage("Singleton Log killed.");
                delete _singleton;
                _singleton = NULL;
            }
        }

        void AddMessage(std::string str)
        {
            std::ofstream _file;
            _file.open("logs.log", std::ios_base::app);

            time_t rawtime;
            time ( &rawtime );
            std::string _time = ctime (&rawtime);
            _time = _time.substr(11,8);

            _file << "[" << _time << "] " << str << "\n";

            _file.close();
        }

    private:
        C_Log()
        {
            std::ofstream _file;
            _file.open("logs.log");
            _file.close();
        }

        ~C_Log()
        {
        }

        static C_Log *_singleton;
};

#endif // MARGINAL_LOG_HPP_INCLUDED
