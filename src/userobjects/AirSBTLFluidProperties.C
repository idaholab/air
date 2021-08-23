#include "AirSBTLFluidProperties.h"
#include "contrib/libSBTL_Air/SBTL_AIR.h"

extern "C" double P_VU_AIR(double v, double u);
extern "C" double T_VU_AIR(double v, double u);
extern "C" int PT_FLASH_AIR(double p, double t, double & v, double & vt, double & u);
extern "C" int PT_FLASH_DERIV_AIR(double p,
                                  double t,
                                  double & v,
                                  double & vt,
                                  double & dvdp_t,
                                  double & dvdt_p,
                                  double & dpdt_v,
                                  double & u,
                                  double & dudp_t,
                                  double & dudt_p,
                                  double & dpdt_u);
extern "C" int PH_FLASH_AIR(double p, double h, double & v, double & vt, double & u);
extern "C" int PS_FLASH_AIR(double p, double s, double & v, double & vt, double & u);
extern "C" void PS_FLASH_DERIV_AIR(double v,
                                   double vt,
                                   double u,
                                   double & dvdp_s,
                                   double & dvds_p,
                                   double & dpds_v,
                                   double & dudp_s,
                                   double & duds_p,
                                   double & dpds_u);
extern "C" double S_VU_AIR(double v, double u);
extern "C" double W_VU_AIR(double v, double u);
extern "C" double CP_VU_AIR(double v, double u);
extern "C" double CV_VU_AIR(double v, double u);
extern "C" double ETA_VU_AIR(double v, double u);
extern "C" double LAMBDA_VU_AIR(double v, double u);
extern "C" double U_VP_AIR(double v, double p);
extern "C" double U_VT_AIR(double v, double t);
extern "C" double S_VU_AIR(double v, double u);
extern "C" double G_VU_AIR(double v, double e);
extern "C" int HS_FLASH_AIR(double h, double s, double & v, double & vt, double & u);
extern "C" void HS_FLASH_DERIV_AIR(double v,
                                   double vt,
                                   double u,
                                   double & dvdh_s,
                                   double & dvds_h,
                                   double & dhds_v,
                                   double & dudh_s,
                                   double & duds_h,
                                   double & dhds_u);
extern "C" int FLASH_VH_AIR(double v, double h, double & u);
// SBTL functions with derivatives
extern "C" void
DIFF_P_VU_AIR(double v, double u, double & p, double & dpdv, double & dpdu, double & dudv);
extern "C" void DIFF_P_VU_AIR_T(
    double vt, double v, double u, double & p, double & dpdv, double & dpdu, double & dudv);
extern "C" void
DIFF_T_VU_AIR(double v, double u, double & t, double & dtdv, double & dtdu, double & dudv);
extern "C" void DIFF_T_VU_AIR_T(
    double vt, double v, double u, double & t, double & dtdv, double & dtdu, double & dudv);
extern "C" void
DIFF_S_VU_AIR(double v, double u, double & s, double & dsdv, double & dsdu, double & dudv);
extern "C" void
DIFF_W_VU_AIR(double v, double u, double & c, double & dcdv, double & dcdu, double & dudv);
extern "C" void DIFF_LAMBDA_VU_AIR(
    double v, double u, double & lambda, double & dlambdadv, double & dlambdadu, double & dudv);
extern "C" void DIFF_LAMBDA_VU_AIR_T(double vt,
                                     double v,
                                     double u,
                                     double & lambda,
                                     double & dlambdadv,
                                     double & dlambdadu,
                                     double & dudv);
extern "C" void
DIFF_U_VP_AIR(double v, double p, double & u, double & dudv_p, double & dudp_v, double & dpdv_u);
extern "C" void DIFF_CP_VU_AIR_T(
    double vt, double v, double u, double & cp, double & dcpdv, double & dcpdu, double & dudv);
extern "C" void DIFF_CV_VU_AIR_T(
    double vt, double v, double u, double & cv, double & dcvdv, double & dcvdu, double & dudv);

registerMooseObject("AirApp", AirSBTLFluidProperties);

