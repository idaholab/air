#include "gtest/gtest.h"
#include "AppFactory.h"
#include "MooseInit.h"
#include "Moose.h"
#include "MooseApp.h"
#include "AirApp.h"

PerfLog Moose::perf_log("air_unit");

int my_argc;
char ** my_argv;

GTEST_API_ int
main(int argc, char ** argv)
{
  // gtest removes (only) its args from argc and argv - so this  must be before moose init
  testing::InitGoogleTest(&argc, argv);
  my_argc = argc;
  my_argv = argv;

  MooseInit init(argc, argv);
  registerApp(AirApp);
  Moose::_throw_on_error = true;

  return RUN_ALL_TESTS();
}
