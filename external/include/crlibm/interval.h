#include "crlibm.h"
#include "crlibm_private.h"
#include "triple-double.h"

typedef struct interval { double INF, SUP;} interval ;

#define LOW(x) x.INF
#define UP(x) x.SUP

#define ASSIGN_LOW(x,e) x.INF=e
#define ASSIGN_UP(x,e) x.SUP=e

#define TRUE (1+1==2)
#define FALSE (1+1==3)

interval j_log();

#define TEST_AND_COPY_RDRU_LOG(__cond__, __res_rd__, __yh_rd__, __yl_rd__, __res_ru__, __yh_ru__, __yl_ru__, __eps__)  \
{                                                                      \
  db_number yh_rd, yl_rd, u53_rd, yh_ru, yl_ru, u53_ru;                    \
  int yh_rd_neg, yl_rd_neg, yh_ru_neg, yl_ru_neg;                             \
  int rd_ok, ru_ok;                                                        \
  double save_res_rd=__res_rd__;                                              \
  yh_rd.d = __yh_rd__;    yl_rd.d = __yl_rd__;                                     \
  yh_rd_neg = (yh_rd.i[HI] & 0x80000000);                                    \
  yl_rd_neg = (yl_rd.i[HI] & 0x80000000);                                    \
  yh_rd.l = yh_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_rd.l = yl_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_rd.l     = (yh_rd.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  yh_ru.d = __yh_ru__;    yl_ru.d = __yl_ru__;                                     \
  yh_ru_neg = (yh_ru.i[HI] & 0x80000000);                                    \
  yl_ru_neg = (yl_ru.i[HI] & 0x80000000);                                    \
  yh_ru.l = yh_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_ru.l = yl_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_ru.l     = (yh_ru.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  __cond__ = 0;                                                        \
  rd_ok=(yl_rd.d > __eps__ * u53_rd.d);                                  \
  ru_ok=(yl_ru.d > __eps__ * u53_ru.d);                                   \
     if(yl_rd_neg) {  /* The case yl==0 is filtered by the above test*/    \
      /* return next down */                                           \
      yh_rd.d = __yh_rd__;                                                   \
      if(yh_rd_neg) yh_rd.l++;  else yh_rd.l--; /* Beware: fails for zero */    \
      __res_rd__ = yh_rd.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_rd__ = __yh_rd__;                                                \
    }                                                                  \
    if(!yl_ru_neg) {  /* The case yl==0 is filtered by the above test*/   \
      /* return next up */                                             \
      yh_ru.d = __yh_ru__;                                                   \
      if(yh_ru_neg) yh_ru.l--;  else yh_ru.l++; /* Beware: fails for zero */    \
      __res_ru__ = yh_ru.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_ru__ = __yh_ru__;                                                \
    }                                                                  \
  if(save_res_rd==-1.0/0.0) __res_rd__=-1.0/0.0;           \
  if(rd_ok && ru_ok){\
    interval _res;                                                     \
    ASSIGN_LOW(_res,__res_rd__);                                       \
    ASSIGN_UP(_res,__res_ru__);                                        \
    return(_res);                                                      \
  }                                                                    \
  else if (rd_ok){\
    __cond__=1;                                                \
  }\
  else if (ru_ok){\
     __cond__=2;                                     \
  }\
}

#define TEST_AND_COPY_RDRU_EXP(__cond__, cond1, cond2, __res_rd__, __yh_rd__, __yl_rd__, __res_ru__, __yh_ru__, __yl_ru__, __eps__)  \
{                                                                      \
  db_number yh_rd, yl_rd, u53_rd, yh_ru, yl_ru, u53_ru;                    \
  int yh_rd_neg, yl_rd_neg, yh_ru_neg, yl_ru_neg;                             \
  int rd_ok, ru_ok;                                                        \
  double save_res_rd=__res_rd__;                                              \
  double save_res_ru=__res_ru__;                                              \
  yh_rd.d = __yh_rd__;    yl_rd.d = __yl_rd__;                                     \
  yh_rd_neg = (yh_rd.i[HI] & 0x80000000);                                    \
  yl_rd_neg = (yl_rd.i[HI] & 0x80000000);                                    \
  yh_rd.l = yh_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_rd.l = yl_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_rd.l     = (yh_rd.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  yh_ru.d = __yh_ru__;    yl_ru.d = __yl_ru__;                                     \
  yh_ru_neg = (yh_ru.i[HI] & 0x80000000);                                    \
  yl_ru_neg = (yl_ru.i[HI] & 0x80000000);                                    \
  yh_ru.l = yh_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_ru.l = yl_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_ru.l     = (yh_ru.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  __cond__ = 0;                                                        \
  rd_ok=(yl_rd.d > __eps__ * u53_rd.d);                                  \
  ru_ok=(yl_ru.d > __eps__ * u53_ru.d);                                   \
     if(yl_rd_neg) {  /* The case yl==0 is filtered by the above test*/    \
      /* return next down */                                           \
      yh_rd.d = __yh_rd__;                                                   \
      if(yh_rd_neg) yh_rd.l++;  else yh_rd.l--; /* Beware: fails for zero */    \
      __res_rd__ = yh_rd.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_rd__ = __yh_rd__;                                                \
    }                                                                  \
    if(!yl_ru_neg) {  /* The case yl==0 is filtered by the above test*/   \
      /* return next up */                                             \
      yh_ru.d = __yh_ru__;                                                   \
      if(yh_ru_neg) yh_ru.l--;  else yh_ru.l++; /* Beware: fails for zero */    \
      __res_ru__ = yh_ru.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_ru__ = __yh_ru__;                                                \
    }                                                                  \
  if(cond1) __res_rd__=save_res_rd;           \
  if(cond2) __res_ru__=save_res_ru;           \
  if(rd_ok && ru_ok){\
    __cond__=3;                                                      \
  }                                                                    \
  else if (rd_ok){\
    __cond__=1;                                                \
  }\
  else if (ru_ok){\
     __cond__=2;                                     \
  }\
}


#define TEST_AND_COPY_RDRU_EXPM1(__cond__, __res_rd__, __yh_rd__, __yl_rd__, __res_ru__, __yh_ru__, __yl_ru__, __eps__)  \
{                                                                      \
  db_number yh_rd, yl_rd, u53_rd, yh_ru, yl_ru, u53_ru;                    \
  int yh_rd_neg, yl_rd_neg, yh_ru_neg, yl_ru_neg;                             \
  int rd_ok, ru_ok;                                                        \
  yh_rd.d = __yh_rd__;    yl_rd.d = __yl_rd__;                                     \
  yh_rd_neg = (yh_rd.i[HI] & 0x80000000);                                    \
  yl_rd_neg = (yl_rd.i[HI] & 0x80000000);                                    \
  yh_rd.l = yh_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_rd.l = yl_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_rd.l     = (yh_rd.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  yh_ru.d = __yh_ru__;    yl_ru.d = __yl_ru__;                                     \
  yh_ru_neg = (yh_ru.i[HI] & 0x80000000);                                    \
  yl_ru_neg = (yl_ru.i[HI] & 0x80000000);                                    \
  yh_ru.l = yh_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_ru.l = yl_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_ru.l     = (yh_ru.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  __cond__ = 0;                                                        \
  rd_ok=(yl_rd.d > __eps__ * u53_rd.d);                                  \
  ru_ok=(yl_ru.d > __eps__ * u53_ru.d);                                   \
     if(yl_rd_neg) {  /* The case yl==0 is filtered by the above test*/    \
      /* return next down */                                           \
      yh_rd.d = __yh_rd__;                                                   \
      if(yh_rd_neg) yh_rd.l++;  else yh_rd.l--; /* Beware: fails for zero */    \
      __res_rd__ = yh_rd.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_rd__ = __yh_rd__;                                                \
    }                                                                  \
    if(!yl_ru_neg) {  /* The case yl==0 is filtered by the above test*/   \
      /* return next up */                                             \
      yh_ru.d = __yh_ru__;                                                   \
      if(yh_ru_neg) yh_ru.l--;  else yh_ru.l++; /* Beware: fails for zero */    \
      __res_ru__ = yh_ru.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_ru__ = __yh_ru__;                                                \
    }                                                                  \
  if(rd_ok && ru_ok){\
    interval _res;                                                     \
    ASSIGN_LOW(_res,__res_rd__);                                       \
    ASSIGN_UP(_res,__res_ru__);                                        \
    return(_res);                                                      \
  }                                                                    \
  else if (rd_ok){\
    __cond__=1;                                                \
  }\
  else if (ru_ok){\
     __cond__=2;                                     \
  }\
}

#define TEST_AND_COPY_RDRU_LOG2(__cond__, __res_rd__, __yh_rd__, __yl_rd__, __res_ru__, __yh_ru__, __yl_ru__, __eps_rd__, __eps_ru__)  \
{                                                                      \
  db_number yh_rd, yl_rd, u53_rd, yh_ru, yl_ru, u53_ru;                    \
  int yh_rd_neg, yl_rd_neg, yh_ru_neg, yl_ru_neg;                             \
  int rd_ok, ru_ok;                                                        \
  yh_rd.d = __yh_rd__;    yl_rd.d = __yl_rd__;                                     \
  yh_rd_neg = (yh_rd.i[HI] & 0x80000000);                                    \
  yl_rd_neg = (yl_rd.i[HI] & 0x80000000);                                    \
  yh_rd.l = yh_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_rd.l = yl_rd.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_rd.l     = (yh_rd.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  yh_ru.d = __yh_ru__;    yl_ru.d = __yl_ru__;                                     \
  yh_ru_neg = (yh_ru.i[HI] & 0x80000000);                                    \
  yl_ru_neg = (yl_ru.i[HI] & 0x80000000);                                    \
  yh_ru.l = yh_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  yl_ru.l = yl_ru.l & 0x7fffffffffffffffLL;  /* compute the absolute value*/ \
  u53_ru.l     = (yh_ru.l & ULL(7ff0000000000000)) +  ULL(0010000000000000); \
  __cond__ = 0;                                                        \
  rd_ok=(yl_rd.d > __eps_rd__ * u53_rd.d);                                  \
  ru_ok=(yl_ru.d > __eps_ru__ * u53_ru.d);                                   \
     if(yl_rd_neg) {  /* The case yl==0 is filtered by the above test*/    \
      /* return next down */                                           \
      yh_rd.d = __yh_rd__;                                                   \
      if(yh_rd_neg) yh_rd.l++;  else yh_rd.l--; /* Beware: fails for zero */    \
      __res_rd__ = yh_rd.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_rd__ = __yh_rd__;                                                \
    }                                                                  \
    if(!yl_ru_neg) {  /* The case yl==0 is filtered by the above test*/   \
      /* return next up */                                             \
      yh_ru.d = __yh_ru__;                                                   \
      if(yh_ru_neg) yh_ru.l--;  else yh_ru.l++; /* Beware: fails for zero */    \
      __res_ru__ = yh_ru.d ;                                                 \
    }                                                                  \
    else {                                                             \
      __res_ru__ = __yh_ru__;                                                \
    }                                                                  \
  if(rd_ok && ru_ok){\
    interval _res;                                                     \
    ASSIGN_LOW(_res,__res_rd__);                                       \
    ASSIGN_UP(_res,__res_ru__);                                        \
    return(_res);                                                      \
  }                                                                    \
  else if (rd_ok){\
    __cond__=1;                                                \
  }\
  else if (ru_ok){\
     __cond__=2;                                     \
  }\
}


#define RETURN_EMPTY_INTERVAL                                               \
{                                                                           \
  interval res;                                                             \
  ASSIGN_LOW(res,0.0/0.0);                                                  \
  ASSIGN_UP(res,0.0/0.0);                                                   \
  return res;                                                               \
}

