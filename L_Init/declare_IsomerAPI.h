#ifndef _DECLARE_H
#define _DECLARE_H

#if !defined(mytypes_h)
#include "L_Init/mytypes_IsomerAPI.h"
#endif

/*
#if !defined(Distr_class2_Prob)
#include "L_Distribution/o_Distr2_prob.h"
#endif

#if !defined(SecondReactions_class)
#include "d_Secondary/o_SR.h"
#endif


#if !defined(Fireball_class)
#include "o_Evap/o_Fireball.h"       //TO
#endif

#if !defined(block_optic_class)
#include "L_Block/p_Block_Optic.h"
#endif

#if !defined(block_compound_class)
#include "L_Block/p_Block_Compound.h"
#endif

#if !defined(mass_class_h)
#include "L_Mass/o_Mass_class.h"
#endif

#include "L_Block/o_Block_calc.h"

#if !defined(O_EE_C_H)
#include "o_Evap/o_EE_c.h"
#endif

#include "L_Init/L_CS_file.h"

#if !defined(Isomer_class)
#include "L_Element/o_Isomer.h"
#endif

#include "d_MC/o_Ray_fileData.h"
*/
bool   flagRecalculateGOM;
bool   flagCalculateEnvelopes;

double G_CoefStragglingDecrease;
double G_CoefStraggK1;
double G_CoefStraggK2;
int     G_coef_transform;
int 	G_pixelMC;
int 	G_pixelMCtrans;
double G_ShiftTOF;
double BindingEnergyVV0;
double G_LeonD;
double G_LeonA;
double G_LeonP;
double G_ShiftVV0;

int G_SecondaryReactions;

//SR_filter SR_filter_frag, SR_filter_fiss;

//s_dBE s_dBE_work, s_dBE_default;
//double G_ExcitationEnergyCoef;
//double G_TimeEvaporation;

//============================================================
//============================================================
//=============    Evaporation   =====================
int G_MethodApf;     // search method
int G_ExcitationApf; // 0 - surface energy; 1 - AA
int    G_ExcitationApf1_type;  // 0 - constant value mode; 1 - current AA
double G_ExcitationApf1_MeV;   // constant value in MeV

int G_Mode_Apf_Manual;  // auto_mode


double G_Energy_in_T_for_nucleus_emit;
int    G_EvaporationVelocity;   // 0 - quality, 1 -fast
double G_R_Evaporation;

int G_CreateCSfile;
int G_CreatePDfile;
int G_MakeFullCSfile;
int G_CalculateAA;
int G_StateDensityMode;
int G_EvapUnstable;   //  0 - only stable
int G_Tunnelling;
int G_LastZevaporation;
int G_AvoidUnboundCS;
int G_ProtectedChannels;

double G_DeltaOddEven;
double G_DeltaOddEvenFission;
double G_DeltaOddEvenFB_N;
double G_DeltaOddEvenFB_Z;

//=============    Excitation energy   ======================
double G_AA_factor;
int G_MethodEE;

//======================================== A
// s_GeomAA FB;
// s_GeomAA FB_UP;
//======================================== B

// double G_HoleEnergy;
// int G_HoleMethod; // 0-lin, 1-exp
// //======================================== C

// s_EE_C EE_C;
//======================================== D
double G_MeanT, G_MeanT2, G_MeanTNZ;
//======================================== E
double G_LN_median,G_LN_median2;
double G_LN_variance,G_LN_variance2;

//-----------------
int G_ApplyLimitingTemperature;
//==================   AutoDialog ===========================

double G_Auto_Tun_a0;
double G_Auto_Tun_a1;
double G_Auto_Tun_a2;

int G_Auto_A_Bound;
int G_Auto_A_Pairing;

double  procent_charge_state_limit_total;
double  procent_charge_state_limit;
double  procent_charge_state_limit_beam_total;
double  procent_charge_state_limit_beam;


//============================================================
//============================================================
//============================================================

double G_tweak;
double G_StepRangeMult;
bool GlobalBreak=false;

int NP=64, NPsimple, NPcharge, NPopt, NPevap, NPevapFis, NP_SecReaction, NPfus_plot, NPwedge;
double Qtab_global[Number_Proton];  //  for charge state distribution

int G_CalcReaction;
int G_CalcReaction_stack;

double v_prod0,G_Sigma0,G_SigmaD, G_SigmaM /*, G_Sigma0con*/;
int NCALC;
int NCALC_MC;
int NCALC_MC_outside;
int NISOM;
bool FlagPrintToFile=false;
bool FusionCompoundCheck=true;
bool opt_fast_epax = false;

int G_LastZ_ask=eask_ask_always;

int  G_LastZ_value=130;
double SumCalc;
bool WinLog=true;
//double r_tab[Number_RangePoints][NumberTabELOSS];
int CalculateEnergyDistribution;
int VelocityExceed;   // if velocity two-body reaction low than Borrel velocity

