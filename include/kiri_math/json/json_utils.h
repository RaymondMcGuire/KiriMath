#ifndef _KIRI_MATH_JSON_UTILS_H_
#define _KIRI_MATH_JSON_UTILS_H_

#include <fstream>
#include <kiri_math/pch.h>

#include <json/json.hpp>

#ifdef KIRI_MATH_WINDOWS
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace kiri_math;
using json = nlohmann::json;

void saveDataAsJSON(const json &jsonData, const std::string &rootDir, const std::string &name = "data.json")
{
    std::string filename = "./" + rootDir + "/" + name;
    std::ofstream file(filename.c_str());
    if (file)
    {
        KIRI_INFO << filename;
        file << jsonData.dump() << std::endl;
        file.close();
    }
}

json readJsonFromFile(const std::string &name = "data.json")
{
    std::ifstream i(name);
    json j;
    i >> j;

    return j;
}

void makeFolder(std::string outputDir)
{
    bool b_mkdir = false;
#ifdef KIRI_MATH_WINDOWS
    b_mkdir = _mkdir(outputDir.c_str());
#else
    b_mkdir = mkdir(outputDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
#endif

    if (b_mkdir)
    {
        KIRI_INFO << "Create Folder:" << outputDir;
    }
}

#endif