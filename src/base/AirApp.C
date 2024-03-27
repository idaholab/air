//* This file is part of air
//* https://github.com/idaholab/air
//*
//* All rights reserved, see NOTICE.txt for full restrictions
//* https://github.com/idaholab/air/blob/master/NOTICE.txt
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AirApp.h"
#include "AirRevision.h"
#include "MooseSyntax.h"
#include "AppFactory.h"

// Modules
#ifndef SKIP_MODULE_LOAD
#include "ModulesApp.h"
#endif

InputParameters
AirApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_output_syntax") = false;
  return params;
}

registerKnownLabel("AirApp");

AirApp::AirApp(InputParameters parameters) : MooseApp(parameters)
{
  AirApp::registerAll(_factory, _action_factory, _syntax);
}

// External entry point for dynamic application loading
extern "C" void
AirApp__registerApps()
{
  AirApp::registerApps();
}

void
AirApp::registerApps()
{
  registerApp(AirApp);
}

// External entry point for dynamic object registration
extern "C" void
AirApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  AirApp::registerAll(f, af, s);
}

void
AirApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  Registry::registerObjectsTo(f, {"AirApp"});
  Registry::registerActionsTo(af, {"AirApp"});

  libmesh_ignore(s);
#ifndef SKIP_MODULE_LOAD
  ModulesApp::registerAllObjects<AirApp>(f, af, s);
#endif
}
