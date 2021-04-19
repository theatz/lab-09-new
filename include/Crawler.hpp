//
// Created by mrbgn on 4/18/21.
//

#include <iostream>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <mutex>

#include "gumbo.h"
#include "IManager.hpp"
#include "Structs.hpp"

using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

#ifndef PRODUCER_CONSUMER_CRAWLER_HPP
#define PRODUCER_CONSUMER_CRAWLER_HPP

class Crawler
{
 public:
  Crawler(uint32_t& depth, IManager& manager);
  void Download(UrlToDownload&& to_download);
  void Parse(PageToParse&& to_parse);
  std::string DefineTarget(std::string& url);
  std::string DefineHost(std::string& url);
  bool DefineLink(std::string link);
  void SearchForLinks(GumboNode* node, PageOutput& pageOutput, uint32_t depth);

 private:
  uint32_t _depth;
  std::mutex _lockParse;
  std::mutex _lockDownload;
  IManager& _manager;
};


#endif  // PRODUCER_CONSUMER_CRAWLER_HPP
