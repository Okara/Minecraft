#ifndef DAT_HEADER_HPP_INCLUDED
#define DAT_HEADER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

struct sDATHeader
{
    char uniqueID[5];
    char version[3];
    unsigned int nb_files;
};

struct sFileEntry
{
    char name[300];
    long size;
    long offset;
};

class C_DAT
{
    private :
        std::string m_datfile;
        sDATHeader m_header;
        std::vector<sFileEntry> m_entries;
        char* m_buffer;
    public :
        C_DAT (void);
        ~C_DAT (void);
        bool Create (std::vector<std::string> files, std::string destination);
        void Read (std::string source);
        char* GetFile (std::string filename);
        long int GetFileSize (std::string filename);
};

#endif // DAT_HEADER_HPP_INCLUDED
