/*
  This code belongs to https://rosettacode.org/wiki/Number_names
*/

#include <string>
#include <iostream>
using std::string;

const char* smallNumbers[] = {
  "zero", "one", "two", "three", "four", "five",
  "six", "seven", "eight", "nine", "ten",
  "eleven", "twelve", "thirteen", "fourteen", "fifteen",
  "sixteen", "seventeen", "eighteen", "nineteen"
};

string spellHundreds(unsigned n) {
  string res;
  if (n > 99) {
    res = smallNumbers[n/100];
    res += " hundred";
    n %= 100;
    if (n) res += " and ";
  }
  if (n >= 20) {
    static const char* Decades[] = {
      "", "", "twenty", "thirty", "forty",
      "fifty", "sixty", "seventy", "eighty", "ninety"
    };
    res += Decades[n/10];
    n %= 10;
    if (n) res += "-";
  }
  if (n < 20 && n > 0)
    res += smallNumbers[n];
  return res;
}

const char* thousandPowers[] = {
  " billion", " million",  " thousand", "" };

typedef unsigned long Spellable;

string spell(Spellable n) {
  if (n < 20) return smallNumbers[n];
  string res;
  const char** pScaleName = thousandPowers;
  Spellable scaleFactor = 1000000000;// 1 billion
  while (scaleFactor > 0) {
    if (n >= scaleFactor) {
      Spellable h = n / scaleFactor;
      res += spellHundreds(h) + *pScaleName;
      n %= scaleFactor;
      if (n) res += " ";
    }
    scaleFactor /= 1000;
    ++pScaleName;
  }
  return res;
}

