#if !defined(_MyExtern_)
  #define _MyExtern_

#if !defined(mytypes_h)
    #include "L_Init/mytypes_IsomerAPI.h"
#endif

#if !defined(Oleg_class)
      #include "L_Element/o_Element.h"
#endif

/*
#if !defined(liseStrcpyOS_h)
      #include "w_Stuff/liseStrcpyOS.h"
#endif


#if !defined(MAIN_START_H)
  #include "w_Main/main_start.h"
#endif

#if !defined(block_compound_class)
      #include "L_Block/p_Block_Compound.h"
#endif

#include "L_Block/o_Block_calc.h"


#if !defined(O_EE_C_H)
#include "o_Evap/o_EE_c.h"
#endif


#if !defined(mass_class_h)
#include "L_Mass/o_Mass_class.h"
#endif

#if !defined(GammaDetector_class)
#include "o_Phys/o_Gamma_detection.h"
#endif


#if !defined(Distr_class2_Prob)
#include "L_Distribution/o_Distr2_prob.h"
#endif
*/

//#ifndef _MPOW2
//    #define _MPOW2
//#define pow(x,y)   exp((y)*log(x))
//endif

#ifndef _MPOW
    #define _MPOW
    #define mpow(x,y)  exp((y)*log(x))
#endif

/*
extern bool   flagRecalculateGOM;
extern bool   flagCalculateEnvelopes;
//extern int    userColorMode;

extern int NP, NPsimple, NPcharge, NP_SecReaction, NPopt, NPevap, NPevapFis, NPfus_plot,NPwedge;

extern int 	 G_coef_transform;
extern int 	 G_pixelMC;
extern int 	 G_pixelMCtrans;
extern double G_CoefStragglingDecrease;
extern double G_CoefStraggK1;
extern double G_CoefStraggK2;
extern double G_ShiftTOF;
extern double BindingEnergyVV0;
extern double G_LeonD;
extern double G_LeonA;
extern double G_LeonP;

extern double G_ShiftVV0;
extern int G_SecondaryReactions;
extern double G_tweak;
extern double G_StepRangeMult;

extern s_dBE s_dBE_work, s_dBE_default;
//============================================================
//============================================================
//=============    Evaporation   =====================
extern int G_MethodApf;
extern int G_ExcitationApf;
extern int    G_ExcitationApf1_type;  // 0 - constant value mode; 1 - current AA
extern double G_ExcitationApf1_MeV;   // constant value in MeV

extern int    G_Mode_Apf_Manual;  // automode

extern double G_Energy_in_T_for_nucleus_emit;
extern int G_EvaporationVelocity;   // 0 - quality, 1 -fast
extern double G_R_Evaporation;

extern double G_DeltaOddEven;	
extern double G_DeltaOddEvenFission;	
extern double G_DeltaOddEvenFB_N;
extern double G_DeltaOddEvenFB_Z;
extern int G_CalcReaction;
extern int G_CalcReaction_stack;


extern  int G_CreateCSfile;
extern  int G_CreatePDfile;
extern  int G_MakeFullCSfile;
extern  int G_CalculateAA;
extern  int G_StateDensityMode;
extern 	int G_EvapUnstable;   //  0 - only stable
extern 	int G_Tunnelling;
extern  int G_AvoidUnboundCS;
extern  int G_ProtectedChannels;


extern 	int G_LastZevaporation;

//=============    Excitation energy   ======================
extern  double G_AA_factor;
extern 	int G_MethodEE;

     //======================================== A
     //======================================== A
extern s_GeomAA FB;
extern s_GeomAA FB_UP;

     //======================================== B
extern double G_HoleEnergy;
extern int G_HoleMethod; // 0-lin, 1-exp

//======================================== C

extern s_EE_C EE_C;
     //======================================== D
extern 	double G_MeanT, G_MeanT2, G_MeanTNZ;
extern int G_ApplyLimitingTemperature;
//======================================== E
extern double G_LN_median,G_LN_median2;
extern double G_LN_variance,G_LN_variance2;

//==================   AutoDialog ===========================

extern double G_Auto_Tun_a0;
extern double G_Auto_Tun_a1;
extern double G_Auto_Tun_a2;

extern int G_Auto_A_Bound;
extern int G_Auto_A_Pairing;
*/
//============================================================
//============================================================
//============================================================

/*
extern double SumCalc;
extern int NCALC;
extern int NCALC_MC;
extern int NCALC_MC_outside;
extern double v_prod0,G_Sigma0,G_SigmaD,G_SigmaM,calcthres;
extern int SSx,SSy,SSw,SSh;
extern int n_opt,j_opt,i_opt[]; //,on_erreur;
extern int CalculateEnergyDistribution;
extern double Qtab_global[Number_Proton];  //  for charge state distribution

extern distribution **G_SR_result;
extern distribution **G_SR_sum_result;

extern distribution *ConvMomentum;
extern distribution2P *MoyalDistr;
extern distribution2P *EllipseDistr;
extern CSfile *CSF;

//----------------------------
extern Compound *cp_tab[NumberTabELOSS];
extern Calibration calibr_TKE;

extern BLOCK_Cible     *Cible;
extern BLOCK_Stripper  *Strip;

extern double EPAX_p_Norm;
extern double EPAX_p_Un;

extern double EPAX_p_Up0;
extern double EPAX_p_Up1;
extern double EPAX_p_Up2;

extern int EPAX_p_H_corrections;


extern BEAM    beam_vector;
extern BEAM    OptBeam_vector;
extern BEAM    ray_vector;
extern OPTICAL_MATRIX  MG;
extern CalcBlock  *CalcBLOCK;

extern Ccalc *CTAB[Number_tab];
extern Ccalc *CTAB_MC[Number_tab_MC];

extern Cproj *beam;
extern C_fusion_compound *Fus_comp;

extern Compound *Gas_detector;
*/
extern s_option *opt;

