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
// SBTL_call_conv.h
//
#pragma once

#ifdef WIN32
    #ifdef SBTL_EXPORTS
        #define SBTLAPI extern "C" __declspec(dllexport)
    #elif SBTL_IMPORTS
        #define SBTLAPI extern "C" __declspec(dllimport)
    #else
        #define SBTLAPI extern "C"
    #endif
#else
    #define SBTLAPI extern "C"
    #define __stdcall
#endif
