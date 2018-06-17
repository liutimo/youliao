//
// Created by liuzheng on 18-5-22.
//

#include "AudioModel.h"
#include "network/HttpClient.h"
#include "../DBPool.h"
AudioModel *AudioModel::m_instance = nullptr;

AudioModel::AudioModel()
{

}

AudioModel::~AudioModel()
{

}

AudioModel* AudioModel::instance()
{
    if (m_instance == nullptr)
        m_instance = new AudioModel();
    return m_instance;
}

void AudioModel::setUrl(const string &url)
{
    m_url = url;
    if (m_url[m_url.length()] != '/')
        m_url += "/";
}


int AudioModel::saveAudioInfo(uint32_t nFromId, uint32_t nToId, uint32_t nCreateTime,
                              const string& pAudioData, uint32_t duration)
{
    HttpClient httpClient;
    string fileName = httpClient.uploadByteFile(m_url, (void*)pAudioData.c_str(), pAudioData.length());

    int audioId = -1;

    if (fileName.empty())
        return audioId;

    fileName = "http://www.liutimo.cn/audio/" + fileName;

    DBConn *conn = DBManager::instance()->getConnection();
    if (conn)
    {
        string sql = "INSERT INTO yl_audio(from_id, to_id, path, duration, created) VALUES(?, ?, ?, ?, ?)";
        PrepareStatement *prepareStatement = new PrepareStatement();
        if (prepareStatement->init(conn->getMysql(), sql))
        {
            int index = 0;
            prepareStatement->setParam(index++, nFromId);
            prepareStatement->setParam(index++, nToId);
            prepareStatement->setParam(index++, fileName);
            prepareStatement->setParam(index++, duration);
            prepareStatement->setParam(index++, nCreateTime);

            if (prepareStatement->executeUpdate())
            {
                audioId = conn->getInsertId();
            }
        }
        delete prepareStatement;
    }

    DBManager::instance()->releaseConnection(conn);
    return audioId;
}



bool AudioModel::getAudioInfo(uint32_t audioId, uint32_t &duration, string& path)
{
    bool ret = false;
    DBConn *conn = DBManager::instance()->getConnection();

    if (!conn)
        return ret;

    std::string querySql = "SELECT * FROM yl_audio WHERE id = " + std::to_string(audioId);
    printSql2Log(querySql.c_str());

    ResultSet *resultSet = conn->query(querySql);


    if (resultSet)
    {
        if (resultSet->next())
        {
            duration = (uint32_t)resultSet->getInt("duration");
            path = resultSet->getString("path");
        }

        delete resultSet;
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}