//
// Created by mrbgn on 4/18/21.
//

#include <atomic>

#include "IManager.hpp"
#include "Structs.hpp"
#include "ThreadPool.hpp"
#include "Crawler.hpp"
#include "Writer.hpp"

#ifndef PRODUCER_CONSUMER_MANAGER_HPP
#define PRODUCER_CONSUMER_MANAGER_HPP

class Manager : public IManager
{
 public:
  Manager(uint32_t& depth, uint32_t& networkThreads, uint32_t& parseThreads,
          std::string& output);
  void Start(UrlToDownload& to_download);
  void Stop();
  void AddDownloadTask(UrlToDownload&& to_download) override;
  void AddParseTask(PageToParse&& to_parse) override;
  void AddWriteTask(std::string&& to_write) override;
  void DeleteDownloadTask() override;
  void DeleteParseTask() override;
  void DeleteWriteTask() override;


 private:
  uint32_t _networkThreads;
  uint32_t _parseThreads;
  ThreadPool _downloadPool;
  ThreadPool _parsePool;
  ThreadPool _writePool;
  Crawler _crawler;
  Writer _writer;

  std::atomic<uint32_t> _networkTasks;
  std::atomic<uint32_t> _parseTasks;
  std::atomic<uint32_t> _writerTasks;

};


#endif  // PRODUCER_CONSUMER_MANAGER_HPP
