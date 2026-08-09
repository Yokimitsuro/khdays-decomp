typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;

typedef struct NNSG3dResAnmHeader {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dResJntAnm {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
} NNSG3dResJntAnm;

void func_02017a90(fx32 *pVal, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    const void *pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    u32 info = *pData;
    u32 last_interp;
    u32 idx;
    fx32 remainder;
    int step;
    u32 step_shift;
    u32 frame;

    frame = (u32)(Frame >> 12);

    if (frame == pJntAnm->numFrame - 1) {
        if (!(info & 0xc0000000)) {
            idx = frame;
        } else if (info & 0x40000000) {
            idx = (frame >> 1) + (frame & 1);
        } else {
            idx = (frame >> 2) + (frame & 3);
        }

        if (pJntAnm->flag & 2) {
            fx32 v0, v1;
            remainder = Frame & (0x1000 - 1);

            if (info & 0x20000000) {
                const fx16 *p_fx16 = (const fx16 *)pArray;
                v0 = *(p_fx16 + idx);
                v1 = *p_fx16;
            } else {
                const fx32 *p_fx32 = (const fx32 *)pArray;
                v0 = *(p_fx32 + idx);
                v1 = *p_fx32;
            }

            *pVal = v0 + (((v1 - v0) * remainder) >> 12);
            return;
        } else {
            if (info & 0x20000000) {
                *pVal = *((const fx16 *)pArray + idx);
            } else {
                *pVal = *((const fx32 *)pArray + idx);
            }
            return;
        }
    }

    if (!(info & 0xc0000000)) {
        goto TRANS_EX_0;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame >= last_interp) {
            idx = last_interp >> 1;
            goto TRANS_EX_0_1;
        } else {
            idx = frame >> 1;
            remainder = Frame & (0x1000 * 2 - 1);
            step = 2;
            step_shift = 1;
            goto TRANS_EX;
        }
    } else {
        if (frame >= last_interp) {
            idx = (frame >> 2) + (frame & 3);
            goto TRANS_EX_0_1;
        } else {
            idx = frame >> 2;
            remainder = Frame & (0x1000 * 4 - 1);
            step = 4;
            step_shift = 2;
            goto TRANS_EX;
        }
    }

TRANS_EX_0:
    idx = (u32)frame;
TRANS_EX_0_1:
    remainder = Frame & (0x1000 - 1);
    step = 1;
    step_shift = 0;
TRANS_EX:
    {
        fx32 v0, v1;
        if (info & 0x20000000) {
            const fx16 *p_fx16 = (const fx16 *)pArray;
            v0 = *(p_fx16 + idx);
            v1 = *(p_fx16 + idx + 1);
        } else {
            const fx32 *p_fx32 = (const fx32 *)pArray;
            v0 = *(p_fx32 + idx);
            v1 = *(p_fx32 + idx + 1);
        }

        *pVal = ((v0 * step) + (((v1 - v0) * remainder) >> 12)) >> step_shift;
    }
}
