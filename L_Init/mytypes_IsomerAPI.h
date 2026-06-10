#if !defined(mytypes_h)
	#define  mytypes_h

#include <QRegularExpression>
// MSVC #pragma warning(disable : 5208)

#if !defined(constant_h)
#include "L_Init/Constant.h"
#endif

/*#include "o_Phys/o_Slits.h"
#include "L_Block/o_Matrix_optics.h"
#include "o_Fission/o_Fission_shell.h"
*/
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
typedef struct  s_range_
{
short int    z;
short int    m;
double r[MaxZtargetHubert];
} s_range;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
typedef struct  _Elab_Ecm_Fuf_ {
  double ElabA;
  double Ecm;
  double Ex;
  double Capture;
  double CS;        //fusion      CS = Captrue* PCN
  double ElabRegl;
  double ChargeRegl;
  double CSbreakup;
  double CSfission;
  double CSresidue;  // fusion- CSbreakup - CSfission
  double PCN;
} _Elab_Ecm_Fuf;


//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
typedef struct s_DI_field_
{
int ErrorCell;
const char *format;
const QRegularExpression  *validation;
const char *init_value;
void init(int Ei, const char *f, const QRegularExpression *v, const char *iv)
		{
            ErrorCell = Ei;
            format=f;
            validation=v;
            init_value =iv;
            };
}
s_DI_field;


