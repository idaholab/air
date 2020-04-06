#include "AirApp.h"
#include "AirRevision.h"
#include "MooseSyntax.h"
#include "AppFactory.h"

// Modules
#include "ModulesApp.h"

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

  ModulesApp::registerAll(f, af, s);
}
