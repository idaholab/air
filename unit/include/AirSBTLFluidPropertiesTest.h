//* This file is part of air
//* https://github.com/idaholab/air
//*
//* All rights reserved, see NOTICE.txt for full restrictions
//* https://github.com/idaholab/air/blob/master/NOTICE.txt
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MooseObjectUnitTest.h"
#include "AirSBTLFluidProperties.h"

class AirSBTLFluidPropertiesTest : public MooseObjectUnitTest
{
public:
  AirSBTLFluidPropertiesTest() : MooseObjectUnitTest("AirApp") { buildObjects(); }

protected:
  void buildObjects()
  {
    InputParameters uo_pars = _factory.getValidParams("AirSBTLFluidProperties");
    _fe_problem->addUserObject("AirSBTLFluidProperties", "fp", uo_pars);
    _fp = &_fe_problem->getUserObject<AirSBTLFluidProperties>("fp");
  }

  const AirSBTLFluidProperties * _fp;
};
