#ifndef YLYLTransferFile_H
#define YLYLTransferFile_H

#include <string>
#include <cstdio>

using namespace std;

enum Position
{
    Beginning,
    Current,
    End
};


class YLTransferFile final
{
public:
    YLTransferFile(const string &path, bool bsave);
    ~YLTransferFile();

    bool readBlock(uint32_t offset, uint32_t size, std::string& data);
    bool writeBlock(uint32_t offset,uint32_t size, const char* data);
    uint32_t length();

private:
    uint32_t tell() const;
    void seek(long offset, Position p = Beginning);

private:
    class YLFilePrivate;
    YLFilePrivate*				m_file;
};

#endif // YLYLTransferFile_H
