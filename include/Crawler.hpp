//
// Created by mrbgn on 4/18/21.
//

#include <iostream>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

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
  Crawler(size_t depth, IManager* manager);
  void Download(UrlToDownload&& to_download);
  void Parse(PageToParse&& to_parse);
  std::string DefineTarget(std::string url);
  std::string DefineHost(std::string url);
  bool DefineLink(std::string link);
  void SearchForLinks(GumboNode* node, PageOutput& pageOutput);

 private:
  size_t _depth;
  IManager* _manager;
};


#endif  // PRODUCER_CONSUMER_CRAWLER_HPP
