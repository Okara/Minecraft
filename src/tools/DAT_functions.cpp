#include "DAT_header.hpp"

C_DAT::C_DAT (void)
{
    m_buffer = NULL;
}

C_DAT::~C_DAT (void)
{
    if (m_buffer!=NULL)
        delete (m_buffer);
}

bool C_DAT::Create (std::vector<std::string> files, std::string destination)
{
    sFileEntry entry;
    std::ifstream file;
    std::ofstream datfile;
    char buffer[1];

    memset (&m_header, 0, sizeof(m_header));
    memcpy (m_header.uniqueID, "JGDAT", 5);
    memcpy (m_header.version, "0.1", 3);
    m_header.nb_files = files.size();

    for (unsigned int i = 0; i<files.size(); i++)
    {
        file.open (files[i].c_str(), std::ifstream::in | std::ifstream::binary);
        if (file.is_open())
        {
            memset (&entry, 0, sizeof(sFileEntry) );
            memcpy (entry.name, files[i].c_str(), strlen ( files[i].c_str() ) );
            file.seekg (0, std::ios::end);
            entry.size = file.tellg();
            entry.offset = 0;
            file.close();

            m_entries.push_back(entry);
        }
        else
        {
            std::cout<<"File "<<files[i]<<" raise an error."<<std::endl;
            return (false);
        }
    }

    long actual_offset = 0;
    actual_offset += sizeof(sDATHeader);
    actual_offset += m_header.nb_files * sizeof(sFileEntry);
    for (unsigned int i=0;i<m_entries.size();i++)
    {
        m_entries[i].offset = actual_offset;
        actual_offset += m_entries[i].size;
    }

    datfile.open (destination.c_str(), std::ofstream::out | std::ofstream::binary);
    datfile.write ((char*)&m_header, sizeof(sDATHeader) );

    for (unsigned int i=0;i<m_entries.size();i++)
    {
        datfile.write ((char*)&m_entries[i], sizeof(sFileEntry) );
    }

    for (unsigned int i = 0; i<m_entries.size(); i++)
    {
        file.open (m_entries[i].name, std::ifstream::in | std::ifstream::binary);
        if (file.is_open())
        {
            file.seekg (0, std::ios::beg);
            while (file.read (buffer, 1))
            {
                datfile.write (buffer, 1);
            }
            file.close();
        }
        file.clear();
    }

    datfile.close();
    return (true);
}

void C_DAT::Read (std::string source)
{
    std::ifstream datfile;
    sFileEntry entry;

    memset (&m_header, 0, sizeof(m_header));
    datfile.open (source.c_str(), std::ifstream::in | std::ifstream::binary);
    if (datfile.is_open())
    {
        datfile.seekg (0, std::ios::beg);
        datfile.read ((char*)&m_header, sizeof(sDATHeader));
        for (unsigned int i=0;i<m_header.nb_files;i++)
        {
            datfile.read ((char*)&entry, sizeof(sFileEntry));
            m_entries.push_back(entry);
        }
        m_datfile = source;
    }
    datfile.close();
}

char* C_DAT::GetFile (std::string filename)
{
    std::ifstream datfile;

    if (m_buffer != NULL)
    {
        delete (m_buffer);
        m_buffer = NULL;
    }

    for (unsigned int i=0; i<m_header.nb_files;i++)
    {
        if (m_entries[i].name == filename)
        {
            m_buffer = new char[(m_entries[i].size)];
            if (m_buffer==NULL)
                return (NULL);
            datfile.open (m_datfile.c_str(), std::ifstream::in | std::ifstream::binary);
            if (datfile.is_open())
            {
                datfile.seekg (m_entries[i].offset, std::ios::beg);
                datfile.read (m_buffer, m_entries[i].size);
                datfile.close();
                return (m_buffer);
            }
        }
    }
    return (NULL);
}

long int C_DAT::GetFileSize (std::string filename)
{
    for (unsigned int i=0; i<m_header.nb_files;i++)
    {
        if (m_entries[i].name == filename)
        {
            return (m_entries[i].size);
        }
    }
    return (0);
}
