#include <iostream>

#include "../../../deps/easyloggingpp/src/easylogging++.h"
#include "../exposed_fp_api.h"
#include "test_cases.h"

INITIALIZE_EASYLOGGINGPP

int
main (int argc, char* argv[])
{
  START_EASYLOGGINGPP (argc, argv);

  el::Configurations c;
  c.setToDefault ();

  el::Loggers::addFlag (el::LoggingFlag::HierarchicalLogging);
  el::Loggers::setLoggingLevel (el::Level::Warning);

  c.setGlobally (el::ConfigurationType::Format, "--------- | %level | %msg");
  c.setGlobally (el::ConfigurationType::ToFile, "false");

  el::Loggers::reconfigureAllLoggers (c);

  fp::traits::bwt e = 8;
  fp::traits::bwt s = 24;
  auto fmt          = fp::traits::fpt (e, s);
  auto tests = fp::test_cases (fmt, fp::test_cases::rounding_mode::RNA);

  tests.run ();

  return 0;
}