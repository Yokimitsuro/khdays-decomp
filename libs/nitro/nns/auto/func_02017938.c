typedef unsigned char u8;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;
typedef signed long long fx64;

typedef struct NNSG3dResJntAnm NNSG3dResJntAnm;

void func_02017938(fx32 *pVal, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    u32 frame = (u32)(Frame >> 12);
    const void *pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    u32 info = *pData;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (!(info & 0xc0000000)) {
        idx = frame;
        goto TRANS_NONINTERP;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto TRANS_NONINTERP;
            } else {
                idx = frame >> 1;
                goto TRANS_INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto TRANS_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto TRANS_NONINTERP;
            }

            if (frame & 1) {
                fx32 v, v_sub;
                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }

                if (info & 0x20000000) {
                    const fx16 *p_fx16 = (const fx16 *)pArray;
                    v = *(p_fx16 + idx);
                    v_sub = *(p_fx16 + idx_sub);
                    *pVal = (v + v + v + v_sub) >> 2;
                } else {
                    const fx32 *p_fx32 = (const fx32 *)pArray;
                    v = *(p_fx32 + idx);
                    v_sub = *(p_fx32 + idx_sub);
                    *pVal = (fx32)(((fx64)v + v + v + v_sub) >> 2);
                }
                return;
            } else {
                idx = frame >> 2;
                goto TRANS_INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto TRANS_NONINTERP;
        }
    }

TRANS_INTERP_2:
    if (info & 0x20000000) {
        const fx16 *p_fx16 = (const fx16 *)pArray;
        *pVal = (*(p_fx16 + idx) + *(p_fx16 + idx + 1)) >> 1;
    } else {
        const fx32 *p_fx32 = (const fx32 *)pArray;
        fx32 v1 = *(p_fx32 + idx) >> 1;
        fx32 v2 = *(p_fx32 + idx + 1) >> 1;
        *pVal = v1 + v2;
    }
    return;

TRANS_NONINTERP:
    if (info & 0x20000000) {
        *pVal = *((const fx16 *)pArray + idx);
    } else {
        *pVal = *((const fx32 *)pArray + idx);
    }
}
