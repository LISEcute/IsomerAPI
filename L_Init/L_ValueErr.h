#if !defined(ValueErr_class)
#define  ValueErr_class


#if !defined(constant_h)
#include "L_Init/Constant.h"
#endif

extern double RootSumSquared2(double x1, double x2);

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW--
struct ValueErr
{
  double value;
  double error;

  //ValueErr() = default;
  ValueErr(double v=0, double err=0) {value=v; error=err;};
  ValueErr(const ValueErr &t) {value=t.value; error=t.error;};

  double makeError(const ValueErr &t1, const ValueErr &t2)
  {
    if(t1.error==BadValue || t2.error==BadValue) error=BadValue;
    else this->error = RootSumSquared2(t1.error,t2.error);
    return error;
  }
  //--------------------------------------

  void min(const ValueErr &t) { if(t.value < this->value && t.value!=BadValue) {*this=t;}};
  void max(const ValueErr &t) { if(t.value > this->value && t.value!=BadValue) {*this=t;}};

  bool isBadValue()      {return value==BadValue;};
  bool isErrorBadValue() {return error==BadValue;};
  void setBadValue() {value=BadValue; error=BadValue;}

  //-----------------------------------
  ValueErr& operator = (const ValueErr &t)
  {value=t.value; error=t.error; return *this;}

  //-----------------------------------
  ValueErr operator+(const ValueErr &t) const
  {
    ValueErr result;

    if (this->value == BadValue || t.value == BadValue)    result.setBadValue();
    else
      {
        result.value = this->value + t.value;
        if(this->error==BadValue || t.error==BadValue)
          result.error=BadValue;
        else
          result.error = RootSumSquared2(this->error, t.error);
      }
    return result;
  }
  //-----------------------------------
  ValueErr operator-(const ValueErr &t) const
  {
    ValueErr result;

    if (this->value == BadValue || t.value == BadValue)    result.setBadValue();
    else
      {
        result.value = this->value - t.value;
        if(this->error==BadValue || t.error==BadValue)
          result.error=BadValue;
        else
          result.error = RootSumSquared2(this->error, t.error);
      }
    return result;
  }

};


#endif
