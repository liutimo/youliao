//
// Created by liuzheng on 18-2-3.
//

#include "ConfigFileReader.h"

ConfigFileReader::ConfigFileReader(const std::string &filename) : m_config_file(std::move(filename))
{
    _LoadFile(m_config_file);
}

ConfigFileReader::~ConfigFileReader()
{

}

const std::string ConfigFileReader::getValue(const std::string &key) const
{
    if (!m_load_ok)
        return std::string();

    std::string value;
    auto iter = m_config_map.find(key);
    if (iter != m_config_map.end())
    {
        value = iter->second;
    }

    return value;
}


int ConfigFileReader::setConfigValue(const std::string &key, const std::string &value)
{
    if (!m_load_ok)
        return -1;

    auto iter = m_config_map.find(key);

    if (iter != m_config_map.end())
    {
        iter->second = value;
    }
    else
    {
        m_config_map.insert(std::make_pair(key, value));
    }

    return _WriteFile("");
}

void ConfigFileReader::_LoadFile(const std::string &filename)
{
    std::ifstream ifs;
    ifs.open(filename);

    if (!ifs.is_open())
    {
        //输出日志
        //打印控制台消息
        std::cout << "配置文件不存在" << std::endl;
        exit(-1);
    }

    std::string line;

    while (getline(ifs, line))
    {
        _ParseLine(line);
    }

    ifs.close();

    m_load_ok = true;
}

int ConfigFileReader::_WriteFile(const std::string &filename)
{
    std::ofstream ofs;
    ofs.open(filename);

    for (auto iter = m_config_map.begin(); iter != m_config_map.end(); ++iter)
    {
        std::string line = iter->first + "=" + iter->second + "\n";
        ofs << line;
    }

    ofs.close();
    return 0;
}

void ConfigFileReader::_ParseLine(std::string &line)
{
    u_long pos = line.find('=');

    if (pos == std::string::npos)
        return;

    std::string key(line.begin(), line.begin() + pos);
    std::string value(line.begin() + pos + 1, line.end());

    _TrimeSpace(key);
    _TrimeSpace(value);

    if (!(key.empty() || value.empty()))
    {
        m_config_map.insert(std::make_pair(key, value));
    }
}

//删除空格和制表符
const std::string& ConfigFileReader::_TrimeSpace(std::string &field)
{
    for (auto it = field.begin(); it != field.end();)
    {
        if (*it == ' ' || *it == '\t')
        {
            it = field.erase(it);
        }
        else
            ++it;
    }

    return field;
}