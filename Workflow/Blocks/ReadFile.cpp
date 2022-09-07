#include "ReadFile.h"

static BlockMaker<ReadFile> ReadFileMaker("readfile");

void ReadFile::work(std::vector<std::string> params, std::string &text)
{
    if (params.empty())
    {
        throw std::runtime_error("Too few arguments for reading input file");
    }
    //params[0] = FileName
    std::ifstream input_file;
    input_file.open(params[0]);

    if (!input_file.is_open())
    {
        throw std::runtime_error("Can't open input file");
    }

    std::string ret_string = "";
    std::string data;

    while (getline(input_file, data))
    {
        ret_string += data + "\n";
    }
    input_file.close();
    text = ret_string;
};
