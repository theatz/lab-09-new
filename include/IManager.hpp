//
// Created by mrbgn on 4/18/21.
//

#include "Structs.hpp"

#ifndef PRODUCER_CONSUMER_IMANAGER_HPP
#define PRODUCER_CONSUMER_IMANAGER_HPP

class IManager
{
 protected:
  ~IManager() = default;

 public:
  virtual void AddDownloadTask(UrlToDownload&& str) = 0;
  virtual void AddParseTask(PageToParse&& str) = 0;
  virtual void AddWriteTask(std::string&& str) = 0;
  virtual void DeleteDownloadTask() = 0;
  virtual void DeleteParseTask() = 0;
  virtual void DeleteWriteTask() = 0;
};

#endif  // PRODUCER_CONSUMER_IMANAGER_HPP
