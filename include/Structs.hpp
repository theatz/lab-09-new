//
// Created by mrbgn on 4/18/21.
//
#include <string>
#include <vector>

#ifndef PRODUCER_CONSUMER_STRUCTS_HPP
#define PRODUCER_CONSUMER_STRUCTS_HPP

struct UrlToDownload {
  std::string url;
  uint32_t depth;
};

struct PageToParse {
  std::string page;
  uint32_t depth;
};

struct PageOutput {
  std::vector<std::string> src;
  std::vector<UrlToDownload> url;
};

#endif  // PRODUCER_CONSUMER_STRUCTS_HPP