// BLOCK *LastBLOCK;
// BLOCK *FirstBLOCK;
// const BLOCK *GateBLOCK;

// BLOCK_Cible     *Cible;
// BLOCK_Stripper  *Strip;



// CalcBlock  *CalcBLOCK;

// BEAM beam_vector;
// BEAM OptBeam_vector;
// BEAM ray_vector;
// OPTICAL_MATRIX  MG;

double EPAX_p_Norm = 1;
double EPAX_p_Un = 1.65;   	// slope par. n-rich ride of Z distr.

double EPAX_p_Up0 = 1.7880;		// slope par. p-rich ride of Z distr.
double EPAX_p_Up1 = +4.7210E-03;
double EPAX_p_Up2 = -1.3030E-05;

int EPAX_p_H_corrections = 1;

// w_show_setup  --- start
bool ReactionDialogMode=false;
int ReactionSaveMode=0;
int GlobalPermissionSetupRedraw = 0;
// w_show_setup  --- stop


//  from d_Monitor_ES_fission.cpp start
/*int paresFisPlot[NumberFisRB][2] = {   //N=3 is bad
    {1,0},
    {1,2},
    {4,5},
    {1,13},
    {1,4},
    {1,5},
    {7,6},
    {7,4},
    {7,5},//----------------CMS nrext
    {9,8},
    {14,13},
    {11,12}
     };
//  from d_Monitor_ES_fission.cpp stop

*/
/*distribution *ConvMomentum;
distribution2P *MoyalDistr;
distribution2P *EllipseDistr;

Compound *cp_tab    [NumberTabELOSS];
// BC5 ? Compound *cp_lat_tab[NumberTabELOSS];
CSfile *CSF;


Fireball 	*FBall, *FBall_UP;

//-------------------------------- result SR
distribution **G_SR_result;
distribution **G_SR_sum_result;
Base_SR	*G_SRglob;
Base_SR	*G_SRopt;
//----------------------------

Ccalc   *CTAB[Number_tab];
Ccalc   *CTAB_MC[Number_tab_MC];
Cisomer *ceIsomer[Number_tab_iso];

Ccalc  *mycalc, *mycalc2;
Cproj *beam=NULL;
C_fusion_compound *Fus_comp;
Compound *Gas_detector;
//s_spectro *liz;
s_option *opt;
s_mass   *mass;
s_me_table *BetaHalflives;
s_me_table *AlphaHalflives;
s_me_table *BranchingRatio;

s_scheme *scheme;
s_color_decay *color_decay_font;
s_color_decay *color_decay_back;
s_color_decay *color_decay_label;
s_DefRes *DefRes;

s_DataFit *DataFit;
s_DataTW  *DataTW;
s_RayFileData *RayFileData;


Creglage *regl, *aff;
Calibration calibr_TKE("MeV");

s_detv *delta;
bool RequireSave;
unsigned int RequireSaveIni1;
unsigned int RequireSaveIni2;
*/
int array_isomers[NumberGanilIsomers][3];
int   number_isomers;

//DBF *s_DBF, *s_DBI;

char *isozn, *isoDy, *iso25;
//char *ecran;
//char *file_name;
QString file_nameCfgBuffer;
QString file_nameOptBuffer;

const char *momentum_distribution[N_sigma_distr]={"[0] A.S.Goldhaber","[1] D.J.M.", "[2] W.A.Friedman", "[3] Convolution"};
const char *velocity_distribution[N_velocity_distr]={
  "Constant",
  "Calculation(V.Borrel)",
  "Calculation(Rami)",
  "Convolution",
  "from 2-body reaction",
  "Calculation(DJM)"};

const char *unit_thickness[4]={ "micron","mg/cm2","mm","g/cm2" };
//const char *unit_thicknessGraph[4]={"\u03BCm","mg<small>/cm<sup>2</sup></small>", "mm","g<small>/cm<sup>2</sup></small>"};
const char *unit_thicknessGraph[4]={"\u03BCm","mg/cm<sup>2</sup>", "mm","g/cm<sup>2</sup>"};
const char *unit_thicknessGraphBold[4]={"<b>\u03BC</b>m","<b>m</b>g/cm<sup>2</sup>", "<b>m</b>m","<b>g</b>/cm<sup>2</sup>"};
const char *unit_thicknessGraphDollar[4]={"micron","mg/cm$2$", "mm","g/cm$2$"};
//const char *unit_Lthickness[2]={{"mm","g/cm2"},{"mm","g/cm2"}};
//const char *unit_LthicknessGraph[2]={"mm","g/cm$2$"};
const char *unit_intensity[4]={"enA","pnA","pps","kW "};
const char *unit_degrader_profile[Number_Profiles]= {"Wedge degrader", "Homogeneous",  "Curved profile", "Custom shape" };
const char *unit_degrader_profile_phys[Number_ProfilesPhys]   = {"Achromatic","Monochromatic","User-defined"};
const char *unit_short_degrader_profile[Number_Profiles]= {"Wedge", "Homogns",  "Curved", "Custom" };
const char *unit_short_degrader_profile_phys[Number_ProfilesPhys]   = {"Achr","Mono","User"};

