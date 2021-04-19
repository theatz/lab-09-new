//
// Created by mrbgn on 4/18/21.
//

#include <fstream>
#include <string>
#include <mutex>

#include "IManager.hpp"

#ifndef PRODUCER_CONSUMER_WRITER_HPP
#define PRODUCER_CONSUMER_WRITER_HPP

class Writer
{
 public:
  Writer(std::string& output, IManager& manager);
  void Write(std::string& to_write);

 private:
  std::mutex _lock;
  std::string _output;
  IManager& _manager;
};

#endif  // PRODUCER_CONSUMER_WRITER_HPP
