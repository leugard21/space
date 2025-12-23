#include "json.h"

#include <iomanip>
#include <sstream>

static std::string escape(const std::string &s) {
  std::ostringstream o;
  for (char c : s) {
    switch (c) {
    case '"':
      o << "\\\"";
      break;
    case '\\':
      o << "\\\\";
      break;
    case '\n':
      o << "\\n";
      break;
    case '\t':
      o << "\\t";
      break;
    default:
      o << c;
    }
  }
  return o.str();
}

std::string to_json(const ScanReport &report) {
  std::ostringstream out;
  out << "{";
  out << "\"total_size\":" << report.totalSize << ",";
  out << "\"skipped\":" << report.skipped << ",";
  out << "\"entries\":[";

  for (std::size_t i = 0; i < report.entries.size(); ++i) {
    const auto &e = report.entries[i];
    out << "{";
    out << "\"name\":\"" << escape(e.path.filename().string()) << "\",";
    out << "\"size\":" << e.size << ",";
    out << "\"percent\":" << std::fixed << std::setprecision(4) << e.percent;
    out << "}";

    if (i + 1 < report.entries.size()) {
      out << ",";
    }
  }

  out << "]}";
  return out.str();
}
