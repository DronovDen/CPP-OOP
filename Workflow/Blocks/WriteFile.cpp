#include "WriteFile.h"

static BlockMaker<WriteFile> WriteFileMaker("writefile");

//add link!
void WriteFile::work(std::vector<std::string> params, std::string &text)
{
    if (params.empty())
    {
        throw std::runtime_error("Too few arguments for writing into output file");
    }
    //params[0] = file name
    std::ofstream output_file;
    output_file.open(params[0]);

    if (!output_file.is_open())
    {
        throw std::runtime_error("Can't open output file");
    }

    output_file << text;
    output_file.close();
};
