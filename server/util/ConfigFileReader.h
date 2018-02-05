//
// Created by liuzheng on 18-2-3.
//

#ifndef UTIL_CONFIGFILEREADER_H
#define UTIL_CONFIGFILEREADER_H

#include "common.h"

class ConfigFileReader {
public:
    explicit ConfigFileReader(const std::string& filename);
    ~ConfigFileReader();

    const std::string getValue(const std::string &key) const;
    int setConfigValue(const std::string& key, const std::string &value);

private:
    void _LoadFile(const std::string& filename);
    int _WriteFile(const std::string& filename);
    void _ParseLine(std::string& line);
    const std::string& _TrimeSpace(std::string& field);

    bool m_load_ok;
    std::map<std::string, std::string> m_config_map;
    std::string m_config_file;


};


#endif //UTIL_CONFIGFILEREADER_H
