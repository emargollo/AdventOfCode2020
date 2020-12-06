#include "Reader.h"

std::vector<std::string> read_input(std::istream& ifs)
{
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<line>(ifs),
        std::istream_iterator<line>(),
        std::back_inserter(lines));
    return lines;
}

std::vector<int> read_ints(std::istream& ifs)
{
    std::vector<int> lines;
    std::transform(std::istream_iterator<line>(ifs),
        std::istream_iterator<line>(),
        std::back_inserter(lines), [&](const line& l) {return std::stoi(l); });
    return lines;
}
