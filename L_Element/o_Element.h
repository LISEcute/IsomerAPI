#if !defined(Oleg_class)
#define  Oleg_class

#if !defined(constant_h)
#include "L_Init/Constant.h"
#endif

#include "L_Init/L_ValueErr.h"

#include <QString>

#define size_NameElement  800

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


class Compound;

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

class Celement
{
  friend class  Creglage;
  friend class  Cproj;
  friend class  Compound;
  friend class  Selement;


private:
  int   z;
  int   n;
  int   a;  // number of nucleons
  int   q;


public:			//=============================
  Celement (int z_init=14, int n_init=-1, int q_init=-1, bool Verify_init=true);
  Celement (const Celement *Ce_init);

#ifndef IsomerAPI_case
  Celement (const Compound *Co_init);
  Celement* equal(const Compound *co);
#endif

  virtual ~Celement(){}

  Celement* equal(const Celement* init );
  Celement* equal(int z_init, int n_init=-1, int q_init=-1);
  Celement* equal(char *el_init );
  Celement* equal_index(int index);

  virtual char*    name(int N=7, bool space=false, int AF_flag=-1);
  virtual const QString &qname(int N=7, bool space=false, int AF_flag=-1);

  bool Test(const Celement*) const;
  bool Test(int A, int Z) const;
  bool TestPlusQ(const Celement*) const;

  void  input_mass_target( double init_mass);
  double GetMassTarget(){return mTarget;}

  double Matom();           	    // atomic mass      in aem
  double Mnucl(){return Mqe(z);}    // nuclear mass
  double Mqe(int qe);   		    // mass without qe-electrons    ion mass
  double Mqq() {return Mqe(q);}    // mass without q electrons     current ionmass

  ValueErr GetMEreal(); // int option=0);   // option=0  -> ME;  option =1 ->error

  double U_to_AMeV(){return Matom()/Ad();}
  double AMeV_to_U(){return Ad()/Matom();}

  double Uqe_to_AMeV(int qe){return Mqe(qe)/Ad();}
  double AMeV_to_Uqe(int qe){return Ad()/Mqe(qe);}

  double Uqq_to_AMeV(){return Mqq()/Ad();}
  double AMeV_to_Uqq(){return Ad()/Mqq();}


  int Index()  {return calc_index(z,n);}
  int IndexQ() {return calc_indexG(z,n,q);}

  int Z() const {return z;}
  int N() const {return n;}
  int A() const {return a;}
  int Q() const {return q;}

  void ChangeVerify(bool v){Verify=v;}
  bool GetVerify() const {return Verify;}

  double Zd() const {return double(z);}
  double Nd() const {return double(n);}
  double Ad() const {return double(a);}
  double Qd() const {return double(q);}

  void SetQ(int q_init)   {q=q_init;}
  bool IsGamma() const {return (z==0 && n==0);}

#ifndef IsomerAPI_case
  bool isPrimaryBeam();
#endif

  Celement *returnCelement() {return this;}

  //int GetOddEven() const {return OddEven;}
  bool N_odd() const;
  bool Z_odd() const;
  bool N_even() const;
  bool Z_even() const;
  bool odd_odd() const;
  bool even_even() const;
  bool odd_even() const;

private:
  QString qName;

protected:
  const char*  el;
  double mTarget;
  bool Verify;

  bool n_even;
  bool z_even;
};
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


// Compatibility: old files that include only o_Element.h still see the split classes.
#ifndef IsomerAPI_case
  #include "o_Target.h"
  #include "o_Proj.h"
  #include "o_Compound.h"
  #include "o_Calc.h"
  #include "o_SCelement.h"
#endif

#endif