InputParameters
AirSBTLFluidProperties::validParams()
{
  InputParameters params = SinglePhaseFluidProperties::validParams();
  params += NaNInterface::validParams();
  params.addClassDescription("Fluid properties of air (gas phase).");
  return params;
}

AirSBTLFluidProperties::AirSBTLFluidProperties(const InputParameters & parameters)
  : SinglePhaseFluidProperties(parameters),
    NaNInterface(this),
    _to_MPa(1e-6),
    _to_Pa(1e6),
    _to_kJ(1e-3),
    _to_J(1e3)
{
}

Real
AirSBTLFluidProperties::p_from_v_e(Real v, Real e) const
{
  return P_VU_AIR(v, e * _to_kJ) * _to_Pa;
}

void
AirSBTLFluidProperties::p_from_v_e(Real v, Real e, Real & p, Real & dp_dv, Real & dp_de) const
{
  e *= _to_kJ;

  double de_dv_p;
  DIFF_P_VU_AIR(v, e, p, dp_dv, dp_de, de_dv_p);

  p *= _to_Pa;
  dp_dv *= _to_Pa;
  dp_de *= _to_Pa / _to_J;
}

Real
AirSBTLFluidProperties::T_from_v_e(Real v, Real e) const
{
  return T_VU_AIR(v, e * _to_kJ);
}

void
AirSBTLFluidProperties::T_from_v_e(Real v, Real e, Real & T, Real & dT_dv, Real & dT_de) const
{
  e *= _to_kJ;

  double de_dv_T;
  DIFF_T_VU_AIR(v, e, T, dT_dv, dT_de, de_dv_T);

  dT_de /= _to_J;
}

Real
AirSBTLFluidProperties::c_from_v_e(Real v, Real e) const
{
  return W_VU_AIR(v, e * _to_kJ);
}

void
AirSBTLFluidProperties::c_from_v_e(Real v, Real e, Real & c, Real & dc_dv, Real & dc_de) const
{
  double de_dv_c;
  DIFF_W_VU_AIR(v, e * _to_kJ, c, dc_dv, dc_de, de_dv_c);

  dc_de /= _to_J;
}