const char *char_ang_accept[2]={"ellipse","rectangle"};
const char *char_ang_accept_method[2]={"jacobian:  sqrt(ax*ay)", "projection on axis: (ax*ay) " };
const char *char_strag_ang[Number_StragAng]=
{  "0 - R.Anne et al, NIM B34 (1988) 295-308 (default)",
   "1 - Moliere et al. (ATIMA 1.2)",
   "2 - Particle Data Group, Phys.Rev.D66,10001(2002),http://pdg.lbl.gov",
   "3 - NO angular straggling   -  for deubug functions" };

const char *char_strag_ene[Number_StragEne]={
  "0 - D.Guillemaud-Mueller et al.,IEEE 33(1986)343",
  "1 - ATIMA 1.2 (LS-theory)",
  "2 - NO energy straggling   -  for deubug functions"
};

const char *YesNo[2]={"No","Yes"};

bool bad_dispersion;    // false - is good, true - is message


const char *PlotChargeState[4]={
  "only charge states",
  "all charge states separ.",
  "sum of charge states",
  "without charge states"
};

const char *PlotReactions[3]={
  "only one",
  "all reactions separ.",
  "sum of reactions"
};

const char *CharSigmaCorrection[N_sigma_corr]={
  /*"Convolution",*/
  "Coulomb energy",
  "Projectile mass"
};

const char *CharModeEnergySeparation[N_mode_separation]={
  "Energy from Qg",
  "Excitation from dSurface",
  "Excitation from Abrasion Model"
};

const char *CharModeEnergySeparationShort[N_mode_separation]={
  "Qg",
  "dSurface",
  "E*_abrasion"
};


s_flip_flop*  sdelta_start;
s_flip_flop*  sopt_state;
s_flip_flop*  sopt_sec;
//s_flip_flop*  sopt_sel_plane;




char EPAX_name_base0[] = "0 - Abrasion/Ablation v.     ";
char *EPAX_name[Number_EPAX];
const char *EPAX_name_base[Number_EPAX] = {
  "0 - Abrasion/Ablation v.     ",
  "1 - EPAX 1.00: K.Summerer et al.,Phys.Rev.C42(1990)2546",
  "2 - EPAX 2.15: K.Summerer et al.,Phys.Rev.C61(2000)034607",
  "3 - EPAX 2.15 + user modifications",
  "4 - EPAX 3.1a: K.Summerer,Phys.Rev.C86(2012)014601",
  "5 - FRACS 1.1: B.Mei,Phys.Rev.C95(2017)034608"   // [E=300MeV/u]
  //  "6 - under construction SPACS 1.e" // : C.Schmitt et al.,Phys.Rev.C94(2016)039901(E)"
};

const char *EPAX_name_short2[Number_EPAX] = {
  "0 - AA",
  "1 - EPAX 1.00",
  "2 - EPAX 2.15",
  "3 - EPAX 2.15+user",
  "4 - EPAX 3.1a",
  "5 - FRACS 1.1"
  //  "6 - SPACS 1.e"
};

const char *EPAX_name_short[Number_EPAX] = {
  "AA",
  "E1",
  "E2",
  "E2*",
  "E3",
  "Fr"
  //  "Sp"
};

const char *EPAX_name_SR[Number_EPAX_SR] = {
  "1 - EPAX 1.00: K.Summerer et al.,Phys.Rev.C42(1990)2546",
  "2 - EPAX 2.15: K.Summerer et al.,Phys.Rev.C61(2000)034607",
  "3 - EPAX 3.1a: K.Summerer, Phys.Rev.C86(2012)014601",
  "4 - FRACS: B.Mei, Phys.Rev.C95 (2017) 034608",
  "5 - Abrasion/Ablation"
};

const char *short_EPAX_name_SR[Number_EPAX_SR] = {
  "EPAX 1.00",
  "EPAX 2.15",
  "EPAX 3.1a",
  "FRACS",
  "AA"
};

const char *MassDataBase_name[Number_MassDataBase] = {
  "0 - AME2016 (database)",
  "1 - User's ME file"
};

const char *MassFormula_name[Number_MassFormula] = {
  "0 - Liquid Drop Model (regular)",
  "1 - W.D.Myers & W.J.Swiatecki, Nucl.Phys. 81(1966)1",
  "2 - LDM#1 + shell corrections 2001 (O.T.)",
  "3 - LDM#1 + shell corrections 2024 (O.T.)"};

