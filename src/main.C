//* This file is part of air
//* https://github.com/idaholab/air
//*
//* All rights reserved, see NOTICE.txt for full restrictions
//* https://github.com/idaholab/air/blob/master/NOTICE.txt
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AirApp.h"
#include "MooseInit.h"
#include "Moose.h"
#include "MooseApp.h"
#include "AppFactory.h"

// Create a performance log
PerfLog Moose::perf_log("Air");

// Begin the main program.
int
main(int argc, char * argv[])
{
  // Initialize MPI, solvers and MOOSE
  MooseInit init(argc, argv);

  // Register this application's MooseApp and any it depends on
  AirApp::registerApps();

  std::shared_ptr<MooseApp> app = AppFactory::createAppShared("AirApp", argc, argv);

  // Execute the application
  app->run();

  return 0;
}
