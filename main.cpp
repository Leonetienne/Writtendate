#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include "spell.h"
#include "StringTools.h"

//! Basically what backticks do in a shell
//! Runs a command and returns stdout
std::string Eval(const std::string& cmd) {
  FILE *p;
  char ch;

  p = popen(cmd.c_str(), "r");
  if (p == NULL) {
    std::cerr << "Unable to open a  process. Make sure the requested program is installed! Tried to call:" << std::endl
      << "'" << cmd << "'" << std::endl;
    exit(-1);
  }

  std::stringstream ss;
  while ((ch=fgetc(p)) != EOF )
    ss << ch;

  // Remove terminating linebreak, if present
  std::string out = ss.str();
  if ((out.length() > 0) && (out[out.length() - 1] == '\n'))
      out = out.substr(0, out.length() - 1);

  return out;
}

//! I don't have to explain what this is, do I?
static const std::vector<std::string> daynths = {
  "first",
  "second",
  "third",
  "fourth",
  "fifth",
  "sixth",
  "seventh",
  "eighth",
  "ninth",
  "tenth",
  "eleventh",
  "twelfth",
  "thirteenth",
  "fourteenth",
  "fifteenth",
  "sixteenth",
  "seventeenth",
  "eighteenth",
  "nineteenth",
  "twentieth",
  "twentyfirst",
  "twentysecond",
  "twentythird",
  "twentyfourth",
  "twentyfifth",
  "twentysixth",
  "twentyseventh",
  "twentyeighth",
  "twentyninth",
  "thirtieth",
  "thirtyfirst"
};

int main() {
  const std::string weekday = Eval("date +'\%A'");
  const std::string month = Eval("date +'\%B'");
  const std::string year = spell(std::stoi(Eval("date +'\%Y'")));
  const std::string day = daynths[std::stoi(Eval("date +'\%d'")) - 1];
  const std::string hour = spell(std::stoi(Eval("date +'\%H'")));
  const std::string minute = spell(std::stoi(Eval("date +'\%M'")));
  const std::string seconds = spell(std::stoi(Eval("date +'\%S'")));

  std::stringstream ss;
  ss << "It is "
    << weekday << ", the "
    << day << " of "
    << month << ", " << year << ". "
    << "It is "
    << hour << " " << minute
    << " and "
    << seconds << " seconds.";

  std::cout << ss.str() << std::endl;

  return 0;
}