//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct  s_DefRes_ // !
{
int    defect_procent_mm;  // 0  - procent, 1 - mm
double defect_value[2];

int Eres_procent_MeV;
double Eres[2];   // 0 - procent, 1-MeV

double Tres;
double Xres;
double Yres;

void init(int i1, double d1a, double d1b,
		  int i2, double d2a, double d2b,
		  double d4, double d5, double d6)
		{
		defect_procent_mm=i1;
		defect_value[0]=d1a;
		defect_value[1]=d1b;
		Eres_procent_MeV = i2;
		Eres[0]=d2a;
		Eres[1]=d2b;

		Tres = d4;
		Xres = d5;
		Yres = d6;
		};
} s_DefRes;
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_option_
{
int reaction;
int log;
int state;
int state_after_reaction;
int plot_charge_state;  // 2 - sum, 1 - all ; 0 - determinate
int plot_reaction;      // 2 - sum, 1 - all ; 0 - determinate
int plot_all_isotopes;   // 1 - all , 0 - just one selected
//int colorMode; // 0 - Light/ 1 - dark
//int blackwhite;
//int fill_circle;
//int u_ep;
//int u_in;
int util;
int iutil;
int CrossSection_FitFile;  // before it was "_sec"
double display;
int animation;
int navigation;
int scattering;
int delta_peak;
int AA_show;
int CS_plot;
int SchemeLocation;
int showDisable;
int AngStragInOptics;

//int Z_scat_target;
int sound;
int ionization;
int disp[2];
//double scat_percentage;
int ShowFit;
int ShowDrift;
int PermitShowDrift;

double threshold;

int useChargeCashe=1;
int useELossCashe =1;

int *dq;
int NumQ;
int BrhoMaxMean;  // 0 - qMax, 1 -mean
int BrhoMaxMeanLeftRight;  // 0 - qMax, 1 -mean, 2- left, 3 -right  for fission
double BrhoTuneShift=0; // in %
int centralCut; // 0 - no, 1 - moderate, 2 - strong
//int Brho_0_slits;   //  0 - set to 0, 1 -set to middle
int charge;
int vv0;
int v_sigma; // 0 - golhaber, 1- morrissey, 2 - friedman,  3 - convolution,
int v_symmetry; // 1 -yes, 0 - no. for fragmentation symmetric around Aprojectile/2
double asym_sigma; // asymmetry value  -100  -  +100  
int v_Pfaff;    // 1 -yes, 0 - no. for pick-up reaction
int v_Pfaff_ChargeExchange;    // 1 - exculde, 0 - include

int sigma_corr[N_sigma_corr]; // 0 without correction,  1 - correction
					// 							   0 - coulomb
					//     						   1 - projectile mass
int RamiApf;				// prefragment option for Rami velocity calculations

int FriMode;				// 0 - Qgg, 1 - Surface, 2 - Qgg + Surface
int FriApf;				      // prefragment option for Friedman width calculations
int FriColoumb;				// take coulomb for Frieman

int ConvMode;				// 0 - Qgg, 1 - Surface, 2 - Qgg + Surface
int ConvUseGaussian;               // use Gaussian model if Separation energy <=0
double SigmaConvolution[N_mode_separation];
double CoefConvolution[N_mode_separation];
double ShiftConvolution[N_mode_separation];

int BarrierShape;  // 0 - classical /  1- quantum-mechanical
double  h_omega;  // for quantum-mechanical barier
int P_CN;  //  option to take into account the probability for compound nucleus formation P_CN (E,l)
int Fusion_ApplyBarrierVanish;
int Fusion_BarrierVanishMode;
int Fusion_NuclPotentialMode;
double WS_V0;
double WS_R0;
double WS_a;
double Fusion_Diffuseness;

double FingerDiffuseness;
double FingerSuppression;

double BarFac;    // for fission barrier coefficient

int EPAX;
int EPAX_SR;
int Eloss;

int CutEdgeEffect;     // 1 - like for older 9.2.32, 0 - no  for extended configurations
int angle_target_stripper;
int spline_opt;
int CheckCfgFiles;
int CheckOptFiles;
int ShowLab;

int strag_ang;   // 0 - LISE ; 1 - ATIMA; 2 - nothing
int strag_ene;   // 0 - LISE ; 1 - ATIMA;  3 - nothing
int strag_ene_method; // 0 - integration, 1 - table
int strag_ene_shape;  // 0 - Gaussian, 1 - Moyal (Vavilov-Landau)
int equil_thickness; // 0 - Charge, 1 - Global, 2-SRIM
int UseChargeForEnergy; // 0 - Not , 1 - Yes , 2 Auto
double EnergyValueForChargeAuto;

int useHybridModel; // 0-no, 1-yes
double kHybrid=2; // k -- n of sigma to start exponent in hybrid model
//temporary
//int ang_accept_shape;   //  rectangle/gaussian
//int ang_accept_method;  //  0- jacob and production of sqrt; 1 - projection on axis


// v.16.2.4 int TurnPlotTitleY;   // turn Y-title on 180 degrees! if = 1
// v.16.2.4 int TurnScreenTitleY;

int PrintRatesPlot;   // 1-print, 0-no
double K_Morr;
double K_Morr_Half;

int FisAngDistShape; // 0 - isotropic; 1 anisotropic      (default 0)
int FisMomCutForAngDist; // 0 - dont use; 1 - use just MatrixKinematics; 2 - use for all; (default 2)
int FisOddEvenCorrections;  // 1-use, 0 - don't use
int FisPostScissionEvaporation;  // 1-use, 0 - don't use
int FisDeexcitFunctionPoints;   //  0 - 1 point,  1 - 3  points, 2 - manually, 3 - GraphMode
double FisEXmanually;
double FisCSmanually;
double FisSuppressionValueGlobal;
double FisSuppressionValueTKE;
int FisTXEmethod;   // 0 - Dissipation; 1 - Q-value
double Fis_f; // 0.0045
double FisBeta1;
double FisBeta2;
double FisTKE_d;
int FisBetaFit; // 0 - manual; 1 - fit
double FisEXsigma;
int FissionBarrierMode;
int FisBarShellCorrections; // 0- no, 1 -yes
int FisBarOddEvenCorrections; // 0- no, 1 -yes
int FB_InOutMax;  // 0 - in, out - 1 , qMax  -2
int FissionBarrierModeForUser;

double BreakupTemperatureA050;
double BreakupTemperatureA150;
double BreakupTemperatureA250;
double BreakupDiffuseness;

int DissipationKramers;       // 1-use, 0- no
int DissipationStepFunction;  // 1-use, 0- no
double DissipationBeta;		// default 2

int AF_HML;     //  111 - show high, medium, show low
int AF_velocity;  // 0- do not use, 1 - use
double AF_Eboundary1;
double AF_Eboundary2;
double AF_Zb_coef;
double AF_Nb_coef;
double AF_CSthreshold;
int AA_fast;  // 0 - no, 1 - yes
int AA_fastMode;  // 0,1,2,3; default 3
int AF_Ex_choice;  // 0 - AA, 1 - weighted

double RadiusProtonActivity;
int L_1p_emission,L_2p_emission;
int UseProtonActivity; // 0 - both, 1- 1p, 2 - 2p
int CodeProtonActivity; // 0 - tunneling  1 - p_orig.for
int UseAlphaDecayModel;
int UseSpontaneousFissionModel;

int CodeCluster; // 0 - tunneling  1 - p_orig.for
double RadiusClusterActivity;
//int L_cluster_emission;
int Zcluster;
int Acluster;

int ShowIsomers;
int ShowUnbound;
int ShowUnknown;
int ShowDiscoveryHistory;
int IncludeUnboundForSearch;
double HalflifeThresholdUnbound;
double HalflifeThresholdStable;
double DecayBranchRatio;

//FissionShell Fishell[2];
double FisNwidth;
double FisKappa;  //κ (kappa) controls how much extra excitation energy the light fragment


int EquilibriumMode;  // 0 - Equilibrium / 1 - nonequilibrium
double UB_Global;     //  Upper boundary for GLOBAL
int    MinZ_Global;
int OptimTarget; // mode 0-3    one, all, one+sr, all+sr
int ShowTime;
int ChargeStateOptimimzation;
int ShowChStOptim;

int MC_strag_ang;
int MC_strag_ene;
int MC_strag_lat;

int MC_ETresolution;
int MC_XYresolution;
int MC_RadialSign;    // 0 - no changes, 1 - Ang & Rad,  2 - as 1 + Theta and Phi

int MC_defect;
int MC_charge;
int MC_loss_reaction;

int MC_reaction_ang;
int MC_reaction_mom;
int MC_ang_acceptance;
int MC_dp;     // 0 : dP/P0  COSY;  1 : dPz/P0 transport

int MC_HighOrder;
int MC_CS_use;   // 0 - do not use, 1 - use
int MC_3D;       // 2D - 0 , 3D - 1
int MC_3D_path; // 0 - default, 1 - with dipoles
int MC_EnvelopeRandomizer;

int MC_envelope_show_all;
int MC_use_bore_for_transmission;
int MC_XY_orientation;   //  0 - Absolute, 1 - LISE++ internal
int Plot_XY_orientation;   //  0 - Absolute, 1 - LISE++ internal
int MC_reverseFlag; // 0-default, 1 - yes

double MC_AZQ_Xsigma;
double MC_AZQ_Ysigma;

int MC_outside_cikl;
int MC_outside_sigma;
int MC_Zaxis_material;

int WedgeCuriosity_Order;           // 1, 2, 3  (if order 2 + corerection for derivative = 0)
int WedgeCuriosity_IntensityShift;  // 0 or 1

double Gpp_Estart;
double Gpp_Epickup;
double Gpp_Eabrasion;
double Gpp_Width;
double Gpp_lambda;
int Gpp_mode;  // see gpp_enum
int Gpp_CS;


int envXY;
int envL;
int envMat;
int envDim;
int envDiag;
int envQuad;
int envMaterial;

int adjustSlits_plane;
int adjustSlits_position;
int adjustSlits_width;
int adjustSlits_mode;


double RR_AbsErr;  // radiation residues
double RR_RelErr;  // radiation residues
double RR_Y_threshold;  // radiation residues
int RR_model;           // radiation residues
int RR_NI; 			// radiation residues
int RR_NF; 			// radiation residues
int RR_Nplot;		// radiation residues  number 1d to plot
int RR_IsoPlot;		// radiation residues  isotopes to plot
double RR_T12min;
double RR_T12max;
int RR_2Dplot;         //  Z vs N, Z vs N-Z, Z vs N-2Z
int RR_Law;  // 1 : 0


}
s_option;
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
typedef struct Struct_Datetime_
{
int iyr;
int imon;
int iday;
int ihour;
int imin;
int isec;
int ihund;
double secs;
} Struct_Datetime;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_DataFit_
{
double Emin;
double Emax;
int E_N;

double Smin;
double Smax;
int S_N;
int n_variables;

double coef[4];
int Divide;
int UseCSerror;
double errFactor;
} s_DataFit;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_dBE_
{
double k0;
double k1;
double k2;
double temperature;
double b0;
int use_dSp;

int N=0;   // result
double chi2=0; //result
} s_dBE;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
typedef struct ExperimentalPoint_
{
double x;
double y;
double ex;
double ey;
double xi;   ////  this parameter for fluctuations
double yi;   ////  this parameter for fluctuations
void init_ExperimentalPoint(){x=y=ex=ey=xi=yi=0;};
}  ExperimentalPoint;


