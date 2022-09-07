#include "Dump.h"

//constructor of example of DumpBlock
static BlockMaker<Dump> DumpBlockMaker("dump");

void Dump::work(std::vector<std::string> params, std::string &text)
{
    if (params.empty())
    {
        throw std::runtime_error("Too few arguments for writing into output file");
    }

    //params[0] = FileName

    std::ofstream output_file;
    output_file.open(params[0]);

    if (!output_file.is_open())
    {
        throw std::runtime_error("Can't open output file");
    }

    if (text.empty())
    {
        throw std::runtime_error("Nothing to write!");
    }
    output_file << text;
    output_file.close();
}