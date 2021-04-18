//
// Created by mrbgn on 4/18/21.
//

#include "Crawler.hpp"

void Crawler::Download(UrlToDownload&& to_download) {
  try {
    //    std::lock_guard<std::mutex> lk(_)
    auto const host = DefineHost(to_download.url);

    auto const port = "80";                     // https - 443, http - 80
    auto const target = DefineTarget(to_download.url);  //
    int version = 10;
    // The io_context is required for all I/O
    boost::asio::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver{ioc};
    tcp::socket socket{ioc};

    // Look up the domain name
    auto const results = resolver.resolve(host, port);

    // Make the connection on the IP address we get from a lookup
    boost::asio::connect(socket, results.begin(), results.end());

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the remote host
    http::write(socket, req);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::read(socket, buffer, res);

    // Write the message to standard out
    std::cout << boost::beast::buffers_to_string(res.body().data())
              << std::endl;

    // Gracefully close the socket
    boost::system::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes
    // so don't bother reporting it.
    //
    if (ec && ec != boost::system::errc::not_connected)
      throw boost::system::system_error{ec};

    //TODO
    // If we get here then the connection is closed gracefully
    //    return PageToParse {
    //      boost::beast::buffers_to_string(res.body().data()), url.depth
    //    }
  }
    //}
  catch (std::exception const& e) {
//    std::cerr << "Error: " << e.what() << ":" << url << std::endl;
//    return PageToParse{"error" url.depth};
  }

}
std::string Crawler::DefineTarget(std::string url) {
  size_t found = url.find("/");
  if (found != std::string::npos) return url.substr(url.find("/"));
  return "/";
}
std::string Crawler::DefineHost(std::string url) {
  size_t found = url.find("/");
  if (found != std::string::npos) return url.substr(0, url.find("/"));
  return url;
}
void Crawler::Parse(PageToParse&& to_parse) {
  struct PageOutput pageOutput;
  pageOutput.url.clear();
  pageOutput.src.clear();

  GumboOutput* output = gumbo_parse(to_parse.page.c_str());
  SearchForLinks(output->root, pageOutput);
  gumbo_destroy_output(&kGumboDefaultOptions, output);

//  return pageOutput; TODO
}
bool Crawler::DefineLink(std::string link) {
  std::size_t found;
  found = link.find("htpps://");
  if (found != std::string::npos) return false;
  found = link.find("http://");
  if (found == std::string::npos) return false;
  return true;
}
void Crawler::SearchForLinks(GumboNode* node, PageOutput& pageOutput) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;

  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    if (DefineLink(href->value)) {
      std::string push = href->value;
      pageOutput.url.push_back(UrlToDownload{push.substr(7), pageOutput.url[0].depth + 1}); // todo
    }
  }

  GumboAttribute* src;
  if (node->v.element.tag == GUMBO_TAG_IMG &&
      (src = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
    if (DefineLink(src->value)) {
      std::string push = src->value;
      pageOutput.src.push_back(push.substr(7));
    }
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    SearchForLinks(static_cast<GumboNode*>(children->data[i]), pageOutput);
  }
}
