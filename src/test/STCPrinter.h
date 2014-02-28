#ifndef ST_8749320934_TEST_STC_PRINTER
#define ST_8749320934_TEST_STC_PRINTER
#include "STC/STC.h"
#include "Exception.h"
#include <iostream>
#include <string>
void STCPrinter(STC::STC* head, std::ostream& out = *(Exception::LogFile), std::string prefix = "");
#endif