//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_DataTW_
{
double Tmin;
double Tmax;
int T_N;    	     //default

double Wmin;
double Wmax;
int W_N;               //default

double W2min;
double W2max;
int W2_N;               //default

int dP;                //default
int dN;                //default

double coef[3];        //default

int DataTWmode;   // 0 - TargetWedge, 1  - WedgeWedge

int KeepValue;          // 0
int WedgeBlock;		// 0
int WedgeBlock2;		// 0

int PrimaryBeam;   // 0 or 1  default
int AngleCalc;  // 0  - calcul, 1-scaling

void *bo;
void *bo_Kicker;
} s_DataTW;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_scheme_
{

int work;
double angle;
int width;
int height;
int margin;
int bckgrnd;

unsigned long target;
unsigned long stripper;
unsigned long dipole;
unsigned long ed;
unsigned long quadro;
unsigned long wedge;
unsigned long wien;
unsigned long material;
unsigned long drift;
unsigned long slits;
unsigned long rotate;
unsigned long shift;	  //  v.9.6.113
unsigned long selected;
unsigned long gns;
unsigned long D6;
unsigned long FC;
unsigned long Kicker;     //  v76
unsigned long Buncher;     //  v9.4.21
unsigned long Solenoid;   //  v83
unsigned long Delay;      //  v8.3.142
unsigned long Fit;      //  v9.8.78
unsigned long disable;
} s_scheme;


