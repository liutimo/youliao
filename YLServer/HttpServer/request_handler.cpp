//
// Created by liuzheng on 18-4-15.
//

#include "request_handler.h"
#include <fstream>
#include <iostream>
#include "reply.h"
#include "request.h"

namespace http
{
    namespace server
    {

        const char*  memfind(const char *src_str,size_t src_len, const char *sub_str, size_t sub_len, bool flag)
        {
            if(NULL == src_str || NULL == sub_str || src_len <= 0)
            {
                return NULL;
            }
            if(src_len < sub_len)
            {
                return NULL;
            }
            const char *p;
            if (sub_len == 0)
                sub_len = strlen(sub_str);
            if(src_len == sub_len)
            {
                if(0 == (memcmp(src_str, sub_str, src_len)))
                {
                    return src_str;
                }
                else
                {
                    return NULL;
                }
            }
            if(flag)
            {
                for (int i = 0; i < src_len - sub_len; i++) {
                    p = src_str + i;
                    if (0 == memcmp(p, sub_str, sub_len)) {
                        return p;
                    }
                }
            }
            else
            {
                for ( int i = (src_len - sub_len) ; i >= 0;i--  )
                {
                    p = src_str + i;
                    if ( 0 == memcmp(  p,sub_str,sub_len ) )
                        return p;

                }
            }
            return NULL;
        }

        request_handler::request_handler(const std::string &doc_root)
        {
            doc_root_ = doc_root;
        }

        void request_handler::handle_request(const request &req, reply &rep, asio::ip::tcp::socket &sock)
        {
            std::string request_path;
            if (!url_decode(req.uri, request_path))
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            if (request_path.empty() || request_path[0] != '/' || request_path.find("..") != std::string::npos)
            {
                rep = reply::stock_reply(reply::bad_request);
                return;
            }

            if (request_path[request_path.size() - 1] == '/')
            {
                request_path += "index.html";
            }

            std::size_t last_slash_pos = request_path.find_last_of("/");
            std::size_t last_dot_pos = request_path.find_last_of(".");
            std::string extension;

            if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
            {
                extension = request_path.substr(last_dot_pos + 1);
            }

            if (req.method == "GET")
            {

                //打开文件并且发送
                std::string full_path = doc_root_ + request_path;
                std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);

                if (!is) {
                    rep = reply::stock_reply(reply::not_found);
                    return;
                }


                char buf[512];
                while (is.read(buf, sizeof(buf)).gcount() > 0)
                    rep.content.append(buf, is.gcount());

                rep.stock_reply(reply::ok);
            }
            else
            {
                if (req.method == "POST")
                {
                    ssize_t  size = atoi(req.headers[2].value.c_str());
                    char *data = new char[size];

                    sock.read_some(asio::buffer(data, size));

                    int len  = 0;
                    auto pPos = memfind(data, size, CONTENT_DISPOSITION, strlen(CONTENT_DISPOSITION));

                    if (pPos != nullptr)
                    {
                        len = pPos - data;
                        auto pPos2 = memfind(pPos, size - len, "filename=", strlen("filename="));
                        if (pPos2 != nullptr)
                        {
                            pPos = pPos2 + strlen("filename=") + 1;

                            len = pPos - data;
                            auto pPosEnd = memfind(pPos, size - len, "\"", strlen("\""));

                            if(!pPosEnd)
                                return;

                            int fileNameLen = pPosEnd - pPos;
                            char szFileName[256];

                            if (fileNameLen <= 255)
                            {
                                memcpy(szFileName, pPos, fileNameLen);
                                szFileName[fileNameLen] = '\0';

                                len = pPos2 - data;
                                auto pPosHttpEnd = memfind(pPos2, size - len, HTTP_END_MARK, strlen(HTTP_END_MARK));
                                if(!pPosHttpEnd)
                                    return;
                                auto pPosFileStart = pPosHttpEnd + strlen(HTTP_END_MARK);

                                len = pPosFileStart - data;

                                char boundary[] = "youliao_youliao";
                                len = pPosFileStart - data;
                                auto pPosFileEnd = memfind(pPosFileStart, size - len, boundary, strlen(boundary), false);

                                if (pPosFileEnd == nullptr) {
                                    std::cout << "文件上传失败" << std::endl;
                                    rep.stock_reply(reply::bad_request);
                                    return;
                                }

                                std::cout << strlen(HTTP_END_MARK) << std::endl;

                                int fileSize = pPosFileEnd - pPosFileStart - strlen(HTTP_END_MARK);

                                int flags = O_RDWR | O_CREAT | O_EXCL;

                                std::string filePath = doc_root_ + "/" + szFileName;

                                int fd = open64(filePath.c_str(), flags, 00640);

                                pwrite(fd, pPosFileStart, fileSize, 0);
                                fsync(fd);
                                close(fd);
                                rep.stock_reply(reply::ok);

                                std::cout << "文件上传成功" << std::endl;
                                return;
                            }
                        }
                    }


                }
            }
        }

        bool request_handler::url_decode(const std::string &in, std::string &out)
        {
            out.clear();
            out.reserve(in.size());

            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] == '%')
                {
                    if (i + 3 <= in.size())
                    {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value)
                        {
                            out += static_cast<char>(value);
                            i += 2;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (in[i] == '+')
                {
                    out += ' ';
                }
                else
                {
                    out += in[i];
                }
            }
            return true;
        }
    }
}