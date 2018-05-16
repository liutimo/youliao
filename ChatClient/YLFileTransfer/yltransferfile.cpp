#include "yltransferfile.h"

class YLTransferFile::YLFilePrivate
{
public:
    YLFilePrivate(const string& path, bool bsave);
    ~YLFilePrivate();

public:
    FILE	*file;
    bool	readOnly;
    uint32_t	size;
};

YLTransferFile::YLFilePrivate::~YLFilePrivate()
{
    if (file)
        fclose(file);
}

YLTransferFile::YLFilePrivate::YLFilePrivate(const string& path, bool bsave)
:file(nullptr)
,size(0)
,readOnly(true)
{
    if (!path.empty())
    {
        if (bsave)
        {
            file = fopen(path.c_str(), "wb+");
            if (file)
                readOnly = false;
            else
            {
                file = fopen(path.c_str(), "wb");
            }
        }
        else
        {
            file = fopen(path.c_str(), "rb+");
            if (file)
            {
                readOnly = false;
            }
            else
            {
                file = fopen(path.c_str(), "rb");
            }
        }
    }
}


YLTransferFile::YLTransferFile(const string &path, bool bsave) :m_file(nullptr)
{
    m_file = new YLFilePrivate(path, bsave);
}


YLTransferFile::~YLTransferFile()
{
    delete m_file;
    m_file = nullptr;
}

bool YLTransferFile::writeBlock(uint32_t offset, uint32_t size, const char* data)
{
    if (!m_file->file)
        return false;

    if (m_file->readOnly)
    {
        return false;
    }

    seek(offset, Beginning);
    int count = fwrite(data, sizeof(char), size, m_file->file);
    if (count < 1)
        return false;

    return true;
}

bool YLTransferFile::readBlock(uint32_t offset, uint32_t size, std::string& data)
{
    if (!m_file || !m_file->file)
    {
        return false;
    }
    seek(offset, Beginning);
    data.resize(size);
    int count = fread((void*)data.data(), sizeof(char), size,m_file->file);
    if (count < 1)
    {
        return false;
    }

    return true;
}

void YLTransferFile::seek(long offset, Position p /*= Beginning*/)
{
    if (!m_file->file)
    {
        return;
    }

    switch (p)
    {
    case Beginning:
        fseek(m_file->file, offset, SEEK_SET);
        break;
    case Current:
        fseek(m_file->file, offset, SEEK_CUR);
        break;
    case End:
        fseek(m_file->file, offset, SEEK_END);
        break;
    }
}

uint32_t YLTransferFile::tell() const
{
    return ftell(m_file->file);
}

uint32_t YLTransferFile::length()
{
    if (m_file->size > 0)
        return m_file->size;

    if (!m_file->file)
        return 0;

    long curpos = tell();
    seek(0, End);
    long endpos = tell();

    seek(curpos, Beginning);

    m_file->size = endpos;
    return endpos;
}
