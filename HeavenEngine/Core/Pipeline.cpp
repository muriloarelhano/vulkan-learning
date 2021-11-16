#include "Pipeline.h"
#include "Pipeline.h"

//std
#include <iostream>
#include <stdexcept>

namespace Heaven
{
    Pipeline::Pipeline(const string& vertFilepath, const string& fragFilepath) 
    {
        CreateGraphicsPipeline(vertFilepath, fragFilepath);
    }

    Pipeline::~Pipeline()
    {
    }

    vector<char> Pipeline::ReadFile(const string &filepath)
    {
        ifstream file(filepath);
        if (!file.is_open())
        {
            throw runtime_error("Failed to open file: " + filepath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }
    
    void Pipeline::CreateGraphicsPipeline(const string& vertFilePath, const string& fragFilePath) 
    {
        auto vertCode = ReadFile(vertFilePath);
        auto fragCode = ReadFile(fragFilePath);

        cout << "Vertex shader code: " << endl << vertCode.size()<< endl;
        cout << "Fragment shader code: " << endl << fragCode.size() << endl;

    }
}