typedef struct s_color_decay_ {
unsigned int  cso[N_DecayString];
} s_color_decay;


typedef struct s_detv_
{
char pos[5];
char pos2[5];
char start_TOF[5];
char stop_TOF[5];
//char pos_Brho[5];
//char pos_Wedge[5];
char pos_X[5];
char pos_X2[5];
char pos_Y[5];
char pos_TKE[5];
char pos_RO_Tilting[5];
char pos_RO_Stopper[5];
char pos_RO_Wedge[5];
char pos_Condition[5];
int UseCondition;
int start;
//double HF_resolution;    9.4.18  use beam->bunch
int HF_diviser;
int ident;
double seuil;
}
s_detv;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
typedef struct s_GeomAA_
{
   int AbrasionModel; // 0-Geometrical, 1-Exponential

      int    GeomCorrection; //  1 - use - default
      int    Thermalization; //1-yes, 0 - no
      int    Pickup;
      double ThermaTimeCoef; // 3e-23

	double A_SigmaCoef;  // model 0

	double FactorCoef1;
	double FactorCoef2;

	int    Friction;
	double FrictionCoef1;
	double FrictionCoef2;

      double G_Surface;
      double AbraExpSlope;

}
s_GeomAA;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct tab_seuil_
{
double seuil;
int couleur;
}
tab_seuil;
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_fit_options_
{
double opt[5];
int N;
int UseBounds;
int example;
int dN_cycle;
int Eval_cycle;
int UseDSCL;
}
s_fit_options;


//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

typedef struct s_flip_flop_
{
int* opt;
int  value[2];
const char *string_f[2];
void init(int*i1,int i2,int i3,const char*i4,const char*i5)
		{ opt=i1; value[0]=i2; value[1]=i3; string_f[0]=i4; string_f[1]=i5;};
}
s_flip_flop;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

