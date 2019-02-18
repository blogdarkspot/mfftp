#include <algorithm>
#include <string>
#include <vector>

namespace utils {

using namespace std;

//std = C++17
#if __cplusplus >= 201703L
using namespace std::literals::string_view_literals;

vector<string> split(string_view strv, string_view delim = " ")
{
    std::vector<string> output;
    size_t first = 0;
    while (first < strv.size()) {
        const auto second = strv.find_first_of(delim, first);
        if (first != second) {
            output.emplace_back(strv.substr(first, second - first));
        }

        if (second == string_view::npos) {
            break;
        }

        first = second + 1;
    }

    return output;
}

#else
vector<string> split(const string& str, const string& delims = " ")
{
    vector<string> output;
    auto first = cbegin(str);
    while (first != cend(str)) {
        const auto second = std::find_first_of(first, std::cend(str), std::cbegin(delims), std::cend(delims));
        if(first != second) {
            output.emplace_back(first, second);
        }
        if(second == std::cend(str)) {
            break;
        }
        first = std::next(second);
    }
    return output;
}

#endif
}