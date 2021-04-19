//
// Created by mrbgn on 4/18/21.
//

#include "Manager.hpp"
Manager::Manager(uint32_t& depth, uint32_t& networkThreads,
                 uint32_t& parseThreads, std::string& output)
    : _networkThreads(networkThreads),
      _parseThreads(parseThreads),
      _downloadPool(networkThreads),
      _parsePool(parseThreads),
      _writePool(1),
      _crawler(depth, *this),
      _writer(output, *this),
      _networkTasks(0),
      _parseTasks(0),
      _writerTasks(0)
{}

void Manager::Start(UrlToDownload& to_download) {
  _networkTasks++;
  AddDownloadTask(std::move(to_download));
  while (_networkTasks != 0 && _parseTasks != 0, _writerTasks != 0);
  Stop();
}
void Manager::Stop() {
  _downloadPool.Stop();
  _parsePool.Stop();
}

void Manager::AddDownloadTask(UrlToDownload&& to_download) {
//  return;
  _downloadPool.enqueue(&Crawler::Download, &_crawler,
                        std::forward<UrlToDownload>(to_download));
}
void Manager::AddParseTask(PageToParse&& to_parse) {
  _parsePool.enqueue(&Crawler::Parse, &_crawler,
                     std::forward<PageToParse>(to_parse));
}
void Manager::AddWriteTask(std::string&& to_write) {
  _writePool.enqueue(&Writer::Write, &_writer,
                     std::forward<std::string>(to_write));
}
void Manager::DeleteDownloadTask() {
  return;
}
void Manager::DeleteParseTask() {
  return;
}
void Manager::DeleteWriteTask() {
  return;
}
