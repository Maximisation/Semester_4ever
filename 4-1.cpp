#include <regex>
#include <iostream>

std::vector<std::string> search(const std::regex& pattern,
                                const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
                                      std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    auto it = std::remove_if(std::begin(results), std::end(results), [](auto item) {
        return item.empty();
    });
    results.erase(it, std::end(results));
    return results;
}

int main() {
    std::regex pattern(R"(\d{1,}[.](0[1-9]|1[0-2])[.](0[1-9]|[12][0-9]|3[01]))");

    std::string text = "sforgje arig earg +7900000-00-00 dfmpa +734241"
                       " +80000000000 2341241241wfm fgerg wfwertrt"
                       "+7 000000000 +73000000000 +75000000000"
                       "12:10:45 6:30:45 29.12.20 29.12.24 29.10.09";
    auto search_result = search(pattern, text);
    for(const auto& item: search_result) {
        std::cout << item << ' ';
    }
}