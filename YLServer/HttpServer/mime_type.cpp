//
// Created by liuzheng on 18-4-15.
//

#include "mime_type.h"

namespace http
{
    namespace server
    {
        namespace mime_types
        {
            struct mapping
            {
                const char* extension;
                const char* mime_type;
            }mappings[] = {
                    {"gif", "image/gif" },
                    {"htm", "text/html"},
                    {"html", "text/html"},
                    {"jpg", "image/hpeg"},
                    {"png", "image/png"}
            };

            std::string extension_to_type (const std::string &extension)
            {
                for (mapping m : mappings)
                {
                    if(m.extension == extension)
                        return m.mime_type;
                }

                return "text/plain";
            }
        }
    }
}
