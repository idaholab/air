//* This file is part of air
//* https://github.com/idaholab/air
//*
//* All rights reserved, see NOTICE.txt for full restrictions
//* https://github.com/idaholab/air/blob/master/NOTICE.txt
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

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
