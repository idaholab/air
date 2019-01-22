#ifndef AIRSBTLFLUIDPROPERTIESTEST_H
#define AIRSBTLFLUIDPROPERTIESTEST_H

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

#endif
