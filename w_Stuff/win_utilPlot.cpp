#include <QPainter>
#include <QDebug>
#include <QString>


#if !defined(liseStrcpyOS_h)
      #include "w_Stuff/liseStrcpyOS.h"
#endif

using namespace Qt::StringLiterals;   // Qt 6+
extern char* qstrcpyL (char *dest,   size_t destsize, const QString &qs);

//  "Bucks" is Borland superscript and subscript
void	StrCpyNoBucks(char *dst, char *src);
QString QStrCpyNoBucks(const char *src);
QString QStrCpyNoBucks(const QString &src);
QString QStrNoHtml(const QString &src);
QString changeSups(const QString &src, const char *sub);
QString transQtToBorland(const QString &src);
QString transBorlandToQt(const QString &src);
char* newLegendQtToBorland(const char *oldstr);

QRect OutTextOleg(QPainter *painter, int x, int y, const char *s, int loc, int clip=0,
                const QRectF* PlotRect=nullptr);

int averageCharWidthOleg(QFont &t);
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWww
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWww
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
void StrCpyNoBucks(char *dst, char *src)
{
  char *s = src;
  char *d = dst;

  while(*s)
    {
      if(*s != '$' && *s != '~') *(d++)=*s;
      s++;
    }

  *d = '\x0';
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
QString QStrCpyNoBucks(const char *src)
{
  QString d(src);

  d.remove("$");
  d.remove("~");
  return d;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
QString QStrCpyNoBucks(const QString &src)
{
  QString d(src);

  d.remove("$");
  d.remove("~");
  return d;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

char* newLegendQtToBorland(const char *oldstr)  // be accurately to use this function!!!
{
  char *newstr = nullptr;

  if(oldstr)
    {
      QString res = transQtToBorland(oldstr);
      int k = res.size();
      newstr = new char[k+1];
      qstrcpyL(newstr,k+1, res);
    }
  else {
      newstr = new char[2];
      strcpyL(newstr,2,"0");
    }

  return newstr;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
QString QStrNoHtml(const QString &src)
{
  QString res(src);

  res.remove("<sup>");
  res.remove(" </sup>");
  res.remove("</sup>");
  res.remove("<sub>");
  res.remove(" </sub>");
  res.remove("</sub>");

  int k;
  while( (k=res.indexOf("<font")) >= 0)
    {
      int kend=res.indexOf(">",k+4);
      if(kend <0) break;
      res.remove(k,kend-k+1);
    }

  res.remove("</font>");
  res = transQtToBorland(res);

  return res;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
QString transQtToBorland(const QString &src)
{
  QString res(src);

  res.replace(QString("<sup>"),  QString("$"));
  res.replace(QString(" </sup>"),QString("$"));
  res.replace(QString("</sup>"), QString("$"));
  res.replace(QString("<sub>"),  QString("~"));
  res.replace(QString(" </sub>"),QString("~"));
  res.replace(QString("</sub>"), QString("~"));
  res.replace(QString("&rarr;"),  QString("->"));
  res.replace(QString("&larr;"),  QString("<-"));
  res.replace(QString("&rArr;"),  QString("=>"));
  res.replace(QString("&lArr;"),  QString("<="));
  res.replace(QString("&gt;"),  QString(">"));
  res.replace(QString("&lt;"),  QString("<"));
  res.replace(QString("&alpha;"),  QString("alpha"));
  res.replace(QString("&gamma;"),  QString("gamma"));
  res.replace(QString("&sigma;"),  QString("sigma"));
  res.replace(QString("&beta;"),  QString("beta"));
  res.replace(QString("&mu;"),  QString("mk"));
  res.replace(QString("&nbsp;"),  QString("  "));
  res.replace(QString("&rho;"),  QString("rho"));
  res.replace(QString("<BR>"),  QString("\n"));
  res.replace(QString("<br>"),  QString("\n"));
  res.remove("<b>");
  res.remove("</b>");
  res.remove("<em>");
  res.remove("</em>");
  res.remove("<small>");
  res.remove("</small>");

  return res;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
QString transBorlandToQt(const QString &src)
{
  QString res(src);

  res.replace(QString(">"),  QString("&gt;"));
  res.replace(QString("<"),  QString("&lt;"));
  res.replace(QString("->"), QString("&rarr;"));
  res.replace(QString("<-"), QString("&larr;"));
  res.replace(QString("$"),  QString("<sup>"));
  res.replace(QString("~"),  QString("<sub>"));
  res.replace(QString("\n"),  QString("<BR>"));

  res = changeSups(res,"<sup>");
  res = changeSups(res,"<sub>");

  return res;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
QString changeSups(const QString &src, const char *sub)
{
  QString res(src);

  int k = res.indexOf(sub);
  bool flagFirst = (k>=0);
  while( k >= 0)
    {
      k += (int)strlen(sub);
      int kend=res.indexOf(sub,k);
      if(kend <0) break;
      if(flagFirst)
        {
          res.insert(++kend,"/");
          flagFirst = false;
        }
      else    flagFirst = true;

      k = kend;
    }

  return res;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//===================================================================
QRect OutTextOleg(QPainter *painter, int x, int y, const char *buffer,
                int loc, int clip, const QRectF* PlotRect)

{  // loc -->  0 - left , 1 - middle, 2-right
  //  clip --> 0 no clip, 1 --> clip, do not draw,
  //  clip --> 2 clip, exit, -1 --> do not draw, no clip
  //   "$" - separator   -- for UP, "~" for for Down

QRect outRect;

  if(!PlotRect && clip>0) clip=0;

  painter->save();

  if(clip>0)
    {
    painter->setClipRect(*PlotRect,Qt::ReplaceClip);
    painter->setClipping(true);
    }

  qreal Yposition=0;
  int Xsize=0, Xreturn=0, Xstart=0;

  QRect size;
  QFont tf = painter->font();
  QFont tfUp(tf);
  qreal sF  = tf.pointSize();
  qreal sUF = sF * 0.7;
  tfUp.setPointSize(sUF);

  qreal aw = averageCharWidthOleg(tf);
  int yTop=100000, yBot=-100000;

  QFont *t = nullptr;

  //int topBottom = -1;
  //if(topBottom > 0 ) {yup=y+0.3*sUF; yud=y-0.3*sF;}
  //else
  qreal up_shift   =  -0.35*sF;
  qreal yup = y + up_shift;
  qreal down_shift =   0.15*sF;
  qreal yud = y + down_shift;

  //========================================================= calculate size
  QString qstr;
  bool shouldPrint=false;
//  bool firstTime=true;
  int flag=0;   // regular
  int flag_prev=0;
  // flag =  1 UP
  // flag = -1 DOWN

  char *s = (char *)buffer;
  //----------------------------------------------------
  while( *s != 0)
    {
      if( *s == '$' )
        {
          flag_prev=flag;
          if(flag == 1) flag=0;
          else          flag=1;
          shouldPrint=true;
        }
      else if( *s == '~' )
        {
          flag_prev=flag;
          if(flag == -1) flag= 0;
          else           flag=-1;
          shouldPrint=true;
        }
      else
        {
          if(!*(s+1)) shouldPrint=true;
          qstr += *s;
        }

      //-----------------------------------
      if(shouldPrint)
        {
          shouldPrint=false;
          if(qstr.size()>0)
            {
              if(flag_prev == 0 )            { t = &tf;   Yposition=y;   }
              else 	if(flag_prev == 1 )  { t = &tfUp; Yposition=yup; }  // up
              else 	if(flag_prev ==-1 )  { t = &tfUp; Yposition=yud; }  //down

              painter->setFont(*t);

              size =  QFontMetrics(*t).boundingRect(qstr);
              Xstart += size.width();
              qstr="";

              if(*(s+1)) Xstart += aw*(flag_prev==0 ? 0.6 : 0.3);

              if(flag_prev==0)
                {
                yTop = qMin(yTop, int(Yposition)-size.top());    // Ytop and Ybottom should be done only for regular font
                yBot = qMax(yBot, int(Yposition)-size.bottom());
                }
              else flag_prev=0;
            }
        }
      //---------------------
      s++;
    }
//------------------------------------------------
Xsize=Xstart;
//---------------------------------------------------

  switch(loc)
    {
    case 0 : Xreturn=x+Xsize; 	  Xstart=x;   	   	break;
    case 1 : Xreturn=x+Xsize/2;   Xstart=x-Xsize/2;  	break;
    case 2 : Xreturn=x;           Xstart=x-Xsize;  	break;
    default: Xstart=x;
    }

  y   = yTop;
  yup = yTop + up_shift;
  yud = yTop + down_shift;

  outRect.setRect(Xstart, yTop, Xsize, yBot-yTop);

  if(clip==2)  // use bool QRect::contains(const QRect &rectangle, bool proper = false) const
    if(
       Xstart 	    <= PlotRect->left()  ||
       Xreturn      >= PlotRect->right() ||
       y    		 <= PlotRect->top()   ||   //  think about top anf bottom instead width & height
       y + size.height() >= PlotRect->bottom()
       )
      {
        painter->restore();
        return outRect;
      }
  //WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
  //================================================  out


  s=(char*)buffer;
  qstr="";
  shouldPrint=false;
  flag_prev=0;
  flag=0;

  while( *s != 0)
    {
      if( *s == '$' )
        {
          flag_prev=flag;
          if(flag == 1) flag=0;
          else          flag=1;
          shouldPrint=true;
        }
      else if( *s == '~' )
        {
          flag_prev=flag;
          if(flag == -1) flag= 0;
          else           flag=-1;
          shouldPrint=true;
        }
      else
        {
          if(!*(s+1)) shouldPrint=true;
          qstr += *s;
        }

      //-----------------------------------
      if(shouldPrint)
        {
          shouldPrint=false;
          if(qstr.size()>0)
            {
                        if(flag_prev == 0 )  { t = &tf;   Yposition=y;   }
              else 	if(flag_prev == 1 )  { t = &tfUp; Yposition=yup; }  // up
              else 	if(flag_prev ==-1 )  { t = &tfUp; Yposition=yud; }  //down

              painter->setFont(*t);

              if(x>10000)
                {
                  if (qstr.startsWith(u"sig"_s))
                    qstr.replace(0, 3, u"σ"_s);

                  if (qstr.startsWith(u"<X>"_s))
                      qstr.replace(0, 3, u"⟨X⟩"_s);

                  if (qstr.startsWith(u"<Y>"_s))
                      qstr.replace(0, 3, u"⟨Y⟩"_s);

                  if (qstr.startsWith(u"Sum"_s))
                      qstr.replace(0, 3, u"∑"_s);
                }

              painter->drawText(Xstart, Yposition, qstr);

              size =  QFontMetrics(*t).boundingRect(qstr);

              Xstart += size.width();
              if(*(s+1)) Xstart += aw*(flag_prev==0 ? 0.6 : 0.3);

              qstr="";
              flag_prev=0;
            }
        }
      //---------------------------------------
      s++;
    }

  painter->restore();
  return outRect;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
int averageCharWidthOleg(QFont &t)
{
  QRect test10=QFontMetrics(t).boundingRect("QWYRTqwyrt");
  int aveWidth =  test10.width()/9;  // 14 default
  return aveWidth;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
