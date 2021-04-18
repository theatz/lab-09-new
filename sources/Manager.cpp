//
// Created by mrbgn on 4/18/21.
//

#include "Manager.hpp"
Manager::Manager(size_t depth, size_t networkThreads, size_t parseThreads,
                 std::string output)
    : _networkThreads(networkThreads),
      _parseThreads(parseThreads),
      _output(output),
      _downloadPool(networkThreads),
      _parsePool(parseThreads),
      _crawler(depth, *this),
      _networkTasks(0),
      _parseTasks(0)
{}
void Manager::Start(UrlToDownload& to_download) {
  _networkTasks++;
  AddDownloadTask(to_download);
  while (_networkTasks != 0 && _parseTasks != 0);
  Stop();
}
void Manager::Stop() {
  _downloadPool.Stop();
  _parsePool.Stop();
}
