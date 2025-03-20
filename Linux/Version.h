#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

struct OSVersion
{
    char name[16];
    unsigned int major;
    unsigned int minor;
    unsigned int build;
};

// 解析 /etc/os-release 文件
static std::unordered_map<std::string, std::string> ParseOSRelease()
{
    std::unordered_map<std::string, std::string> os_info;
    std::ifstream file("/etc/os-release");

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open /etc/os-release");
    }

    std::string line;
    while (std::getline(file, line))
    {
        // 跳过空行和注释
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        // 解析键值对
        size_t delimiter_pos = line.find('=');
        if (delimiter_pos == std::string::npos)
        {
            continue; // 忽略无效行
        }

        std::string key = line.substr(0, delimiter_pos);
        std::string value = line.substr(delimiter_pos + 1);

        // 去除值中的引号
        if (!value.empty() && value.front() == '"' && value.back() == '"')
        {
            value = value.substr(1, value.size() - 2);
        }

        os_info[key] = value;
    }

    return os_info;
}

static void ParseVersionString(const std::string &version, unsigned int *major, unsigned int *minor)
{
    size_t dot_pos = version.find('.');
    if (dot_pos == std::string::npos)
    {
        throw std::invalid_argument("Invalid version string: missing '.'");
    }

    *major = std::stoi(version.substr(0, dot_pos));
    *minor = std::stoi(version.substr(dot_pos + 1));
}

static OSVersion GetOSVersion()
{
    OSVersion res;
    auto os_info = ParseOSRelease();

    // 从解析结果中提取所需字段
    strncpy(res.name, os_info["NAME"].c_str(), 16);
    ParseVersionString(os_info["VERSION_ID"], &res.major, &res.minor);
    res.build = 0;
    return res;
}