const char *FisBar_name[Number_FisBar] = {
  "0 - \"Barfit\" - A.J.Sierk, PRC33(1986)2039",
  "1 - \"FisRot\" - S.Cohen et al.,An.P 82(1974)",
  "2 - LDM - W.Myers & W.Swiatecki,NP81(1966)",
  "3 - FILE: A.Mamdouh et al,NPA679(2001)337",
  "4 - FILE: Experimental barriers",
  "5 - FILE: P.Moller et al.,LANL-UR-08-4190",
  "6 - FILE: P.Moller et al., PRC91(2015)024310"};

const char *FisBar_name_short[Number_FisBar] = {
  "\"Barfit\" - A.J.Sierk",
  "\"FisRot\" - RLDM(Cohen)",
  "LDM (Myers & Swiatecki)",
  "A.Mamdouh et al.,NPA679",
  "Experimental barriers",
  "P.Moller ..,LANL-UR-08",
  "P.Moller ..,PRC91(2015)"
};

const char *T12_name[Number_T12] = {
  "0 - Experimental values",
  "1 - Beta decay: P.Moller et al.,ADNDT66(1997);PRC67,055802(2003)",
  "2 - Alpha decay: P.Moller et al.,ADNDT59(1995)",
  "3 - Proton decay: see Proton Radioactivty dialog"
};



const char *T12_name_short[Number_T12] = {
  "Experiment",
  "Beta decay",
  "Alpha decay",
  "Proton decay"
};

const char *T12_compiled_name[Number_T12_compile] = {
  "0 - Experimental values",
  "1 - Min (Beta,Alpha,Proton)",
  "2 - Compilation of Experiment & Min (Beta,Alpha,Proton)",
  "3 - Experimental values + notes from the Database"
};

const char *T12_compiled_name_short[Number_T12_compile] = {
  "Experiment",
  "Min(Beta,Alpha,Proton)",
  "Compilation",
  "Experiment+Notes"
};


const char *T12_alpha_name[Number_T12_alpha] ={
  "0 - database: P.Moller et al., ADNDT 59 (1995) 185-381",
  "1 - B.A.Brown, PRC 46 (1992) 811",
  "2 - A.H.Wapstra et al., Nuclear Spectroscopy Tables, North-Holland, 1959",
  "3 - K.A.Keller and H.Z.Munzel, Z.Phys.255 (1972) 419; R.Taagepera et.al.",
  "4 - Experimental half-life values"
};

const char *T12_alpha_name_short[Number_T12_alpha] ={
  "0 - database: P.Moller",
  "1 - B.A.Brown, PRC 46(1992)",
  "2 - A.H.Wapstra et al.,1959",
  "3 - K.A.Keller et al,Z.Phys.255",
  "4 - Experimental half-lives"
};

const char *T12_SF_name_short[Number_T12_spontaneous] ={
  "formula 1 [NPA759(05)64]",
  "formula 2 [NPA759(05)64]",
  "formula 3-1 [NPA759(05)64]",
  "formula 3-2 [NPA759(05)64]",
  "qMax of all above NPA759 formulas",
  "Karpov,Zagrebaev,IJMPE21(12)1250013"
};


const char *Drift_names[NumberDriftModes] ={
  "beam-line",
  "standard",
  "multipole",
  "e-quad",
  "finger"
};

const char *multipole_names[] ={
  "m-drift",  ///  field ==0 , multipole drift
  "QUADrupole",
  "SEXTupole",
  "MULTipole"
};
/*
multi_drift,
multi_quad,
multi_sext,
multi_multi
*/

const char *ConvolutionPlotNames[NumberConvolutionPlotNames] = {
  "v/v0: mean",
  "v/v0: peak",
  "FWHM*g",
  "sigma*g",
  "sigma",
  "PsigmaL*g",
  "PsigmaR*g",
  "Asymmetry",
  "SepEnergy",
  "tau"
};

const char *ConvolutionPlotDim[NumberConvolutionPlotNames] = {
  " ",
  " ",
  "MeV/c",
  "MeV/c",
  "MeV/c",
  "MeV/c",
  "MeV/c",
  "%",
  "MeV",
  "MeV/c"
};


//char Fusion_name[] = "LisFus v.       ";

QString Fusion_name[Number_Fusion] = {"LisFus v."};


const char *ELOSS_name[Number_ELOSS_PLOT] =  {
  "0 - [He-base] F.Hubert et al, AD&ND Tables 46(1990)1",
  "1 - [H -base] J.F.Ziegler et al,Pergamon Press,NY(low energy)",
  "2 - ATIMA 1.2 LS-theory (recommended for high energy)",
  "3 - ATIMA 1.2 without LS-correction",
  "4 - ATIMA 1.4 H.Weick, improved mean charge formula for HI",
  "5 - electrical component of [1] - J.F.Ziegler et al",
  "6 - nuclear component of [1] - J.F.Ziegler et al"
};