struct time_interval {
	const char *char_time;
	double interval;
	};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum VV0_type {
vv_Constant,
vv_Borrel  ,
vv_Rami    ,
vv_Convolute,
vv_TwoBody,
vv_VMorr
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Vsigma_type {
vs_Goldhaber,
vs_Morrissey,
vs_Friedman,
vs_Convolute
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Valpha_type {
va_Moller,
va_Brown,
va_Waapstra,
va_Taagepera
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Vcharge_type {
vc_Winger,
vc_Leon,
vc_Shima,
vc_GlobalW,
vc_GlobalL,
vc_Schiwietz
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Vseparation_type {
vs_Qgg,
vs_Surface,
vs_Total
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
enum Vangular_strag_type {
vas_LISE,
vas_ATIMA,
vas_PDG,   // Particle data group  pdg.lbl.gov
vas_nothing
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Venergy_strag_type {
ves_LISE,
ves_ATIMA,
ves_nothing
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Venergy_loss_type {
vs_Hubert,
vs_Zigler,
vs_Atima,
vs_AtimaWT,
vs_Atima14
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Save1_type {
save_Preference,  //0
save_Plot,
save_Calculation,
save_Evaporation,
save_EvapAuto,     //4
save_Excitation,
save_Mechanism,
save_Fragmentation,
save_Friedman,        //8
save_Convolution,
save_Internet,
save_MSP144,
save_SchemeOptions,      //12
save_SomeOptions,        // -----------  is not used this
save_Fusion,
save_FissionProperties,
save_CoulombFission,      //16
save_AbrasionFission,
save_CS_file,
save_ChargeSuppression,
save_FisCS_Suppression,    //20
save_FissionBarrier,
save_SecReactions,
save_DataFit,
save_TargetOptimizationOptions,//24
save_DataTW,
save_GammaDetector,
save_SecTarget,
save_MC_options,                //28
save_Pickup_options,		  //29
save_RayFile_options          //30
};
//========================================

enum Save2_type {
save2_Levmar_options,
save2_RadiationResidues,
save2_RadiationResiduesOptions,
save2_AdjustSlits,
save2_BeamDump,
save2_FRACSoptions,
save2_SPACSoptions,
save2_IMEparams
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Reaction_type {   // total 12
react_Fragmentation,  // 0
react_FusionResidual,
react_FusionFission,  //2
react_CoulombFission,
react_AbrasionFissionLow, //4
react_AbrasionFissionMid,
react_AbrasionFissionHigh, //6
react_Twobody,
react_IonSource,          //8
react_SecondaryTarget1,
react_SecondaryTarget2,   //10
react_SecondaryTarget3
};

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Tunnelling_mode_type {
vs_auto,
vs_manual
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Optimum_target_mode_type {
vs_one,
vs_all,
vs_one_sr,
vs_all_sr
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum Eq_target_mode {
ve_Global,
ve_Charge,
ve_Srim
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--


enum modes_type_plot_axis{
pa_Z,
pa_A,
pa_N,
pa_NZ,
pa_N2Z,
pa_NdZ,    //  <N>/Z
pa_suZ,    // Z=const
pa_suA,     // A=const
pa_suN    // N=const
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

///   #define  NumberBLOCKs	    18  look at constant

enum BlockNames {
  eTarget,
  eStripper,
  eWedge,
  eMaterial,
  eFaraday,

  eDipole,
  eWien,
  eDrift,
  eRotate,
  eShift,  // v.9.6.113
  eED,
  eGFS,
  eD6,
  eKicker,        // v76
  eBuncher,        // v9.4.21
  eSolenoid,		// v83
  eDelay,		// v8.3.142
  eFit,		// 9.10.78        N=18
  eMultipole,	// 9.10.134   only for BlockPlotPosition -- it's not in NumberBLOCKs
  eFinger	      // 17.11.25   only for BlockPlotPosition -- it's not in NumberBLOCKs
};

//!!!!!   PAY ATTENTIN FOR THE NEW BLOCK @  static int NcalcArray[NumberBLOCKs]
//  o_CalcBlock_add.h

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--


enum su_n_iso {
   sui_simple,
   sui_charges,
   sui_reaction,
   sui_charges_reaction,
   sui_simple_maximum
   };

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--

enum pr_KindDegrader {     // kind of degrader
   pr_Wedge,
   pr_Homo,
   pr_Curved,
   pr_Custom
   };

enum prp_ProfileMode {     // desirable mode
   prp_Achr,
   prp_Mono,
   prp_User,  // or Polynom
   prp_File
   };

enum nm_db {
	db_S1n,
	db_S2n,
	db_S1p,
	db_S2p,
	db_Qa,
	db_Beta,
     	db_BetaP,
	db_T12,
	db_ME,
	db_BE,
	db_BE_A,
	db_Sd,
	db_S3he,
	db_St,
      db_Stability,
      db_StabilityC,
      db_Min,
      db_Dn,
      db_Dno,
      db_Dne,
      db_Dna,
      db_Dnb,

      db_Dp,
      db_Dpo,
      db_Dpe,
      db_Dpa,
      db_Dpb,

      db_Dnb_Dpb,

      db_Pn3,
      db_Pp3,
      db_Pd3,
      db_Pn4,

      db_FermiP,
      db_FermiN,
      db_FermiDelta,

      db_GroundState
};

enum nm_di {
	di_EG,
	di_IT,
	di_T12,
	di_LE,
	di_JPI,
	di_IG,
	di_MG,
	di_MR,
	di_CC,
	di_SOURCE,
      di_NAME
	};

enum fb_db {
	fb_Sierk,
	fb_Cohen,
      fb_Myers,
      fb_Mamdouh,
      fb_exp,
      fb_Moller08,
      fb_Moller15
      };

enum secr_db {
	secr_opt,
      secr_all,
      secr_plot
      };

enum secr_filt {
	secf_no,
      secf_rect,
      secf_diag,
      secf_both
      };

enum AFN_names {
	afn_low,
      afn_mid,
      afn_high,
      afn_EM
      };

enum plt_output {
	plt_one,
      plt_all,
      plt_sum
      };

enum da_enum{
  da_stable,
  da_1n,
  da_2n,
  da_1pCB,
  da_2pCB,
  da_1p,
  da_2p,
  da_alpha_nobound,
  da_alpha_decay,
  da_betam,
  da_betap
  };

enum iso_enum{
	iso_Doesntexist,              //0  -> 0    ok
      iso_Stable,                   //1  -> 1    ok
	iso_Betap,              	//3  -> 2
	iso_Betam,              	//2  -> 3
	iso_Betap_Betam,    		//4  -> 4    ok
	iso_Alpha,              	//5  -> 5    ok
	iso_Alpha_Betap,    		//6  -> 6    ok
	iso_Alpha_Betam,    		//14 -> 7
	iso_Proton,             	//7  -> 8
      iso_Proton_Betap,             //13 -> 9
      iso_Proton_Alpha,             //12 -> 10
	iso_Spontaneous_fission,      //8  -> 11
	iso_SF_Betap,	    		//15 -> 12
	iso_SF_Betam,      		//16 -> 13
     	iso_SF_Alpha,         		//9  -> 14
     	iso_Unbound,                  //10 -> 15
     	iso_Unknown,                   //11 -> 16
     	iso_Betam_neutron,             //11 -> 16
     	iso_Betap_proton
      };

enum Pdecay_enum{
	pd_Unbound,
      pd_Stable,
	pd_Betap,
	pd_BetapP,
	pd_Betam,
	pd_BetamN,
	pd_Alpha,
	pd_Proton,
	pd_SF,
     	pd_Unknown
      };

enum  DecayArrayEnum {
  dr_betam,
  dr_betap,
  dr_proton,
  dr_alpha,
  dr_SF
  };

enum  TI_enum 	{
      tie_ys,         //-1       03/06/2013
      tie_zs,         //0
      tie_as,
      tie_fs,
      tie_ps,
      tie_ns,
      tie_us,
      tie_ms,
      tie_sec,          //7
      tie_m,
      tie_h,
      tie_d,
      tie_y,
      tie_ky,
      tie_My,           //13
      tie_Gy,
      tie_Ty,
      tie_Py,
      tie_stable,      //17
      tie_unbound,
      tie_unknown,
      tie_private
      };

# define StableTIpostion tie_stable

enum gd_enum
	{
	gd_area,
	gd_dist,
	gd_eff
	};


enum MC_enum {   // MC_RB
mc_X,      //0
mc_T,
mc_Y,
mc_P,      //3
mc_D,      //4
mc_R,
mc_A,
mc_E,      //7
mc_TKE,
mc_M,
mc_Brho,
mc_Erho,

mc_Envelope, //12
mc_Loss,

mc_Range,

mc_Deposition,

mc_TOF,         //16
mc_Length,


mc_V,           //18
mc_Vz,
mc_Vx,
mc_Vy,
mc_Vxy,         //22
mc_Beta,
mc_Gamma,
//---------------------------------
mc_Mass,       //25
mc_Ad,
mc_Z,
mc_N,
mc_Q,

mc_ZmQ,
mc_AoQ,
mc_Am2Q,
mc_Am3Q          //33
};

enum MC_RB_enum {   // MC_RB
mcRB_X,      //0
mcRB_T,
mcRB_Y,
mcRB_P,      //3
mcRB_D,      //4
mcRB_R,
mcRB_A,
mcRB_E,      //7
mcRB_TKE,
mcRB_M,
mcRB_Brho,
mcRB_Erho,

mcRB_Envelope, //12
mcRB_Loss,

mcRB_Range,

mcRB_Deposition,

mcRB_TOF,         //16
mcRB_Length,

mcRB_V,           //18
mcRB_Z
};

enum MC_FILE_enum {      // MC_RB_files
mcf_X,		//0
mcf_T,
mcf_Y,
mcf_P,
mcf_D,
mcf_R,
mcf_A,
mcf_E,
mcf_TKE,
mcf_Mom,
mcf_Brho,
mcf_Erho, //11

mcf_Length, //12
mcf_Time,
mcf_Eloss,
mcf_Range,
mcf_Reaction,
mcf_CS, //17
//----

mcf_V,           //18
mcf_Vz,
mcf_Vx,
mcf_Vy,
mcf_Vxy,         //22
mcf_Beta,
mcf_Gamma,         //24

mcf_Mass,	//25
mcf_Ad,
mcf_Z,
mcf_N,
mcf_Q,

mcf_ZmQ,
mcf_AoQ,
mcf_Am2Q,
mcf_Am3Q,	//34
//----
mcf_Zbegin,
mcf_Zend,
mcf_empty
};

enum MC_separators {
mcs_tab,
mcs_semicolon,
mcs_comma,
mcs_space
};

enum MC_inputs {
mci_ion,
mci_fragment,
mci_calc,
mci_list,
mci_outside
};




enum MO_enum {
mo_X,
mo_T,
mo_Y,
mo_P,
mo_L,
mo_D
};

enum Gpp_mode {
gpp_none,
gpp_proton,
gpp_neutron,
gpp_both
};

enum ConvPlotsNum {
eCP_vv0_mean,
eCP_vv0_peak,
eCP_FWHMg,
eCP_sigmag,
eCP_sigma,
eCP_PsigmaLg,
eCP_PsigmaRg,
eCP_Asymmetry,
eCP_SepEnergy,
eCP_tau
};


enum en_SpontFission{
eSF_f1,
eSF_f2,
eSF_f3_1,
eSF_f3_2,
eSF_max,
eSF_Karpov
};


enum ED_bend_type {
bend_cyl,
bend_sph,
bend_tor
};


enum EffLengthErrors {
effL_good,
effL_negative,
effL_nopreceding_drift,
effL_nopreceding_drift_standard,
effL_nofollowing_drift,
effL_nofollowing_drift_standard
};


enum enum_GetSubMenu {
subm_file,
subm_options,
subm_experiment,
subm_mechanism,
subm_calculations,
subm_utilities,
subm_1Dplot,
subm_2Dplot,
subm_databases,
subm_help
};

enum enum_cmplot2
{
CM_PLOT_DE_TOF	,
CM_PLOT_TKE_TOF	,
CM_PLOT_DE_TKE  ,
CM_PLOT_DE_DE2  ,
CM_PLOT_DE_X    ,
CM_PLOT_DE_Y	,
CM_PLOT_TKE_X   ,
CM_PLOT_TKE_Y	,
CM_PLOT_TOF_X	,
CM_PLOT_TOF_Y   ,
CM_PLOT_X_Y     ,
CM_PLOT_X_X2    ,
CM_PLOT_RANGE_X ,
CM_PLOT_Z_AQ	,
CM_PLOT_Q_AQ	,
CM_PLOT_Z_AM2Q	,
CM_PLOT_Z_AM3Q  ,
CM_PLOT_Q_AM3Q,
CM_PLOT_X_AQ
};



//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
enum enum_askZ {
	eask_nocalculate_noask,    // ignore always
      eask_ask_always,           // regular
      eask_ask_once,		   // excitation fucntion , optimum plot  i=0
	eask_calculate_noask       // excitation fucntion , optimum plot  i>0
      };
#endif
