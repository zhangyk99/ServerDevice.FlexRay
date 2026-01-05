//
// Created by 79933 on 2025/12/3.
//

#ifndef MTESTSERVER_DEVICE_FLEXRAY_FLEXRAYTOOLS_H
#define MTESTSERVER_DEVICE_FLEXRAY_FLEXRAYTOOLS_H

#include <string>
#include <algorithm>
#include <vector>

#ifdef _WIN32
#include <direct.h> // For _getcwd
#include <windows.h> // For MAX_PATH
#else
#include <unistd.h> // For getcwd
#include <limits.h> // For PATH_MAX
#endif

namespace FlexRay{
// 统一路径分隔符为正斜杠（/）
    inline std::string NormalizePath(const std::string &path) {
        std::string normalizedPath = path;
        std::replace(normalizedPath.begin(), normalizedPath.end(), '\\', '/');
        return normalizedPath;
    }


// 分拆路径为基路径和最后一个名称
    inline std::pair<std::string, std::string> SplitPath(const std::string &path) {
        std::string normalizedPath = NormalizePath(path);
        size_t lastSlashPos = normalizedPath.find_last_of('/');
        if (lastSlashPos == std::string::npos) {
            return {"", normalizedPath}; // 没有斜杠,返回空基路径和完整路径
        }
        return {normalizedPath.substr(0, lastSlashPos), normalizedPath.substr(lastSlashPos + 1)};
    }

    //string parse
    inline std::vector<std::string> splitString(const std::string &str, const std::string &delimiter) {
        std::vector<std::string> result{};
        size_t start = 0, end;
        while ((end = str.find(delimiter, start)) != std::string::npos) {
            result.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        result.push_back(str.substr(start));
        return result;
    }
}

#endif //MTESTSERVER_DEVICE_FLEXRAY_FLEXRAYTOOLS_H
