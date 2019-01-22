///////////////////////////////////////////////////////////////////////////
// LibSBTL_vu_AIR - SBTL library for (gaseous) air based on:
//
// Lemmon, E.W., Jacobsen, R.T, Penoncello, S.G., and Friend, D.G.:
//
//   "Thermodynamic Properties of Air and Mixtures of Nitrogen, Argon, and Oxygen from 60 to 2000 K at Pressures to 2000 MPa,"
//   J. Phys. Chem. Ref. Data, 29(3):331-385, 2000. doi: 10.1063/1.1285884
//
// Lemmon, E.W. and Jacobsen, R.T.:
//
//   "Viscosity and Thermal Conductivity Equations for Nitrogen, Oxygen, Argon, and Air,"
//   Int. J. Thermophys., 25:21-69, 2004.
//
// Copyright (C) Idaho National Laboratory.
// All rights reserved.
//
// Disclaimer:
// The Idaho National Laboratory (INL) uses its best efforts to deliver a high-quality software and to verify that the computed information is correct.
// However, INL makes no warranties to that effect, and INL shall not be liable for any damage that may result from errors or omissions in the software.
//
// Version: 0.9.0
//
// HV_FLASH
//
///////////////////////////////////////////////////////////////////////////
//
#include "math.h"
#include "SBTL_AIR.h"
#include "SBTL_call_conv.h"
//
#define ITMAX 10

//initial guess from auxiliary splines
extern "C" double __stdcall U_VH_AIR_INI_T(double vt, double h);
//
//forward functions with derivatives
extern "C" void __stdcall DIFF_P_VU_AIR_T(double vt, double v, double u, double& p, double& dpdv, double& dpdu, double& dudv);
extern "C" void __stdcall DIFF_P_VU_AIR_TT(double vt, double u, double& p, double& dpdv, double& dpdu, double& dudv);
//
SBTLAPI int __stdcall FLASH_VH_AIR(double v, double h, double& u) throw()
{
    double vt;
    static const double df_h=1.e-8;  //-8   //abs. deviation in h

    double hx,px;
    double dhdu_v;
    double dpdv_u, dpdu_v, dudv_p;

    vt=log(v);

    //calculate initial guess
    u=U_VH_AIR_INI_T(vt,h);

    //newtons method
    double f_h=-1.;
    int icount=0;
    while(fabs(f_h)>df_h) {
        DIFF_P_VU_AIR_TT(vt, u, px, dpdv_u, dpdu_v, dudv_p);      // px, transformed derivatives
        hx=u+px*v*1.e3;
        dhdu_v=1.+dpdu_v*v*1.e3;
        f_h=hx-h;
        u=u-f_h/dhdu_v;
        if(icount++>ITMAX) {
            u=ERR_VAL;
            return I_ERR;
        }
    }
    return I_OK;
}
//
SBTLAPI int __stdcall FLASH_VH_AIR_T(double v, double vt, double h, double& u) throw()
{

    static const double df_h=1.e-8;  //-8   //abs. deviation in h

    double hx,px;
    double dhdu_v;
    double dpdv_u, dpdu_v, dudv_p;

    //calculate initial guess
    u=U_VH_AIR_INI_T(vt,h);

    //newtons method
    double f_h=-1.;
    int icount=0;
    while(fabs(f_h)>df_h) {
        DIFF_P_VU_AIR_TT(vt, u, px, dpdv_u, dpdu_v, dudv_p);      // px, transformed derivatives
        hx=u+px*v*1.e3;
        dhdu_v=1.+dpdu_v*v*1.e3;
        f_h=hx-h;
        u=u-f_h/dhdu_v;
        if(icount++>ITMAX) {
            u=ERR_VAL;
            return I_ERR;
        }
    }
    return I_OK;
}
//
SBTLAPI void __stdcall VH_FLASH_DERIV_AIR(double v, double vt, double u, double& dudv_h, double& dudh_v, double& dvdh_u) throw()
{
    double dpdv_u, dpdu_v, dudv_p;
    double dhdv_u, dhdu_v;
    double p_;

    //derivatives
    DIFF_P_VU_AIR_T(vt, v, u, p_, dpdv_u, dpdu_v, dudv_p);
    dhdv_u=(dpdv_u*v+p_)*1.e3;
    dhdu_v=1.+dpdu_v*v*1.e3;
    dudv_h=-dhdv_u/dhdu_v;
    //
    dudh_v=1./dhdu_v;
    dvdh_u=1./dhdv_u;
}
//
