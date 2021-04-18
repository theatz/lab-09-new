//
// Created by mrbgn on 4/18/21.
//

#include "IManager.hpp"
#include "Structs.hpp"
#include "ThreadPool.hpp"
#include "Crawler.hpp"

#ifndef PRODUCER_CONSUMER_MANAGER_HPP
#define PRODUCER_CONSUMER_MANAGER_HPP

class Manager : private IManager
{
 public:
  Manager(size_t depth, size_t networkThreads, size_t parseThreads,
          std::string output);
  void Start(UrlToDownload& to_download);
  void Stop();
  void AddDownloadTask(PageToParse& to_download) override;
  void AddParseTask(PageOutput& to_parse) override;

 private:
  size_t _networkThreads;
  size_t _parseThreads;
  std::string _output;
  ThreadPool _downloadPool;
  ThreadPool _parsePool;
  Crawler _crawler;

  size_t _networkTasks;
  size_t _parseTasks;

};


#endif  // PRODUCER_CONSUMER_MANAGER_HPP