const char *ELOSS_name_add[5] =  {
  "5 - Range straggling - method [0] - LISE",
  "6 - Range straggling - method [1] - Atima",
  "7 - Lateral range - method [0] - LISE",
  "8 - Lateral range - method [1] - Atima",
  "9 - Lateral range - method [2] - PDG"
};


const char *modes_plot_axis_long[Number_AxisElementModes]={
  "Protons (Z)",
  "Mass number (A)",
  "Neutrons (N)",
  "Isospin (N-Z)",
  "Line (N-2Z)",
  "<N> / Z",
  "sum(CS); Z=const",
  "sum(CS); A=const",
  "sum(CS); N=const"
};

const char *modes_plot_axis_short[Number_AxisElementModes]={          //modes_plot_axis_short[order_x_ax []]
                                                                      "Z",
                                                                      "A",
                                                                      "N",
                                                                      "N-Z",
                                                                      "N-2Z",
                                                                      "<N>/Z",
                                                                      "sum Z=cst",
                                                                      "sum A=cst",
                                                                      "sum N=cst"
                                                           };


//const char *ExciteEnergy_name[Number_EE_models] = {
const char *ExciteEnergy_name[] = {
  "1 - J.W.Wilson et al., NIM B18 (1987) 225-231",
  "2 - J.-J.Gaimard, K.-H.Schmidt, NPA531(1991)709",
  "3 - Parametrized Gaussian distribution",
  "4 - Exponential <T> distribution",
  "5 - Log-Normal distribution",
  "6 - IME-HOLE model",
};

const char *Charges_name[Number_Charges] = {
  "0 - [ > 15AMeV] J.Winger et al.,NIM B70(1992)380; modified",
  "1 - [ >  5AMeV] A.Leon et al., AD&ND Tables 69(1998)217; modified",
  //"2 - [>5AMeV] E.Baron et al. 6th Conf. EAAB, Padova, 1992",
  "2 - [ <  5AMeV] K.Shima et al., NIM 200(1982)605-608",
  "3 - GLOBAL (>\"UB\" AMeV) + J.Winger(<30AMeV) (30-UB AMeV mixed); NIM B142(1998)441",
  "4 - GLOBAL (>\"UB\" AMeV) + A.Leon  (<30AMeV) (30-UB AMeV mixed); NIM B142(1998)441 ",
  "5 - [ < 15AMeV] G.Schiwietz, P.Grande,  NIM B175-177 (2001) 125-131"
};

const char *Short_charges_name[Number_Charges] = {
  "0-Winger",
  "1-Leon",
  "2-Shima",
  "3-GLOBAL+W",
  "4-GLOBAL+L",
  "5-Schiwietz"
};

const char *EqThick_name[] = {         // corrected in v.14.13.1
                                       "0 - \"GLOBAL\": NIM B142(1998)441",
                                       "1 - \"Charge\": NIM B142(1998)441",
                                       "2 - \"SRIM\" (Handbook of AP & E)"
                             };

const char *EDipo_name[Number_Edipo] = {
  "Cylindrical",
  "Spherical",
  "Toroidal"
};

const char *decay_name[] = {
  "Doesn't exist!",           //0
  "Stable",                   //1
  "Beta+ decay",              //3
  "Beta- decay",              //2
  "Beta+ & Beta- decay",    //4
  "Alpha decay",              //5
  "Alpha & Beta+ decay",    //6
  "Alpha & Beta- decay",    //14
  "Proton decay",             //7
  "Proton & Beta+ decay",   //13
  "Proton & Alpha decay",   //12
  "Spontaneous fission",      //8
  "SF & Beta+ decay",       //15
  "SF & Beta- decay",       //16
  "SF & Alpha decay",       //9
  "Unbound",                  //10
  "Unknown",                   //11
  "Beta- & Beta-n decay",     //17
  "Beta+ & Beta+p decay"     //18
};

// <big>&beta;<sup><b>+</b></sup></big>&nbsp;
// <big>&beta;<sup><b>-</b></sup></big>&nbsp;
// <big>&alpha;</big>&nbsp;
// <big>p</big>&nbsp;

