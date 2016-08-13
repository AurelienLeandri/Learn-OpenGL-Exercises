//
// Created by leo on 7/31/16.
//

#include "file_reader.hh"
#include <fstream>
#include <iostream>

std::string file_reader::readFile(std::string fileName) {
  std::ifstream ifs;
  ifs.open(fileName);
  if (!ifs.is_open())
    std::cerr << "<FileReader> ERROR: Cannot open file "
      << fileName << std::endl;
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));
  return content;
}
