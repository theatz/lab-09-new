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
  virtual void AddDownloadTask(PageToParse& str) = 0;
  virtual void AddParseTask(PageOutput& str) = 0;
};

#endif  // PRODUCER_CONSUMER_IMANAGER_HPP