/*
extern s_mass   *mass;
extern s_me_table *BetaHalflives;
extern s_me_table *AlphaHalflives;
extern s_me_table *BranchingRatio;
*/
extern s_scheme *scheme;
extern s_color_decay *color_decay_font;
extern s_color_decay *color_decay_back;
extern s_color_decay *color_decay_label;


extern s_DataFit *DataFit;
extern s_DataTW  *DataTW;
//extern Creglage *regl,*aff;
extern s_detv *delta;

extern s_DefRes *DefRes;

extern bool RequireSave;

extern const char *momentum_distribution[];
extern const char  *velocity_distribution[];
extern const char *unit_intensity[];
extern const char *unit_thickness[];
extern const char *unit_thicknessGraph[];
extern const char *unit_thicknessGraphBold[];
extern const char *unit_thicknessGraphDollar[];

extern const char *unit_degrader_profile[];
extern const char *unit_degrader_profile_phys[];

extern const char *YesNo[];
extern const char *char_ang_accept[];
extern const char *char_ang_accept_method[];
extern const char *PlotChargeState[];
extern const char *PlotReactions[];
extern const char *CharSigmaCorrection[];
extern const char *CharModeEnergySeparation[];
extern const char *char_reactions[Number_ALLreactions];
extern const char *char_reactions_short[Number_ALLreactions];
extern const char *char_reactions_short2[Number_ALLreactions];
extern const char *FisBar_name[];
extern const char *FisBar_name_short[];
extern const char *T12_name[];
extern const char *T12_name_short[];
extern const char *T12_compiled_name[];
extern const char *T12_compiled_name_short[];
extern const char *T12_alpha_name[];
extern const char *T12_alpha_name_short[];
extern const char *T12_SF_name_short[];
extern const char *MC_mode_chars[];


extern const char *web_lise[Number_LISE_web];

extern bool bad_dispersion;    // false - is good, true - is message
extern bool FusionCompoundCheck;
extern bool opt_fast_epax;

//extern s_GammaDetector *GammaDet;


extern char *isozn,*isoDy,*iso25;
extern const char *symb;
extern const char *ElementNames[];

extern QString file_name;
extern QString file_nameCfgBuffer;
extern QString file_nameOptBuffer;

extern int G_LastZ_ask;
extern int G_LastZ_value;
extern bool GlobalBreak;

extern const char *decay_name[];
extern const char *decay_nameHtml[];
extern const char *Partial_decay_name[];

extern bool FlagPrintToFile;

extern bool WinLog;
extern char *EPAX_name[Number_EPAX];
extern const char *EPAX_name_short[Number_EPAX];
extern const char *EPAX_name_SR[Number_EPAX_SR];
extern const char *short_EPAX_name_SR[Number_EPAX_SR];
extern QString Fusion_name[Number_Fusion];
extern const char *Charges_name[Number_Charges];
extern const char *char_strag_ang[Number_StragAng];
extern const char *char_strag_ene[Number_StragEne];
extern const char *modes_plot_axis_long[Number_AxisElementModes];
extern const char *modes_plot_axis_short[Number_AxisElementModes];
extern const char *MassFormula_name[Number_MassFormula];
extern const char *MassDataBase_name[Number_MassDataBase];
extern const char *Drift_names[NumberDriftModes];
extern const char *EDipo_name[Number_Edipo];

extern s_flip_flop* sopt_state;
extern s_flip_flop* sopt_sec;
extern s_flip_flop* sdelta_start;

extern int VelocityExceed;   // if velocity two-body reaction low than Borrel velocity
//================================================== more distributed functions

extern void kill_zero(char*, char fill);
extern void CmLISEsiteLink(QString str);
extern void CmGlobalSiteLink(QString str);

extern void PutSaveIniFile1(unsigned int v);
extern void PutSaveIniFile2(unsigned int v);
/*
extern double round_decimal(double v, int sign);
*/
extern double pow2(double par);

extern bool set_limits(double x, double &xmin, double &xmax);
extern void SetCalcReaction();
extern void AddCalcReaction(int react);
extern void ClearCalcReaction(int react);
extern bool IsCalcReaction(int react);
extern void CheckCalcSetReaction();


extern void		BZERO(double* X, int n);
extern void		BZERON(double* X, int n);
extern void		BZERO(int* X, int n);
extern void		BZERON(int* X, int n);


extern void		BSET(double* X, double Y, int n);                  // in - destination, out - source
extern void		BSETN(double* X, double Y, int n) ;

extern void		BSET(int* X, int Y, int n);
extern void		BSETN(int* X, int Y, int n);

extern void		BCOPY(double* in, double* out, int n);
extern void		BCOPY(double* in, const double* out, int n);
extern void		BCOPY(int* in, int* out, int n);

#endif