Real
AirSBTLFluidProperties::e_from_v_h(Real v, Real h) const
{
  double e;
  const unsigned int ierr = FLASH_VH_AIR(v, h * _to_kJ, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return e * _to_J;
}

void
AirSBTLFluidProperties::e_from_v_h(Real v, Real h, Real & e, Real & de_dv, Real & de_dh) const
{
  const unsigned int ierr = FLASH_VH_AIR(v, h * _to_kJ, e);
  if (ierr != I_OK)
  {
    e = getNaN();
    de_dv = getNaN();
    de_dh = getNaN();
  }
  else
  {
    double p, dp_dv, dp_de, de_dv_p;
    DIFF_P_VU_AIR(v, e, p, dp_dv, dp_de, de_dv_p);
    e *= _to_J;
    p *= _to_Pa;
    dp_dv *= _to_Pa;
    dp_de *= _to_Pa / _to_J;

    Real dv_dh = 1. / (p + dp_dv * v);
    de_dh = 1. / (1. + dp_de * v);
    de_dv = -de_dh / dv_dh;
  }
}

Real
AirSBTLFluidProperties::cp_from_v_e(Real v, Real e) const
{
  return CP_VU_AIR(v, e * _to_kJ) * _to_J;
}

void
AirSBTLFluidProperties::cp_from_v_e(Real v, Real e, Real & cp, Real & dcp_dv, Real & dcp_de) const
{
  double vt = std::log(v);
  double de_dv_cp;
  DIFF_CP_VU_AIR_T(vt, v, e * _to_kJ, cp, dcp_dv, dcp_de, de_dv_cp);
  cp *= _to_J;
  dcp_dv *= _to_J;
}

Real
AirSBTLFluidProperties::cv_from_v_e(Real v, Real e) const
{
  return CV_VU_AIR(v, e * _to_kJ) * _to_J;
}

void
AirSBTLFluidProperties::cv_from_v_e(Real v, Real e, Real & cv, Real & dcv_dv, Real & dcv_de) const
{
  double vt = std::log(v);
  double de_dv_cv;
  DIFF_CV_VU_AIR_T(vt, v, e * _to_kJ, cv, dcv_dv, dcv_de, de_dv_cv);
  cv *= _to_J;
  dcv_dv *= _to_J;
}

Real
AirSBTLFluidProperties::mu_from_v_e(Real v, Real e) const
{
  return ETA_VU_AIR(v, e * _to_kJ);
}

void
AirSBTLFluidProperties::mu_from_v_e(Real v, Real e, Real & mu, Real & dmu_dv, Real & dmu_de) const
{
  mu = mu_from_v_e(v, e);
  // currently zero, becuase the underlying SBTL package has no API for it
  dmu_dv = 0;
  dmu_de = 0;
}

Real
AirSBTLFluidProperties::k_from_v_e(Real v, Real e) const
{
  return LAMBDA_VU_AIR(v, e * _to_kJ);
}

void
AirSBTLFluidProperties::k_from_v_e(Real v, Real e, Real & k, Real & dk_dv, Real & dk_de) const
{
  double dedv;
  DIFF_LAMBDA_VU_AIR(v, e * _to_kJ, k, dk_dv, dk_de, dedv);
  dk_de *= 1 / _to_J;
}

Real
AirSBTLFluidProperties::s_from_v_e(Real v, Real e) const
{
  return S_VU_AIR(v, e * _to_kJ) * _to_J;
}

void
AirSBTLFluidProperties::s_from_v_e(Real v, Real e, Real & s, Real & ds_dv, Real & ds_de) const
{
  double de_dv_s;
  DIFF_S_VU_AIR(v, e * _to_kJ, s, ds_dv, ds_de, de_dv_s);
  s *= _to_J;
  ds_dv *= _to_J;
  ds_de *= _to_J / _to_J;
}

Real
AirSBTLFluidProperties::s_from_h_p(Real h, Real p) const
{
  double v, vt, e;
  const unsigned int ierr = PH_FLASH_AIR(p * _to_MPa, h * _to_kJ, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return S_VU_AIR(v, e) * _to_J;
}

void
AirSBTLFluidProperties::s_from_h_p(Real h, Real p, Real & s, Real & ds_dh, Real & ds_dp) const
{
  double v, vt, e;
  const unsigned int ierr = PH_FLASH_AIR(p * _to_MPa, h * _to_kJ, v, vt, e);
  if (ierr != I_OK)
  {
    s = getNaN();
    ds_dh = getNaN();
    ds_dp = getNaN();
  }
  else
  {
    double pp, dp_dv, dp_de, de_dv_p;
    double ds_dv, ds_de, de_dv_s;
    DIFF_P_VU_AIR(v, e, pp, dp_dv, dp_de, de_dv_p);
    DIFF_S_VU_AIR(v, e, s, ds_dv, ds_de, de_dv_s);
    e *= _to_J;
    dp_dv *= _to_Pa;
    dp_de *= _to_Pa / _to_J;
    s *= _to_J;
    ds_dv *= _to_J;
    // ds_de *= _to_J / _to_J;
    double dh_dv = (p + dp_dv * v);
    double dh_de = 1. + dp_de * v;
    ds_dp = (ds_dv * dh_de - ds_de * dh_dv) / (dp_dv * dh_de - dp_de * dh_dv);
    ds_dh = (ds_dv * dp_de - ds_de * dp_dv) / (dh_dv * dp_de - dh_de * dp_dv);
  }
}

Real
AirSBTLFluidProperties::beta_from_p_T(Real p, Real T) const
{
  double rho, drho_dp, drho_dT;
  rho_from_p_T(p, T, rho, drho_dp, drho_dT);
  return -drho_dT / rho;
}

void
AirSBTLFluidProperties::beta_from_p_T(
    Real p, Real T, Real & beta, Real & dbeta_dp, Real & dbeta_dT) const
{
  beta = beta_from_p_T(p, T);
  dbeta_dp = 0;
  dbeta_dT = 0;
}

Real
AirSBTLFluidProperties::rho_from_p_T(Real p, Real T) const
{
  double v, vt, e;
  const unsigned int ierr = PT_FLASH_AIR(p * _to_MPa, T, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return 1. / v;
}

void
AirSBTLFluidProperties::rho_from_p_T(
    Real p, Real T, Real & rho, Real & drho_dp, Real & drho_dT) const
{
  double v, vt, dv_dp, dv_dT, dp_dT_v;
  double e, de_dp, de_dT, dp_dT_e;
  const unsigned int ierr =
      PT_FLASH_DERIV_AIR(p * _to_MPa, T, v, vt, dv_dp, dv_dT, dp_dT_v, e, de_dp, de_dT, dp_dT_e);
  if (ierr != I_OK)
  {
    rho = getNaN();
    drho_dp = getNaN();
    drho_dT = getNaN();
  }
  else
  {
    rho = 1. / v;
    const double drho_dv = -1. / v / v;
    drho_dp = drho_dv * dv_dp / _to_Pa;
    drho_dT = drho_dv * dv_dT;
  }
}

Real
AirSBTLFluidProperties::e_from_p_rho(Real p, Real rho) const
{
  double v = 1. / rho;
  return U_VP_AIR(v, p * _to_MPa) * _to_J;
}

void
AirSBTLFluidProperties::e_from_p_rho(Real p, Real rho, Real & e, Real & de_dp, Real & de_drho) const
{
  double de_dv, dp_dv_e;
  double v = 1. / rho;
  DIFF_U_VP_AIR(v, p * _to_MPa, e, de_dv, de_dp, dp_dv_e);

  e *= _to_J;
  de_dp *= _to_J / _to_Pa;
  double dv_drho = -1. / rho / rho;
  de_drho = de_dv * dv_drho * _to_J;
}

Real
AirSBTLFluidProperties::e_from_T_v(Real T, Real v) const
{
  return U_VT_AIR(v, T) * _to_J;
}

void
AirSBTLFluidProperties::e_from_T_v(Real T, Real v, Real & e, Real & de_dT, Real & de_dv) const
{
  double TT, dT_dv_e, dT_de_v, de_dv_T;

  e = U_VT_AIR(v, T);

  DIFF_T_VU_AIR(v, e, TT, dT_dv_e, dT_de_v, de_dv_T);

  e *= _to_J;
  de_dT = 1. / dT_de_v * _to_J;
  de_dv = de_dv_T * _to_J;
}

Real
AirSBTLFluidProperties::p_from_T_v(Real T, Real v) const
{
  double e;
  e = U_VT_AIR(v, T);
  return P_VU_AIR(v, e) * _to_Pa;
}

void
AirSBTLFluidProperties::p_from_T_v(Real T, Real v, Real & p, Real & dp_dT, Real & dp_dv) const
{
  double e, dp_dv_e, dp_de_v, de_dv_p;
  double TT, dT_dv_e, dT_de_v, de_dv_T;

  e = U_VT_AIR(v, T);
  DIFF_P_VU_AIR(v, e, p, dp_dv_e, dp_de_v, de_dv_p);
  DIFF_T_VU_AIR(v, e, TT, dT_dv_e, dT_de_v, de_dv_T);

  p *= _to_Pa;
  dp_dT = (dp_de_v / dT_de_v) * _to_Pa;
  dp_dv = (dp_dv_e + dp_de_v * de_dv_T) * _to_Pa;
}

Real
AirSBTLFluidProperties::h_from_T_v(Real T, Real v) const
{
  double e, p;
  e = U_VT_AIR(v, T);
  p = P_VU_AIR(v, e);
  return (e + p * v * 1.e3) * _to_J;
}

void
AirSBTLFluidProperties::h_from_T_v(Real T, Real v, Real & h, Real & dh_dT, Real & dh_dv) const
{
  double e, dp_dv_e, dp_de_v, de_dv_p;
  double TT, dT_dv_e, dT_de_v, de_dv_T;
  double p, dp_dT, dp_dv, de_dT, de_dv;

  e = U_VT_AIR(v, T);
  DIFF_P_VU_AIR(v, e, p, dp_dv_e, dp_de_v, de_dv_p);
  DIFF_T_VU_AIR(v, e, TT, dT_dv_e, dT_de_v, de_dv_T);
  dp_dT = (dp_de_v / dT_de_v);
  dp_dv = (dp_dv_e + dp_de_v * de_dv_T);
  de_dT = 1. / dT_de_v;
  de_dv = de_dv_T;

  h = e + p * v * 1.e3;
  dh_dT = de_dT + dp_dT * v * 1.e3;
  dh_dv = de_dv + (dp_dv * v + p) * 1.e3;

  h *= _to_J;
  dh_dT *= _to_J;
  dh_dv *= _to_J;
}

Real
AirSBTLFluidProperties::s_from_T_v(Real T, Real v) const
{
  double e;
  e = U_VT_AIR(v, T);
  return S_VU_AIR(v, e) * _to_J;
}

void
AirSBTLFluidProperties::s_from_T_v(Real T, Real v, Real & s, Real & ds_dT, Real & ds_dv) const
{
  double e, ds_dv_e, ds_de_v, de_dv_s;
  double TT, dT_dv_e, dT_de_v, de_dv_T;

  e = U_VT_AIR(v, T);
  DIFF_S_VU_AIR(v, e, s, ds_dv_e, ds_de_v, de_dv_s);
  DIFF_T_VU_AIR(v, e, TT, dT_dv_e, dT_de_v, de_dv_T);
  ds_dT = (ds_de_v / dT_de_v);
  ds_dv = (ds_dv_e + ds_de_v * de_dv_T);

  s *= _to_J;
  ds_dT *= _to_J;
  ds_dv *= _to_J;
}

Real
AirSBTLFluidProperties::cv_from_T_v(Real T, Real v) const
{
  double e;
  e = U_VT_AIR(v, T);
  return CV_VU_AIR(v, e) * _to_J;
}

Real
AirSBTLFluidProperties::h_from_p_T(Real p, Real T) const
{
  double v, vt, e;
  const unsigned int ierr = PT_FLASH_AIR(p * _to_MPa, T, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return e * _to_J + p * v;
}

void
AirSBTLFluidProperties::h_from_p_T(Real p, Real T, Real & h, Real & dh_dp, Real & dh_dT) const
{
  double v, vt, dv_dp, dv_dT, dp_dT_v;
  double e, de_dp, de_dT, dp_dT_e;
  const unsigned int ierr =
      PT_FLASH_DERIV_AIR(p * _to_MPa, T, v, vt, dv_dp, dv_dT, dp_dT_v, e, de_dp, de_dT, dp_dT_e);
  if (ierr != I_OK)
  {
    h = getNaN();
    dh_dp = getNaN();
    dh_dT = getNaN();
  }
  else
  {
    h = e * _to_J + p * v;
    dh_dp = de_dp * _to_J / _to_Pa + (v + p * _to_MPa * dv_dp);
    dh_dT = de_dT * _to_J + p * dv_dT;
  }
}

Real
AirSBTLFluidProperties::cp_from_p_T(Real p, Real T) const
{
  double v, vt, e;
  const unsigned int ierr = PT_FLASH_AIR(p * _to_MPa, T, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return CP_VU_AIR(v, e) * _to_J;
}

void
AirSBTLFluidProperties::cp_from_p_T(Real p, Real T, Real & cp, Real & dcp_dp, Real & dcp_dT) const
{
  cp = cp_from_p_T(p, T);
  dcp_dp = 0;
  dcp_dT = 0;
}

Real
AirSBTLFluidProperties::cv_from_p_T(Real p, Real T) const
{
  double v, vt, e;
  const unsigned int ierr = PT_FLASH_AIR(p * _to_MPa, T, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return CV_VU_AIR(v, e) * _to_J;
}

Real
AirSBTLFluidProperties::mu_from_p_T(Real p, Real T) const
{
  double v, vt, e;
  const unsigned int ierr = PT_FLASH_AIR(p * _to_MPa, T, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return ETA_VU_AIR(v, e);
}

void
AirSBTLFluidProperties::mu_from_p_T(Real, Real, Real &, Real &, Real &) const
{
  mooseError(name(), ": ", __PRETTY_FUNCTION__, " not implemented.");
}

Real
AirSBTLFluidProperties::k_from_p_T(Real p, Real T) const
{
  double v, vt, e;
  const unsigned int ierr = PT_FLASH_AIR(p * _to_MPa, T, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return LAMBDA_VU_AIR(v, e);
}

void
AirSBTLFluidProperties::k_from_p_T(Real p, Real T, Real & k, Real & dk_dp, Real & dk_dT) const
{
  double v, vt, dv_dp, dv_dT, dp_dT_v;
  double e, de_dp, de_dT, dp_dT_e;
  const unsigned int ierr =
      PT_FLASH_DERIV_AIR(p * _to_MPa, T, v, vt, dv_dp, dv_dT, dp_dT_v, e, de_dp, de_dT, dp_dT_e);
  if (ierr != I_OK)
  {
    k = getNaN();
    dk_dp = getNaN();
    dk_dT = getNaN();
  }
  else
  {
    double pp, dpdv_u, dpdu_v, dudv_p;
    double tt, dtdv_u, dtdu_v, dudv_t;
    double dkdv_u, dkdu_v, dudv_k;
    DIFF_P_VU_AIR_T(vt, v, e, pp, dpdv_u, dpdu_v, dudv_p);
    DIFF_T_VU_AIR_T(vt, v, e, tt, dtdv_u, dtdu_v, dudv_t);
    DIFF_LAMBDA_VU_AIR_T(vt, v, e, k, dkdv_u, dkdu_v, dudv_k);
    dk_dp = (dkdv_u * dtdu_v - dkdu_v * dtdv_u) / (dpdv_u * dtdu_v - dpdu_v * dtdv_u) / _to_Pa;
    dk_dT = (dkdv_u * dpdu_v - dkdu_v * dpdv_u) / (dtdv_u * dpdu_v - dtdu_v * dpdv_u);
  }
}

Real
AirSBTLFluidProperties::p_from_h_s(Real h, Real s) const
{
  double v, vt, e;
  HS_FLASH_AIR(h * _to_kJ, s * _to_kJ, v, vt, e);
  return P_VU_AIR(v, e) * _to_Pa;
}

void
AirSBTLFluidProperties::p_from_h_s(Real h, Real s, Real & p, Real & dp_dh, Real & dp_ds) const
{
  double v, vt, e;
  HS_FLASH_AIR(h * _to_kJ, s * _to_kJ, v, vt, e);

  double dv_dh, dv_ds, dh_ds_v, de_dh, de_ds, dh_ds_e;
  HS_FLASH_DERIV_AIR(v, vt, e, dv_dh, dv_ds, dh_ds_v, de_dh, de_ds, dh_ds_e);

  double dp_dv, dp_de;
  p_from_v_e(v, e * _to_J, p, dp_dv, dp_de);

  dp_dh = dp_dv * dv_dh / _to_J + dp_de * de_dh;
  dp_ds = dp_dv * dv_ds / _to_J + dp_de * de_ds;
}

Real
AirSBTLFluidProperties::g_from_v_e(Real v, Real e) const
{
  return G_VU_AIR(v, e * _to_kJ) * _to_J;
}

Real
AirSBTLFluidProperties::rho_from_p_s(Real p, Real s) const
{
  double v, vt, e;
  const unsigned int ierr = PS_FLASH_AIR(p * _to_MPa, s * _to_kJ, v, vt, e);
  if (ierr != I_OK)
    return getNaN();
  else
    return 1. / v;
}

void
AirSBTLFluidProperties::rho_from_p_s(
    Real p, Real s, Real & rho, Real & drho_dp, Real & drho_ds) const
{
  double v, vt, e;
  const unsigned int ierr = PS_FLASH_AIR(p * _to_MPa, s * _to_kJ, v, vt, e);
  if (ierr != I_OK)
  {
    rho = getNaN();
    drho_dp = getNaN();
    drho_ds = getNaN();
  }
  else
  {
    double dv_dp, dv_ds, dp_ds_v, de_dp, de_ds, dp_ds_e;
    PS_FLASH_DERIV_AIR(v, vt, e, dv_dp, dv_ds, dp_ds_v, de_dp, de_ds, dp_ds_e);
    rho = 1. / v;
    double drho_dv = -1. / v / v;
    drho_dp = drho_dv * dv_dp / _to_Pa;
    drho_ds = drho_dv * dv_ds / _to_J;
  }
}

Real
AirSBTLFluidProperties::molarMass() const
{
  return 0.02896546;
}
