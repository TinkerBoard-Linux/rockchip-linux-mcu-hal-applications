#ifndef _BASIC_DSP_H_
#define _BASIC_DSP_H_

#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************arithmetic operations*******************/
// yn=abs(xn);
RT_RET Basic_Arith_Abs(int chan, float *xn, float *yn);
// yn=1/sqrt(xn);
RT_RET Basic_Arith_InvSquareRoot(int chan, float *xn, float *yn);
// yn=sqrt(xn);
RT_RET Basic_Arith_SquareRoot(int chan, float*xn, float *yn);
// yn=x0 / x1;
RT_RET Basic_Arith_Divide(int chan, float *x0, float *x1, float *yn);
// yn=x0 * x1;
RT_RET Basic_Arith_Multiply(int chan, float *x0, float *x1, float *yn);
// yn=-xn;
RT_RET Basic_Arith_Invert(int chan, float *xn, float *yn);
// yn = xn[0]+xn[1]...
RT_RET Basic_Arith_Add(int chan, float *xn, float *yn);
// yn = xn[0]-xn[1]...
RT_RET Basic_Arith_Subtract(int chan, float*xn, float* yn);

typedef struct RmsWithTcParam_
{
    int  timeConstant;      // Time coefficient  ：1 <= timeConstant <= 8686
    bool isDBps;            // time uint，true is dbps、false is ms
    int  fs;                // sampling rate
} RmsWithTcParam;

inline static RmsWithTcParam* Basic_Arith_RmsWithTCParamInit(void)
{
    RmsWithTcParam* param = (RmsWithTcParam*)malloc(sizeof(RmsWithTcParam));
    param->fs = 48000;
    param->isDBps = false;
    param->timeConstant = 121;

    return param;
};

void  *Basic_Arith_RmsWithTcInit(int fs, int chan, RmsWithTcParam *param);
void Basic_Arith_RmsWithTcDestroy(void *st_);
RT_RET Basic_Arith_RmsWithTcProcess(void *st_, float *xn, float *yn);
RT_RET Basic_Arith_RmsWithTcSetParam(void *st_, RmsWithTcParam *param);

/* summa 和 squaresmma可共用st */
void  *Basic_Arith_SummationInit(int chan);
void Basic_Arith_SummationDestroy(void *st_);
RT_RET Basic_Arith_SummationProcess(void *st_, float *xn, float *rst, float *yn);
#define Basic_Arith_SquareSummationInit Basic_Arith_SummationInit
#define Basic_Arith_SquareSummationDestroy Basic_Arith_SummationDestroy
RT_RET	Basic_Arith_SquareSummationProcess(void *st_, float *xn, float *rst, float *yn);


/******************logic*******************/
RT_RET Basic_Logic_AbsMax(int chan, float *xn, float *yn);
RT_RET Basic_Logic_Max(int chan, float *xn, float *yn);
RT_RET Basic_Logic_Min(int chan, float *xn, float *yn);

typedef enum COMPARE_TYPE_ {
    COMPARE_GT    =   0,      /* > */
    COMPARE_LT    =   1,      /* < */
    COMPARE_GE    =   2,      /* >= */
    COMPARE_LE    =   3,      /* <= */
    COMPARE_EQ    =   4,      /* == */
} COMPARE_TYPE;

typedef enum LOGIC_TYPE_ {
    LOGIC_AND    =   0,
    LOGIC_NAND   =   1,
    LOGIC_OR     =   2,
    LOGIC_NOR    =   3,
    LOGIC_XOR    =   4,
} LOGIC_TYPE;

