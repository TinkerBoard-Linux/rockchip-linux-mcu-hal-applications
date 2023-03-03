/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2023 Rockchip Electronics Co., Ltd.
 */

#include "skv.h"
#include "ECNR.h"

void *st_ptr;
RTSkvParam *param;
SkvFrameParam *fparam;

static void ecnr_param_printf(SkvFrameParam *fparam)
{
    printf("==== HAL SkvFrameParam Print ====\n");
    printf("fparam->samplebits:%d\n", fparam->samplebits);
    printf("fparam->samplerate:%d\n", fparam->samplerate);
    printf("fparam->in_channels:%d\n", fparam->in_channels);
    printf("fparam->out_channels:%d\n", fparam->out_channels);
    printf("fparam->src_channels:%d\n", fparam->src_channels);
    printf("fparam->ref_channels:%d\n", fparam->ref_channels);

    printf("==== HAL RTSkvParam Print ====\n");
    printf("param->model:%x\n", param->model);

    printf("==== HAL SkvAecParam Print ====\n");
    printf("param->aec->pos:%d\n", param->aec->pos);
    printf("param->aec->drop_ref_channel:%d\n", param->aec->drop_ref_channel);
    printf("param->aec->aec_mode_en:%d\n", param->aec->aec_mode_en);
    printf("param->aec->delay_len:%d\n", param->aec->delay_len);
    printf("param->aec->look_ahead:%d\n", param->aec->look_ahead);

    printf("==== HAL SkvBeamFormParam Print ====\n");
    printf("param->bf->model_en:%d\n", param->bf->model_en);
    printf("param->bf->ref_pos:%d\n", param->bf->ref_pos);
    printf("param->bf->targ:%d\n", param->bf->targ);
    printf("param->bf->num_ref_channel:%d\n", param->bf->num_ref_channel);
    printf("param->bf->drop_ref_channel:%d\n", param->bf->drop_ref_channel);

    printf("==== HAL SkvDereverbParam Print ====\n");
    printf("param->bf->dereverb->rlsLg:%d\n", param->bf->dereverb->rlsLg);
    printf("param->bf->dereverb->curveLg:%d\n", param->bf->dereverb->curveLg);
    printf("param->bf->dereverb->delay:%d\n", param->bf->dereverb->delay);
    printf("param->bf->dereverb->forgetting:%f\n", param->bf->dereverb->forgetting);
    printf("param->bf->dereverb->t60:%f\n", param->bf->dereverb->t60);
    printf("param->bf->dereverb->coCoeff:%f\n", param->bf->dereverb->coCoeff);

    printf("==== HAL SkvAesParam Print ====\n");
    printf("param->bf->aes->beta_up:%f\n", param->bf->aes->beta_up);
    printf("param->bf->aes->beta_down:%f\n", param->bf->aes->beta_down);

    printf("==== HAL SkvNlpParam Print ====\n");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            printf("param->bf->nlp->nlp16k[%d][%d]:%d\n", j, i, param->bf->nlp->nlp16k[j][i]);

    printf("==== HAL SkvAnrParam Print ====\n");
    printf("param->bf->anr->noiseFactor:%f\n", param->bf->anr->noiseFactor);
    printf("param->bf->anr->swU:%d\n", param->bf->anr->swU);
    printf("param->bf->anr->psiMin:%f\n", param->bf->anr->psiMin);
    printf("param->bf->anr->psiMax:%f\n", param->bf->anr->psiMax);
    printf("param->bf->anr->fGmin:%f\n", param->bf->anr->fGmin);

    printf("==== HAL SkvAgcParam Print ====\n");
    printf("param->bf->agc->attack_time:%f\n", param->bf->agc->attack_time);
    printf("param->bf->agc->release_time:%f\n", param->bf->agc->release_time);
    printf("param->bf->agc->max_gain:%f\n", param->bf->agc->max_gain);
    printf("param->bf->agc->max_peak:%f\n", param->bf->agc->max_peak);
    printf("param->bf->agc->fRth0:%f\n", param->bf->agc->fRth0);
    printf("param->bf->agc->fRk0:%f\n", param->bf->agc->fRk0);
    printf("param->bf->agc->fRth1:%f\n", param->bf->agc->fRth1);
    printf("param->bf->agc->fs:%d\n", param->bf->agc->fs);
    printf("param->bf->agc->frmlen:%f\n", param->bf->agc->frmlen);
    printf("param->bf->agc->attenuate_time:%f\n", param->bf->agc->attenuate_time);
    printf("param->bf->agc->fRth2:%f\n", param->bf->agc->fRth2);
    printf("param->bf->agc->fRk1:%f\n", param->bf->agc->fRk1);
    printf("param->bf->agc->fRk2:%f\n", param->bf->agc->fRk2);
    printf("param->bf->agc->fLineGainDb:%f\n", param->bf->agc->fLineGainDb);
    printf("param->bf->agc->swSmL0:%d\n", param->bf->agc->swSmL0);
    printf("param->bf->agc->swSmL1:%d\n", param->bf->agc->swSmL1);
    printf("param->bf->agc->swSmL2:%d\n", param->bf->agc->swSmL2);

    printf("==== HAL SkvCngParam Print ====\n");
    printf("param->bf->cng->fGain:%f\n", param->bf->cng->fGain);
    printf("param->bf->cng->fMpy:%f\n", param->bf->cng->fMpy);
    printf("param->bf->cng->fSmoothAlpha:%f\n", param->bf->cng->fSmoothAlpha);
    printf("param->bf->cng->fSpeechGain:%f\n", param->bf->cng->fSpeechGain);

    printf("==== HAL SkvDtdParam Print ====\n");
    printf("param->bf->dtd->ksiThd_high:%f\n", param->bf->dtd->ksiThd_high);
    printf("param->bf->dtd->ksiThd_low:%f\n", param->bf->dtd->ksiThd_low);

    printf("==== HAL SkvEqParam Print ====\n");
    printf("param->bf->eq->shwParaLen:%d\n", param->bf->eq->shwParaLen);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 13; j++)
            printf("param->bf->eq->pfCoeff:%d\n", param->bf->eq->pfCoeff[i][j]);

    printf("==== HAL mic_chns_map Print ====\n");
    for (int i = 0; i < fparam->src_channels; i++)
        printf("param->aec->mic_chns_map[%d];%d\n", i, param->aec->mic_chns_map[i]);
}

