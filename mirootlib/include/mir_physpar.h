#ifndef MORIIISM_MITOOL_MIROOTLIB_PHYSPAR_H_
#define MORIIISM_MITOOL_MIROOTLIB_PHYSPAR_H_

// parameters of physics (cgs units)

// particle data group
const double kSpeedOfLight                = 2.99792458e10;   // (cm / s)
const double kPlanckConst                 = 6.6260693e-27;   // (erg s)
const double kElementCharge               = 4.80320441e-10;  // (esu)
const double kGravityConst                = 6.6742e-8;       // (dyn cm^2 g^-2)
const double kBoltzmannConst              = 1.3806505e-16;   // (erg / K)
const double kThomsonCrossSection         = 0.665245873e-24; // (cm^2)
const double kAvogadroConst               = 6.0221415e23;    // (mol^-1)
const double kStefanBoltzmannConst        = 5.670400e-5;     // (erg/cm^2/deg^4/s), sigma in F = sigma T^4
const double kElectronMass                = 9.1093826e-28;   // (g)
const double kProtonMass                  = 1.67262171e-24;  // (g)

const double kFineStructureConst          = 7.297352568e-3;  // alpha =~ 1/137
const double kClassicalElectronRadius     = 2.817940325e-13; // r_e (cm)
const double kBohrRadius                  = 0.5291772108e-8; // a_0 (cm)
// Bohr radius: approximately equal to the most probable distance
// between the proton and electron in a hydrogen atom in its ground state.

// -------------------------

const double kErgPerEv       = 1.6022e-12; // (erg/eV)
const double kJulePerEv      = 1.6022e-19; // (J/eV)
const double kHzPerEv        = 2.4180e14;  // (Hz/eV)
const double kKelvinPerEv    = 11604;      // (K/eV)

const double kCmPerAu        = 1.4960e13;  // (cm / AU) distance between sun and earth
const double kCmPerLy        = 9.4605e17;  // (cm / ly) light year
const double kCmPerPc        = 3.0857e18;  // (cm / pc)

const double kEarthEqRad     = 6.3781e8;   // (cm)  equatorial radius of the earth
const double kEarthMass      = 5.98e27;    // (g)
const double kGEarth         = 9.8067e2;   // (cm/s^2)  acceleration by gravity of the earth

const double kSunEqRad       = 6.960e10;   // (cm) equatorial radius of the sun
const double kSunMass        = 1.989e33;   // (g)

const double kErgPerJule      = 1.e7;      // (erg / J)
const double kGaussPerTesla   = 1.e4;      // (G / T)
const double kJyInCgs         = 1.e-23;    // (erg/s/cm^2/Hz)
const double kA0InCgs         = 1.e-8;     // (cm / A0) cm per Angstrom

// ------------------------------

const double kDayToSec        = 24*60*60;
const double kYearToSec       = 365*24*60*60;

#endif // MORIIISM_MITOOL_MIROOTLIB_PHYSPAR_H_
