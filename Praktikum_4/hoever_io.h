#ifndef HOEVER_IO_H
#define HOEVER_IO_H

#include <vector>
#include <string>
#include "CKomplex.h"

std::vector<CKomplex> werte_einlesen(const std::string& dateiname);
void                  werte_ausgeben(const std::string& dateiname, const std::vector<CKomplex>& werte, double epsilon);

#endif // HOEVER_IO_H
