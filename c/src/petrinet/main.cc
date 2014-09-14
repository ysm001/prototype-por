#include <iostream>
#include <fstream>
#include "./pnml_parser.h"
#include "./petrinet_option.h"
#include "./ats_file_generator.h"
#include "../util/debug.h"

int main(int argc, char** argv) {
  PetrinetOption option;
  option.Parse(argc, argv);

  if (option.debug()) enable_debug();

  ATSFileGenerator generator;
  std::ofstream ofs(option.output_file_name());
  ofs << generator.Generate(option.pnml_file_name());
}