int ecnr_init(uint32_t src_shmem_address)
{
    uint32_t position = src_shmem_address;

    fparam = malloc(sizeof(SkvFrameParam));
    memcpy(fparam, position, sizeof(SkvFrameParam));
    position = position + sizeof(SkvFrameParam);

    param = malloc(sizeof(RTSkvParam));
    memcpy(param, position, sizeof(RTSkvParam));
    position = position + sizeof(RTSkvParam);

    param->aec = malloc(sizeof(SkvAecParam));
    memcpy(param->aec, position, sizeof(SkvAecParam));
    position = position + sizeof(SkvAecParam);

    param->bf = malloc(sizeof(SkvBeamFormParam));
    memcpy(param->bf, position, sizeof(SkvBeamFormParam));
    position = position + sizeof(SkvBeamFormParam);

    param->bf->dereverb = malloc(sizeof(SkvDereverbParam));
    memcpy(param->bf->dereverb, position, sizeof(SkvDereverbParam));
    position = position + sizeof(SkvDereverbParam);

    param->bf->aes = malloc(sizeof(SkvAesParam));
    memcpy(param->bf->aes, position, sizeof(SkvAesParam));
    position = position + sizeof(SkvAesParam);

    param->bf->nlp = malloc(sizeof(SkvNlpParam));
    memcpy(param->bf->nlp, position, sizeof(SkvNlpParam));
    position = position + sizeof(SkvNlpParam);

    param->bf->anr = malloc(sizeof(SkvAnrParam));
    memcpy(param->bf->anr, position, sizeof(SkvAnrParam));
    position = position + sizeof(SkvAnrParam);

    param->bf->agc = malloc(sizeof(SkvAgcParam));
    memcpy(param->bf->agc, position, sizeof(SkvAgcParam));
    position = position + sizeof(SkvAgcParam);

    param->bf->cng = malloc(sizeof(SkvCngParam));
    memcpy(param->bf->cng, position, sizeof(SkvCngParam));
    position = position + sizeof(SkvCngParam);

    param->bf->dtd = malloc(sizeof(SkvDtdParam));
    memcpy(param->bf->dtd, position, sizeof(SkvDtdParam));
    position = position + sizeof(SkvDtdParam);

    param->bf->eq = malloc(sizeof(SkvEqParam));
    memcpy(param->bf->eq, position, sizeof(SkvEqParam));
    position = position + sizeof(SkvEqParam);

    param->aec->mic_chns_map = malloc(fparam->src_channels * sizeof(short));
    memcpy(param->aec->mic_chns_map, position, fparam->src_channels * sizeof(short));

    //ecnr_param_printf(fparam);
    rkaudio_param_printf(fparam->src_channels, fparam->ref_channels, param);

    st_ptr = rkaudio_preprocess_init(fparam->samplerate, fparam->samplebits,
                                     fparam->src_channels, fparam->ref_channels, param);
    if (st_ptr == NULL)
    {
        printf("Failed to create audio preprocess handle\n");
        return RL_FALSE;
    }

    return RL_TRUE;
}

int delay_flag = 0;
int ecnr_process(uint32_t src_shmem_address, uint32_t dst_shmem_address)
{
    int is_wakeup = 0;
    int in_size = IN_SIZE * fparam->in_channels * 2;

    char *in = (char *)src_shmem_address;
    char *out = (char *)dst_shmem_address;

    rkaudio_preprocess_short(st_ptr, (short *)in, out, in_size / 2, &is_wakeup);
    /* HACK:fix xrun appear */
    if (delay_flag == 0)
    {
        delay_flag = 1;
        HAL_DelayMs(16);
    }

    return RL_TRUE;
}

int ecnr_deinit(uint32_t src_shmem_address)
{
    rkaudio_preprocess_destory(st_ptr);

    free(fparam);
    free(param->aec);
    free(param->bf);
    free(param->bf->dereverb);
    free(param->bf->aes);
    free(param->bf->anr);
    free(param->bf->agc);
    free(param->bf->nlp);
    free(param->bf->cng);
    free(param->bf->dtd);
    free(param->bf->eq);
    free(param->aec->mic_chns_map);
    free(param);

    return RL_TRUE;
}