const char *decay_nameHtml[] = {
  "Doesn't exist!",           //0
  "Stable",                   //1
  "<big>&beta;<sup><b>+</b></sup></big>&nbsp; decay",              //3
  "<big>&beta;<sup><b>-</b></sup></big>&nbsp; decay",              //2
  "<big>&beta;<sup><b>+</b></sup></big>&nbsp;  &  &nbsp; <big>&beta;<sup><b>-</b></sup></big>&nbsp; decay",    //4
  "<big>&alpha;</big>&nbsp; decay",              //5
  "<big>&alpha;</big>&nbsp;  & &nbsp; <big>&beta;<sup><b>+</b></sup></big>&nbsp; decay",    //6
  "<big>&alpha;</big>&nbsp;  & &nbsp; <big>&beta;<sup><b>-</b></sup></big>&nbsp; decay",    //14
  "<big>p</big>&nbsp; decay",             //7
  "<big>p</big>&nbsp;  & &nbsp; <big>&beta;<sup><b>+</b></sup></big>&nbsp; decay",   //13
  "<big>p</big>&nbsp;  & &nbsp; <big>&alpha;</big>&nbsp; decay",   //12
  "Spontaneous fission",      //8
  "SF  &nbsp;  & &nbsp;  <big>&beta;<sup><b>+</b></sup></big>&nbsp; decay",       //15
  "SF  &nbsp;  & &nbsp;  <big>&beta;<sup><b>-</b></sup></big>&nbsp; decay",       //16
  "SF  &nbsp;  & &nbsp;  <big>&alpha;</big> &nbsp; decay",       //9
  "Unbound",                  //10
  "Unknown",                   //11
  "<big>&beta;<sup><b>-</b></sup></big>&nbsp;  & &nbsp; <big>&beta;<sup><b>-</b></sup> n</big> &nbsp; decay",     //17
  "<big>&beta;<sup><b>+</b></sup></big>&nbsp;  & &nbsp; <big>&beta;<sup><b>+</b></sup> p</big> &nbsp; decay"     //18
};

const char *label_decay_name[] = {
  "Doesntexist",              //0  -> 0    ok
  "Stable",                   //1  -> 1    ok
  "Betap",              	//3  -> 2
  "Betam",              	//2  -> 3
  "Betap_Betam",    		//4  -> 4    ok
  "Alpha",              	//5  -> 5    ok
  "Alpha_Betap",    		//6  -> 6    ok
  "Alpha_Betam",    		//14 -> 7
  "Proton",             	//7  -> 8
  "Proton_Betap",             //13 -> 9
  "Proton_Alpha",             //12 -> 10
  "SpontFission",      //8  -> 11
  "SF_Betap",	    		//15 -> 12
  "SF_Betam",      		//16 -> 13
  "SF_Alpha",         		//9  -> 14
  "Unbound",                  //10 -> 15
  "Unknown",                   //11 -> 16
  "Betam_n",                   //11 -> 17
  "Betap_p"                   //11 -> 17
};


const char *Partial_decay_name[N_PartialDecay] = {
  "Unbound ",   //0
  "Stable  ",
  "Beta+   ",        //2
  "Beta+ p ",        //3
  "Beta-   ",
  "Beta- n ",      //5
  "Alpha   ",
  "Proton  ",        //7
  "SFission",
  "Unknown "    //9
};

/* 
NEW

    iso_Doesntexist,              //0  -> 0    ok
    iso_Stable,                   //1  -> 1    ok
    iso_Betap,              	//3  -> 2
    iso_Betam,              	//2  -> 3
    iso_Betap_Betam,    		//4  -> 4    ok
    iso_Alpha,              	//5  -> 5    ok
    iso_Alpha_Betap,    		//6  -> 6    ok
    iso_Betam_Alpha,    		//14 -> 7
    iso_Proton,             	//7  -> 8
    iso_Proton_Betap,             //13 -> 9
    iso_Proton_Alpha,             //12 -> 10
    iso_Spontaneous_fission,      //8  -> 11
    iso_SF_Betap,	    		//15 -> 12
    iso_SF_Betam,      		//16 -> 13
    iso_SF_Alpha,         		//9  -> 14
    iso_Unbound,                  //10 -> 15
    iso_Unknown                   //11 -> 16
*/

const char *web_lise[Number_LISE_web] = {
  "https://lise.frib.msu.edu/",
  "http://lise.frib.msu.edu/",
  "http://www.nscl.msu.edu/~tarasov/lisepp/",
  "http://groups.nscl.msu.edu/lise/"
  //	"http://dnr080.jinr.ru/lise/"
}  ;

const char *web_lise_version[Number_LISE_version_web] =
{
  "https://lise.frib.msu.edu/",
  "http://lise.frib.msu.edu/",
  "http://www.nscl.msu.edu/~tarasov/lisepp/",
  "http://groups.nscl.msu.edu/lise/"
};

const char *ftp_lise[Number_LISE_ftp] = {
  "https://lise.frib.msu.edu/download/"//,
  //	"ftp://dnr080.jinr.ru/lise/"
}  ;

const char *char_reactions[Number_ALLreactions] = {
  "Projectile Fragmentation",
  "Fusion -> Residual",
  "Fusion -> Fission",
  "Coulomb fission",
  "Abrasion-Fission (Low Ex)",
  "Abrasion-Fission (Mid Ex)",
  "Abrasion-Fission (High Ex)",
  "Two body reaction",
  "ISOL method",
  "Secondary Target ~1",
  "Secondary Target ~2",
  "Secondary Target ~3"
};

