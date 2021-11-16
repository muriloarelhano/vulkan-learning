#pragma once

#include <string>
#include <vector>
#include <fstream>
using namespace std;

namespace Heaven
{
    class Pipeline
    {
    public:
        Pipeline(const string& vertFilepath, const string& fragFilepath);
        ~Pipeline();

    private:
        static vector<char> ReadFile(const string& filepath);
        void CreateGraphicsPipeline(const string& vertFilePath, const string& fragFilePath);
    };
}