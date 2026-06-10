#include <stdlib.h>
#include <stdio.h>
#include <QtMath>
#include <string.h>

#ifdef IsomerAPI_case
  #include "L_Init/myextern_IsomerAPI.h"
#else
  #include "L_Init/myextern.h"
  #include "L_Mass/o_Ionization.h"
  extern s_ionization *Sionization;
#endif

#if !defined(Oleg_class)
#include "L_Element/o_Element.h"
#endif


extern double el_masse[Number_Proton+1];
extern void killExpZero(char *ss, bool strong=true);
extern char* qstrcpyL (char *dest,   size_t destsize, const QString &qs);

char NameElement [size_NameElement];  // temporary -- should be erased to work only with qName
char NameElement2[size_NameElement]; // temporary -- should be erased to work only with qName

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
Celement::Celement(int z_init, int n_init, int q_init, bool Verify_init)
{
  Verify=Verify_init;
  equal(z_init,n_init,q_init);
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
Celement::Celement(const Celement *Ce_init)
{
  ChangeVerify(Ce_init->GetVerify());
  equal(Ce_init->z,Ce_init->n,Ce_init->q);
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
#ifndef IsomerAPI_case
Celement::Celement(const Compound *Co_init)
{
  equal(Co_init);
}
//========================================================================
Celement*  Celement::equal(const Compound *Co_init)
{
  Verify=true;
  return equal(Co_init->GetZ(0),Co_init->GetN(0));
}
#endif
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
Celement*  Celement::equal_index(int index)
{
  return equal(Z_from_index(index),N_from_index(index));
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
Celement*  Celement::equal(int z_init, int n_init, int q_init )
{
  if(z_init <= 0 )
    {
      if(!Verify )z=0;
      else        z=1;
    }
  else	      	z=z_init;

  input_mass_target(el_masse[z]);

  if(n_init >=  0) 	n=n_init;
  else
    if(!Verify ) n=0;

  if(q_init  <= 0)	q=z;
  else 		q=q_init;

  a=z+n;  el=(char *)(symb+2*z);

  //----------------------------------------
  n_even =  n%2 == 0;
  z_even =  z%2 == 0;

  //-------------------------------------------
  return this;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
Celement* Celement::equal(const Celement* init)
{
  if(this==init)return this;
  ChangeVerify(init->GetVerify()); equal(init->z,init->n,init->q); return this;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
Celement* Celement::equal(char *el_init)
{
  char *s, *seos;                                     // format: ii cc  ii+\0
  int at,zt,qt,i, shift;

  extern char* eos(char *b);
  ChangeVerify(true);

  at=0;
  zt=qt=1;
  s = el_init;
  seos=eos(s);

  while(*s < '0')
    {
      if(s==seos) goto bad_end;
      s++;
    }

  if(*s <= '9')
    {
      i=atoi(s);
      if( i==0 )  goto bad_end;
      at=i;
    }

  while(*s <= '9')
    {
      if(s==seos) goto bad_end;
      s++;
    }

  if( *s     <= 'z' && *s 	>= 'a' ) *s =  char(*s     - ('a'-'A'));
  if( *(s+1) <= 'Z' && *(s+1)   >= 'A' ) *(s+1) = char(*(s+1) + ('a'-'A'));


  shift=2;

  for(i=0; i<=Number_Proton; i++)							// from 2 symbols
    if(strncmp(s, symb+2*i, 2) == 0) break;

  if(i > Number_Proton )  {
      shift=1;
      for(i=0; i<=Number_Proton; i++)                                 // from 1 symbol
        if(  *(symb+2*i  ) == *s   &&
             *(symb+2*i+1) == ' ' 	) break;
    }

  //-----------------------------------------
  if(i <= Number_Proton )
    {
      zt=qt=i;
      if( at<1 || at < zt )
        {
          if(zt>0) {z=zt; input_mass_target(el_masse[zt]); at=n+z;}
          else     at=1;
        }
      s+=shift;
    }
  else           goto bad_end;
  //-----------------------------------------

  while(*s < '0') 	{ if(s==seos) goto bad_end;  s++; }
  i=atoi(s);
  if( i==0 || i > zt ) goto bad_end;
  qt=i;
  s+=2;

  while(*s < '0') 	{ if(s==seos) goto bad_end;  s++; }


bad_end:         equal(zt,at-zt,qt);

return this;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
bool Celement::N_odd() const  {return !n_even ; }
bool Celement::Z_odd() const  {return !z_even ; }
bool Celement::N_even() const {return n_even ;  }
bool Celement::Z_even() const {return z_even ; }
bool Celement::even_even() const {return  z_even &&  n_even ; }
bool Celement::odd_odd()   const {return !z_even && !n_even; }
bool Celement::odd_even()  const {return  z_even && !n_even; }
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
const QString& Celement::qname(int flag, bool space, int AF_flag )
{
  ///      0 AZ, 1 AZQQw, 2 AZQ, 7 - Z
  ///     1* - Graph, 2* - GraphNoSpace (really for plots)
  ///     AF_flag == 777 -----> BEAM
  ///     space=true --> keep space one one-char elements

  int Graph=flag/10;
  int mode =flag%10;
  QString qEl,qbuf;

  if(IsGamma()) {qName="gamma"; return qName;}

  if(z > Number_Proton)
    {
      qEl = (char)( (z-Number_Proton)/10 + 'K');
      qEl += (char)(z%10+'0');
    }
  else
    {
      qEl = *el;
      if(space || *(el+1)!=' ') qEl += *(el+1);
    }
//------------------------
  if(mode==7)
    {
      qstrcpyL(NameElement2,size_NameElement,qEl);   // temporary to keep NameElement2
      qName=qEl;
      return qName;
    }
  else
    {
      const char *form1a=(Graph>0 ? "<sup>%d </sup>" : "%d");
      const char *form2a=(Graph>0 ? "<sup>%d</sup>" : "%d");
      qName = qbuf.asprintf((Graph==2 ? form2a : form1a),A());
      qName += qEl;

      const char *form1b=(Graph>0 ? "<sup> %d+</sup>" : "%d+");
      const char *form2b=(Graph>0 ? "<sup>%d+</sup>" : "%d+");

      if(mode>0)
        qName += qbuf.asprintf((Graph==2 ? form2b : form1b),Q());

      //-----------------------
    #ifndef IsomerAPI_case
      if( (AF_flag     >= 0 && AF_flag     < Number_reactions+Number_SecondaryTargets)  ||
          (AF_flag%100 >= 0 && AF_flag%100 < Number_reactions+Number_SecondaryTargets)      )
        {
          extern const char *char_reactions_short[];
          extern const char *char_reactions_short2[];

          if(AF_flag>=100)  qName += qbuf.asprintf("<sup>%s</sup>", char_reactions_short2[AF_flag%100]);
          else              qName += qbuf.asprintf("<sub>%s</sub>", char_reactions_short[AF_flag%100]);
        }
      else
        if(AF_flag==777) qName += "[beam]";
    #endif
    }

return qName;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
char* Celement::name(int flag, bool space, int AF_flag )
{
qstrcpyL(NameElement, size_NameElement, qname(flag,space,AF_flag));
return NameElement;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
bool Celement::Test(const Celement *t) const
{
  if( t->z == z  && t->a == a ) return true;
  else				return false;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
bool Celement::Test(int A, int Z) const
{
  if( Z == z  && A == a ) 	return true;
  else				return false;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
bool Celement::TestPlusQ(const Celement *t) const
{
  if( t->z == z  && t->a == a  && t->q == q   ) return true;
  else						return false;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
void Celement::input_mass_target( double temp)
{
  mTarget=temp;  // mass
  temp=mTarget-z;
  if(temp <= 0) { mTarget=z; n=0; }  //  if a bad input
  else {
      n=temp;
      if(temp-n > 0.5) n++;
    };
  a=z+n;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
double Celement::Matom(void)
{
  if(IsGamma()) return 0;
  double ME =  (GetMEreal()).value;
  double mIsotop= a + ME/amu_MeV;
  return mIsotop;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
double Celement::Mqe(int qe)
{
  if(IsGamma()) return 0;
  qe = qMax(0,qe); qe = qMin(z,qe);

  double ME =  (GetMEreal()).value;
  double dBE = 0;

#ifndef IsomerAPI_case
  if(z<=110 && Sionization && opt->ionization)
    {
      double BindingEnergy0 = Sionization->GetTotal(z,0);
      double BindingEnergyQ = Sionization->GetTotal(z,qe);
      dBE = (BindingEnergy0-BindingEnergyQ)*1e-6;         // eV to MeV
    }
#endif

  double mIsotop= a + (ME - double(qe)*Mass_e + dBE)  / amu_MeV;
  return mIsotop;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
ValueErr Celement::GetMEreal()
{
  ValueErr ME;
  if(IsGamma()) return ME;

#ifndef IsomerAPI_case
  ME = mass->GetMeTable(this);
#endif

  return ME;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
#ifndef IsomerAPI_case
bool Celement::isPrimaryBeam()
{
  return this->Test(beam);
}
#endif
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW==