const char *fusion_char_reactions[2] = {
  "Fusion &rarr; Residual",
  "Fusion &rarr; Fission",
};

const char *char_reactions_short[Number_ALLreactions] = {
  "ProjFrag",
  "FusRes",
  "FusFis",
  "CoulFis",
  "AFlow",
  "AFmid",
  "AFhigh",
  "TwoBody",
  "ISOL",
  "SecTarg1",
  "SecTarg2",
  "SecTarg3"
};

const char *char_reactions_short2[Number_ALLreactions] = {
  "PF",
  "FR",
  "FF",
  "CF",
  "AL",
  "AM",
  "AH",
  "TB",
  "IS",
  "T1",
  "T2",
  "T3"
};


const char *char_secr_filtres[Number_SecR_filtres] = {
  "NO filter",
  "Corner rectangle filter",
  "Diagonal filter",
  "Corner rectangle or Diagonal filters"
};

const char *char_BeamShape1D[Number_BeamShape1] = {
  "Gaussian",
  "Gauss.(cut @ 1sigma)",
  "Rectangle uniform",
  "Ellipse uniform (proj.)"
};

const char *char_BeamShape2D[Number_BeamShape2] = {
  "Ellipse uniform",
  "Rectangle uniform",
  "Ellipse hollow",
  "Rectangle hollow"
};

const char *char_time_new_versions[Number_time_new_versions] = {
  "never",   //0
  "daily",   //1
  "weekly",  //2
  "every two weeks", // 3
  "monthly",    // 4
  "every two months",  // 5
  "every half-year",   // 6
  "yearly"             // 7
};


const char *MC_mode_chars[MC_input] =
{
  "One selected ion",
  "One selected fragment",
  "Isotope Group",
  "List of isotopes",
  "Ions rays after target"
};


const char *symb=
    "n H HeLiBeB C N O F NeNaMgAlSiP S ClArK CaScTiV CrMnFeCoNiCuZn"
    "GaGeAsSeBrKrRbSrY ZrNbMoTcRuRhPdAgCdInSnSbTeI XeCsBaLaCePrNdPm"
    "SmEuGdTbDyHoErTmYbLuHfTaW ReOsIrPtAuHgTlPbBiPoAtRnFrRaAcThPaU "
    "NpPuAmCmBkCfEsFmMdNoLrRfDbSgBhHsMtDsRgCnNhFlMcLvTsOgB9C0"
    "C1C2C3C4C5C6C7C8C9D0D1D2D3D4D5D6D7D8D9E0"  //140
    "E1E2E3E4E5E6E7E8E9F0F1F2F3F4F5F6F7F8F9F0"  //160
    "G1G2G3G4G5G6G7G8G9H0H1H2H3H4H5H6H7H8H9H0"  //180
    "I1I2I3I4I5I6I7I8I9J0J1J2J3J4J5J6J7J8J9K0"  //200
    ;


/*const*/ double el_masse[Number_Proton+1]={
  1.,
  1.00797,4.0026,6.939,  9.0122,10.811, 12.01115,14.0067,15.9994,18.9984,20.183,
  22.9898,24.312,26.9815,28.086,30.9738,32.064, 35.453, 39.948,  39.102, 40.08,
  44.956, 47.9,  50.942, 51.996,54.938, 55.847, 58.933, 58.71,   63.54,  65.37,
  69.72,  72.59,  74.922,78.96, 79.909, 83.8,   85.47,  87.62,   88.905, 91.22,
  92.906, 95.94,  98.,   101.07,102.905,106.4,  107.87, 112.4,   114.82, 118.69,
  121.75, 127.6, 126.904,131.3, 132.905,137.34, 138.91, 140.12,  140.907,144.24,
  147.,   150.35,151.96, 157.25,158.924,162.5,  164.93, 167.26,  168.934,173.04,
  174.97, 178.49,180.948,183.85,186.2,  190.2,  192.2,  195.09,  196.967,200.59,
  204.37, 207.19,208.98, 210.,  210.,   222.,   223.,   226.,    227.,   232.038,
  231.,   238.03,237.,   242.,  243.,   247.,   247.,   249.,    254.,   253.,
  256.,   254.,  257.,   260.,  262.,   265.,   267.,   270.,    272.,   275.,
  277.,   280.,  282.,   285.,  287.,   290.,   292.,   295.,    297.,   300.,
  302.,   305.,  307.,   310.,  312.,   315.,   317.,   320.,    322.,   325.,
  332.,   335.,  337.,   340.,  342.,   345.,   347.,   350.,    352.,   355.,
  358.,   360.,  362.,   365.,  368.,   370.,   373.,   376.,    379.,   382.,
  385.,   388.,  391.,   393.,  396.,   399.,   402.,   405.,    408.,   411.,
  413.,   416.,  419.,   422.,  425.,   428.,   431.,   434.,    437.,   440.,
  443.,   446.,  449.,   452.,  455.,   457.,   460.,   463.,    466.,   468.,
  471.,   474.,  477.,   480.,  483.,   485.,   488.,   491.,    494.,   497.,
  500.,   503.,  505.,   507.,  510.,   513.,   516.,   519.,    522.,   525.
};


