#ifndef REDUCER_REDUCER_OPTION_H_
#define REDUCER_REDUCER_OPTION_H_

#include <string>
#include "../../thirdparty/cmdline.h"

class ReducerOption {
 public:
  ReducerOption() {}

  bool Parse(int argc, char** argv) {
    parser_.add<std::string>("ats", 'a');
    parser_.add<std::string>("dot", 'd', "", false);

    if (!parser_.parse(argc, argv)) {
      std::cout << parser_.error_full() << parser_.usage();
      return false;
    }

    return true;
  }

  std::string ats_file_name() const { return parser_.exist("ats") ? std::move(parser_.get<std::string>("ats")) : ""; }
  std::string dot_file_name() const { return parser_.exist("dot") ? std::move(parser_.get<std::string>("dot")) : ""; }
 private:
  cmdline::parser parser_;

  DISALLOW_COPY_AND_ASSIGN(ReducerOption);
};

#endif  // REDUCER_REDUCER_OPTION_H_