/* comparing x0 and x1, the result is 1, output x0, otherwise output x1 */
RT_RET Basic_Logic_ABCondition(COMPARE_TYPE condition, float *x0, float *x1, float *yn);
/* comparing x0 and x1, the result is 1, output x2, otherwise output x3 */
RT_RET Basic_Logic_ABCDCondition(COMPARE_TYPE condition, float *x0, float *x1, float *x2, float *x3, float *yn);
/* bits:0~30 */
void* Basic_Logic_BufferGateInit(int chan, int bits);
void Basic_Logic_BufferGateDestroy(void *st_);
RT_RET Basic_Logic_BufferGateProcess(void *st_, float *xn, int *yn);
RT_RET Basic_Logic_BufferGateSetParam(void *st_, int bits);
/* share Basic_Logic_BufferGateInit、Destroy and SetParam */
RT_RET Basic_Logic_ZeroComparatorProcess(void *st_, float *xn, int *yn);

typedef enum ONESHOT_TYPE_ {
    ONESHOT_FALL          =   0,
    ONESHOT_FALL_RST      =   1,
    ONESHOT_RISE          =   2,
    ONESHOT_RISE_RST      =   3,
} ONESHOT_TYPE;

typedef enum HOLDALGO_TYPE_ {
    HOLD_VALUE            = 0,
    HOLD_ABSMAX,
    HOLD_MAX,
    HOLD_MIN
} HOLDALGO_TYPE;

void *Basic_Logic_OneShotInit(ONESHOT_TYPE algoType, int bit);
void Basic_Logic_OneShotDestroy(void *st_);
RT_RET Basic_Logic_OneShotProcess(void *st_, float *xn, float *rst, int *yn);
RT_RET Basic_Logic_OneShotSetParam(void *st_, ONESHOT_TYPE algoType, int bit);
RT_RET Basic_Logic_LogicCalc(LOGIC_TYPE logic, float *x0, float *x1, float *yn);

/******************dsp function*******************/
void* Basic_DSP_HoldInit(HOLDALGO_TYPE algoType);
void Basic_DSP_HoldDestroy(void *st);
RT_RET Basic_DSP_HoldSetParam(void* st_, HOLDALGO_TYPE algoType);
RT_RET Basic_DSP_HoldProcess(void *st_, float *xn, float *hold, float *yn);

typedef enum DELAYALGO_TYPE_ {
    ALGO_DELAY            = 0,    /* set delay point delay */
    VOL_CONTROL_DELAY,            /* delay control via voltage */
} DELAYALGO_TYPE;

void *Basic_DSP_DelayInit(int chan, DELAYALGO_TYPE algoType, int delay,int maxDelay);
void Basic_DSP_DelayDestroy(void *st_);
RT_RET Basic_DSP_DelayReset(void *st_, DELAYALGO_TYPE algoType, int delay, int maxDelay);
RT_RET Basic_DSP_DelayProcess(void *st_, float *xn, float *yn);/* multiple inputs x, one delay, multiple outputs */
RT_RET Basic_DSP_VolControlDelayProcess(void *st_, float *xn, float *voltage, float *yn);/* one input x, multiple voltage delays, and multiple outputs */

/******************gain*******************/
typedef enum GAIN_TYPE_ {
    GAIN_DB    = 0,    /* Gain in db */
    GAIN_LIN,          /* Gain unit is amplitude multiple (2LIN=6DB) */
} GAIN_TYPE;

void *Basic_Gain_Init(int chan, GAIN_TYPE gainType, float gain);
void Basic_Gain_Destroy(void *st);
RT_RET Basic_Gain_SetParam(void *st_, GAIN_TYPE gainType, float gain);
RT_RET Basic_Gain_Process(void *st_, float *xn, float *yn);

/******************polynomial*******************/
//order;
//*table;     // a(n-1)*x^(n-1)+a(n-2)*x^(n-2)+a0
void *Basic_Polynomial_Init(int chan, int order, float *table);
void Basic_Polynomial_Destroy(void *st_);
RT_RET Basic_Polynomial_SetParam(void *st_, int order, float *table);
RT_RET Basic_Polynomial_Process(void *st_, float *xn, float *yn);

#ifdef __cplusplus
}
#endif

#endif // _BASIC_DSP_H_

