//
// Created by mrbgn on 4/18/21.
//

#include "Writer.hpp"
Writer::Writer(std::string& output, IManager& manager)
    : _output(output), _manager(manager)
{}

void Writer::Write(std::string&& to_write) {
  std::ofstream out;
  out.open(_output, std::ios::app);
  if (out.is_open())
  {
    out << to_write << std::endl;
  }
  out.close();

  {
    std::lock_guard<std::mutex> guard(_lock);
    _manager.DeleteWriteTask();
  }
}
