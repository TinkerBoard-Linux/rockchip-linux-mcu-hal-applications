
#ifndef _MIXERS_H_
#define _MIXERS_H_
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif


RT_RET Mixers_SigMergerProcess(int chanNum, float *xn, float *yn);
typedef enum CONTROL_TYPE_ {
    SINGLE_CTRL = 0,/* splitter: one input, single gain control, multiple output; Mixer: multiple input, single control, multiple output */
    MULTIPLE_CTRL,/* splitter: one input, multiple gain control, multiple output; Mixer: multiple input, multiple control, multiple output */
} CONTROL_TYPE;

/* static float mixer_gain[] = { 1, 0.5f, 1.1f } */
/* this param can be used for Mixers_ Init and Splitters_ init */
RT_RET Mixers_Splitters_SetParam(void *st_, CONTROL_TYPE ctrlType, float *gain);
/* the st of Mixers_init can be used for control, stereos */
void *Mixers_Init(int chan, CONTROL_TYPE ctrlType, float *gain);
void Mixers_Destroy(void *st_);
/* multiple input, one output */
RT_RET Mixers_ControlProcess(void *st_, float *xn, float *yn);
/* multiple input, two output */
RT_RET Mixers_StereoProcess(void *st_, float *x0, float *x1, float *y0, float *y1);

void *Splitters_Init(int chan, CONTROL_TYPE ctrlType, float* gain);
void Splitters_Destroy(void *st_);
/* one input, multiple output */
RT_RET Splitters_Process(void *st_, float *xn, float *yn);

/** N-way input, M-way output
 *  If there are two inputs and three outputs, the order of gain is
 *  gain00, gain01, gain02
 *  gain10, gain11, gain12
 *  The two inputs are multiplied by gain00 and gain01 respectively, and the first output is made after adding.
 */
void *Mixers_NxMInit(int inChan, int outChan, float *gain);
void Mixers_NxMDestroy(void *st_);
RT_RET Mixers_NxMSetParam(void *st_, float *gain);
RT_RET Mixers_NxMProcess(void *st_, float *xn, float *yn);

#ifdef __cplusplus
}
#endif

#endif

