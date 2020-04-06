#pragma once

#include "MooseApp.h"

class Factory;

class AirApp : public MooseApp
{
public:
  AirApp(InputParameters parameters);

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);

protected:
public:
  static InputParameters validParams();
};
