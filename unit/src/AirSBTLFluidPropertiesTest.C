//* This file is part of air
//* https://github.com/idaholab/air
//*
//* All rights reserved, see NOTICE.txt for full restrictions
//* https://github.com/idaholab/air/blob/master/NOTICE.txt
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AirSBTLFluidPropertiesTest.h"
#include "SinglePhaseFluidPropertiesTestUtils.h"

TEST_F(AirSBTLFluidPropertiesTest, test)
{
  const Real T = 120.0 + 273.15;
  const Real p = 101325;

  const Real rho_from_p_T = _fp->rho_from_p_T(p, T);
  const Real rho = rho_from_p_T;

  const Real h_from_p_T = _fp->h_from_p_T(p, T);
  const Real h = h_from_p_T;

  const Real e_from_p_rho = _fp->e_from_p_rho(p, rho);
  const Real e = e_from_p_rho;

  const Real v = 1 / rho;

  const Real s_from_v_e = _fp->s_from_v_e(v, e);
  const Real s = s_from_v_e;

  // p
  REL_TEST(_fp->p_from_v_e(v, e), p, REL_TOL_CONSISTENCY);
  REL_TEST(_fp->p_from_h_s(h, s), p, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->p_from_v_e, v, e, REL_TOL_DERIVATIVE);
  DERIV_TEST(_fp->p_from_h_s, h, s, REL_TOL_DERIVATIVE);

  // T
  REL_TEST(_fp->T_from_v_e(v, e), T, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->T_from_v_e, v, e, REL_TOL_DERIVATIVE);

  // rho
  // TODO: REL_TEST(rho, rho_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(rho_from_p_T, 0.89770070582713246, REL_TOL_SAVED_VALUE);
  REL_TEST(_fp->rho_from_p_s(p, s), rho_from_p_T, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->rho_from_p_T, p, T, REL_TOL_DERIVATIVE);
  DERIV_TEST(_fp->rho_from_p_s, p, s, REL_TOL_DERIVATIVE);

  // e
  // TODO: REL_TEST(e, e_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(e_from_p_rho, 8150.2752346044754, REL_TOL_SAVED_VALUE);
  REL_TEST(_fp->e_from_v_h(v, h), e, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->e_from_p_rho, p, rho, 5e-4);
  DERIV_TEST(_fp->e_from_v_h, v, h, REL_TOL_DERIVATIVE);

  // c
  const Real c = _fp->c_from_v_e(v, e);
  // TODO: REL_TEST(c, c_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(c, 397.06740585871455, REL_TOL_SAVED_VALUE);
  DERIV_TEST(_fp->c_from_v_e, v, e, REL_TOL_DERIVATIVE);

  // cp
  const Real cp = _fp->cp_from_v_e(v, e);
  // TODO: REL_TEST(cp, cp_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(cp, 1013.3795339037777, REL_TOL_SAVED_VALUE);
  DERIV_TEST(_fp->cp_from_v_e, v, e, REL_TOL_DERIVATIVE);
  REL_TEST(_fp->cp_from_p_T(p, T), 1013.3795339037777, REL_TOL_SAVED_VALUE);

  // cv
  const Real cv = _fp->cv_from_v_e(v, e);
  // TODO: REL_TEST(cv, cv_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(cv, 725.57903095165773, REL_TOL_SAVED_VALUE);
  REL_TEST(_fp->cv_from_p_T(p, T), 725.57903095165773, REL_TOL_SAVED_VALUE);
  DERIV_TEST(_fp->cv_from_v_e, v, e, REL_TOL_DERIVATIVE);

  // mu
  Real mu = _fp->mu_from_v_e(v, e);
  // TODO: REL_TEST(mu, mu_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(mu, 0.000022763142836965456, REL_TOL_SAVED_VALUE);
  REL_TEST(_fp->mu_from_p_T(p, T), 0.000022763142836965456, REL_TOL_SAVED_VALUE);
  Real dmu_dv, dmu_de;
  _fp->mu_from_v_e(v, e, mu, dmu_dv, dmu_de);
  REL_TEST(mu, 0.000022763142836965456, REL_TOL_SAVED_VALUE);
  REL_TEST(dmu_dv, 0., REL_TOL_SAVED_VALUE);
  REL_TEST(dmu_de, 0., REL_TOL_SAVED_VALUE);

  // k
  const Real k = _fp->k_from_v_e(v, e);
  // TODO: REL_TEST(k, k_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(k, 0.032989538356443394, REL_TOL_SAVED_VALUE);
  REL_TEST(_fp->k_from_p_T(p, T), 0.032989538356443394, REL_TOL_SAVED_VALUE);
  DERIV_TEST(_fp->k_from_v_e, v, e, REL_TOL_DERIVATIVE);
  DERIV_TEST(_fp->k_from_p_T, p, T, REL_TOL_DERIVATIVE);

  // s
  REL_TEST(s, 528.99169194029662, REL_TOL_EXTERNAL_VALUE);
  // TODO: REL_TEST(s, s_saved, REL_TOL_SAVED_VALUE);
  REL_TEST(_fp->s_from_h_p(h, p), s, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->s_from_v_e, v, e, REL_TOL_DERIVATIVE);
  DERIV_TEST(_fp->s_from_h_p, h, p, REL_TOL_DERIVATIVE);

  // g
  const Real g = _fp->g_from_v_e(v, e);
  REL_TEST(g, -86951.234900372016, REL_TOL_EXTERNAL_VALUE);
  // TODO: REL_TEST(g, g_saved, REL_TOL_SAVED_VALUE);

  // h
  // TODO: REL_TEST(h, h_external, REL_TOL_EXTERNAL_VALUE);
  REL_TEST(h_from_p_T, 121021.96993449892, REL_TOL_SAVED_VALUE);
  DERIV_TEST(_fp->h_from_p_T, p, T, REL_TOL_DERIVATIVE);

  REL_TEST(_fp->e_from_T_v(T, v), e, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->e_from_T_v, T, v, REL_TOL_DERIVATIVE * 2.);
  REL_TEST(_fp->p_from_T_v(T, v), p, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->p_from_T_v, T, v, REL_TOL_DERIVATIVE);
  REL_TEST(_fp->h_from_T_v(T, v), h, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->h_from_T_v, T, v, REL_TOL_DERIVATIVE * 4.);
  REL_TEST(_fp->s_from_T_v(T, v), s, REL_TOL_CONSISTENCY);
  DERIV_TEST(_fp->s_from_T_v, T, v, REL_TOL_DERIVATIVE);
  REL_TEST(_fp->cv_from_T_v(T, v), cv, REL_TOL_CONSISTENCY);

  // beta
  // const Real beta = _fp->beta_from_p_T(p, T);
  // TODO: REL_TEST(beta, beta_external, REL_TOL_EXTERNAL_VALUE);
  // TODO: REL_TEST(beta, beta_saved, REL_TOL_SAVED_VALUE);

  REL_TEST(_fp->molarMass(), 0.02896546, REL_TOL_SAVED_VALUE);
}
