#pragma once

#include <string>
#include <vector>

struct SearchResult {
    std::string url;
    int relevance;
};

class SearchServer {
public:
    explicit SearchServer(const std::string& configPath);
    void run();

private:
    unsigned short port_;
    std::string dbHost_;
    std::string dbName_;
    std::string dbUser_;
    std::string dbPass_;
    int dbPort_;

    std::vector<std::string> parseQuery(const std::string& rawQuery);
    std::vector<SearchResult> searchInDatabase(const std::vector<std::string>& words);
    std::string buildSearchForm();
    std::string buildSearchResults(const std::vector<SearchResult>& results);
    std::string buildErrorPage(const std::string& message);
};