// actual values are taken from scoef95 (Ziegler)
/*const*/ double el_densite[Number_Proton+1]={
  0.,
  .071,  .126,  .53,  1.85,  2.34,  2.26,  .81,  1.14,  1.505,  1.2,
  .97,  1.74,  2.7,   2.33,  1.82,  2.07, 1.56,  1.4,    .86,   1.55,
  3.,    4.51,  6.1,   7.19,  7.43,  7.86, 8.9,   8.9,   8.96,   7.14,
  5.91,  5.32,  5.72,  4.79,  3.12,  2.6,  1.53,  2.6,   4.47,   6.49,
  8.4,  10.2,  11.5,  12.2,  12.4,  12.,  10.5,   8.65,  7.31,   7.3,
  6.62,  6.24,  4.94,  3.06,  1.9,   3.5,  6.17,  6.67,  6.77,   7.,
  1.,    7.54,  5.26,  7.89,  8.27,  8.54, 8.8,   9.05,  9.33,   6.98,
  9.84, 13.1,  16.6,  19.3,  21.,   22.6, 22.5,  21.4,  19.3,   13.6,
  11.85,11.4,   9.8,   9.2,   1.,    1.,   1.,    5.,    1.,    11.7,
  15.4, 19.07, 19.5,   1.,   11.7,   1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.,
  1.,    1.,    1.,    1.,    1.,    1.,   1.,    1.,    1.,      1.
};

double el_densite_gas[Number_Proton+1];


const char *ElementNames[] = {
  "Neutron",
  "Hydrogen",
  "Helium",
  "Lithium",
  "Beryllium",
  "Boron",
  "Carbon",
  "Nitrogen",
  "Oxygen",
  "Fluorine",
  "Neon",
  "Sodium",
  "Magnesium",
  "Aluminum",
  "Silicon",
  "Phosphorus",
  "Sulfur",
  "Chlorine",
  "Argon",
  "Potassium",
  "Calcium",
  "Scandium",
  "Titanium",
  "Vanadium",
  "Chromium",
  "Manganese",
  "Iron",
  "Cobalt",
  "Nickel",
  "Copper",
  "Zinc",
  "Gallium",
  "Germanium",
  "Arsenic",
  "Selenium",
  "Bromine",
  "Krypton",
  "Rubidium",
  "Strontium",
  "Yttrium",
  "Zirconium",
  "Niobium",
  "Molybdenum",
  "Technetium",
  "Ruthenium",
  "Rhodium",
  "Palladium",
  "Silver",
  "Cadmium",
  "Indium",
  "Tin",
  "Antimony",
  "Tellurium",
  "Iodine",
  "Xenon",
  "Cesium",
  "Barium",
  "Lanthanum",
  "Cerium",
  "Praseodymium",
  "Neodymium",
  "Promethium",
  "Samarium",
  "Europium",
  "Gadolinium",
  "Terbium",
  "Dysprosium",
  "Holmium",
  "Erbium",
  "Thulium",
  "Ytterbium",
  "Lutetium",
  "Hafnium",
  "Tantalum",
  "Tungsten",
  "Rhenium",
  "Osmium",
  "Iridium",
  "Platinum",
  "Gold",
  "Mercury",
  "Thallium",
  "Lead",
  "Bismuth",
  "Polonium",
  "Astatine",
  "Radon",
  "Francium",
  "Radium",
  "Actinium",
  "Thorium",
  "Protactinium",
  "Uranium",
  "Neptunium",
  "Plutonium",
  "Americium",
  "Curium",
  "Berkelium",
  "Californium",
  "Einsteinium",
  "Fermium",
  "Mendelevium",
  "Nobelium",
  "Lawrencium",
  "Rutherfordium",
  "Dubnium",
  "Seaborgium",
  "Bohrium",
  "Hassium",
  "Meitnerium",
  "Darmstadtium",     //       Ds
  "Roentgenium",      //111    Rg
  "Copernicium",      //112    CN
  "Nihonium",  //113
  "Flerovium",  //114
  "Moscovium",  //115
  "Livermorium",  //116
  "Tennessine",  //117
  "Oganesson",  //118
  "Ununennium", //119
  "Unbinilium", //120
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " ",
  " "};

#endif // _DECLARE_H
