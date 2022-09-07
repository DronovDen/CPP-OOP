#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

#include "Exceptions.h"
#include "TupleHandle.h"

template <typename... Args>
class CSVParser
{

public:
    CSVParser(std::ifstream &csvFile, char colSep = ';', char rowSep = '\n', char shieldSymb = '\"')
        : csvFile(csvFile), columnSep(colSep), rowSep(rowSep), shieldSymb(shieldSymb)
    {
        if (!csvFile)
        {
            throw my_exception("Can't open .csv file!");
        }
        SetLinesNumber();
    }

    ~CSVParser()
    {
        csvFile.close();
    }

    class ParserIterator
    {
    private:
        CSVParser *parser;
        size_t idx;
        size_t endIdx;

    public:
        ParserIterator(int idx, int endIdx, CSVParser<Args...> *parser)
            : idx(idx), endIdx(endIdx), parser(parser) {}
        ParserIterator &operator++()
        {
            if (idx < endIdx)
            {
                idx++;
            }
            return *this;
        }
        bool operator==(const ParserIterator &other)
        {
            return this->parser == other.parser && this->idx == other.idx;
        }
        bool operator!=(const ParserIterator &other)
        {
            return !operator==(other);
        }
        std::tuple<Args...> operator*()
        {
            return parser->getTuple(parser->getRow(idx), idx);
        }
    };

    ParserIterator begin()
    {
        return ParserIterator(0, linesNumber, this);
    }
    ParserIterator end()
    {
        return ParserIterator(linesNumber, linesNumber, this);
    }

private:
    std::ifstream &csvFile;
    char shieldSymb;
    char columnSep;
    char rowSep;
    size_t linesNumber;

    void SetLinesNumber()
    {
        linesNumber = 0;
        std::string tmp;
        while (getline(csvFile, tmp))
        {
            linesNumber += 1;
        }
        tmp.clear();
        csvFile.clear();
        csvFile.seekg(0, std::ios::beg);
    }

    std::string getRow(size_t lineIdx)
    {
        std::string row;
        char symb;
        while (csvFile.get(symb) && symb != rowSep)
        {
            row += symb;
        }
        return row;
    }

    std::vector<std::string> splitRow(std::string line)
    {
        std::vector<std::string> fields;
        std::string fieldString;

        bool shield = false;
        for (auto &ch : line)
        {
            if (ch == shieldSymb && !shield)
            {
                shield = true;
                continue;
            }
            if (ch == shieldSymb && shield)
            {
                shield = false;
                continue;
            }
            if (ch == columnSep && !shield)
            {
                fields.push_back(fieldString);
                fieldString.clear();
            }
            else
            {
                fieldString += ch;
            }
        }

        if (!fieldString.empty())
        {
            fields.push_back(fieldString);
        }

        return fields;
    }

    const std::tuple<Args...> getTuple(std::string line, int lineIdx)
    {
        if (line.empty())
        {
            throw my_exception(
                "Row " + std::to_string(lineIdx + 1) + ": "
                                                       "Empty");
        }

        auto fields = splitRow(line);
        auto fieldsNumber = sizeof...(Args); //sizeof...(Args) mean args number (5)

        if (fields.size() != fieldsNumber)
        {
            throw my_exception(
                "Row " + std::to_string(lineIdx + 1) + ": "
                                                       "Wrong fields number (unexpected field separator)");
        }

        std::tuple<Args...> parsedFields;
        try
        {
            parsedFields = toTuple<Args...>(fields);
        }
        catch (my_exception &e)
        {
            throw my_exception(
                "Row " + std::to_string(lineIdx + 1) + ": " +
                e.what());
        }

        return parsedFields;
    }
};