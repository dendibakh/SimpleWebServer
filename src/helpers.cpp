#include "helpers.hpp"
#include <unordered_map>
#include <sstream>

using mimeExtMap = std::unordered_map<std::string, std::string>;

static const mimeExtMap& getMimeExt()
{
  static mimeExtMap map = { { "gif", "image/gif" },
			    { "htm", "text/html" },
			    { "html", "text/html" },
			    { "jpg", "image/jpeg" },
			    { "png", "image/png" }
			  };
  return map;
}

std::string extensionToMimeType(const std::string& extension)
{
  auto it = getMimeExt().find(extension);
  if (it != getMimeExt().end())
    return it->second;

  return "text/plain";
}

bool urlDecode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}
