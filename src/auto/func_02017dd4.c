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

void func_02017dd4(fx32 *s_invs, fx32 Frame, const u32 *pData,
                   const NNSG3dResJntAnm *pJntAnm)
{
    const void *pArray = (const void *)((const u8 *)pJntAnm + *(pData + 1));
    u32 info = *pData;
    u32 last_interp;
    u32 idx0, idx1;
    fx32 remainder;
    int step;
    u32 step_shift;
    u32 frame;

    frame = (u32)(Frame >> 12);

    if (frame == pJntAnm->numFrame - 1) {
        if (!(info & 0xc0000000)) {
            idx0 = frame;
        } else if (info & 0x40000000) {
            idx0 = (frame >> 1) + (frame & 1);
        } else {
            idx0 = (frame >> 2) + (frame & 3);
        }

        if (pJntAnm->flag & 2) {
            idx1 = 0;
            goto SCALE_EX_0_1;
        } else {
            if (info & 0x20000000) {
                const fx16 *p_fx16 = (const fx16 *)pArray;
                s_invs[0] = *(p_fx16 + 2 * idx0);
                s_invs[1] = *(p_fx16 + 2 * idx0 + 1);
            } else {
                const fx32 *p_fx32 = (const fx32 *)pArray;
                s_invs[0] = *(p_fx32 + 2 * idx0);
                s_invs[1] = *(p_fx32 + 2 * idx0 + 1);
            }
            return;
        }
    }

    if (!(info & 0xc0000000)) {
        goto SCALE_EX_0;
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame >= last_interp) {
            idx0 = last_interp >> 1;
            idx1 = idx0 + 1;
            goto SCALE_EX_0_1;
        } else {
            idx0 = frame >> 1;
            idx1 = idx0 + 1;
            remainder = Frame & (0x1000 * 2 - 1);
            step = 2;
            step_shift = 1;
            goto SCALE_EX;
        }
    } else {
        if (frame >= last_interp) {
            idx0 = (frame >> 2) + (frame & 3);
            idx1 = idx0 + 1;
            goto SCALE_EX_0_1;
        } else {
            idx0 = frame >> 2;
            idx1 = idx0 + 1;
            remainder = Frame & (0x1000 * 4 - 1);
            step = 4;
            step_shift = 2;
            goto SCALE_EX;
        }
    }

SCALE_EX_0:
    idx0 = (u32)frame;
    idx1 = idx0 + 1;
SCALE_EX_0_1:
    remainder = Frame & (0x1000 - 1);
    step = 1;
    step_shift = 0;
SCALE_EX:
    {
        fx32 s0, s1;
        fx32 inv0, inv1;

        if (info & 0x20000000) {
            const fx16 *p_fx16 = (const fx16 *)pArray;
            s0 = *(p_fx16 + 2 * idx0);
            inv0 = *(p_fx16 + 2 * idx0 + 1);
            s1 = *(p_fx16 + 2 * idx1);
            inv1 = *(p_fx16 + 2 * idx1 + 1);
        } else {
            const fx32 *p_fx32 = (const fx32 *)pArray;
            s0 = *(p_fx32 + 2 * idx0);
            inv0 = *(p_fx32 + 2 * idx0 + 1);
            s1 = *(p_fx32 + 2 * idx1);
            inv1 = *(p_fx32 + 2 * idx1 + 1);
        }

        s_invs[0] = ((s0 * step) + (((s1 - s0) * remainder) >> 12)) >> step_shift;
        s_invs[1] = ((inv0 * step) + (((inv1 - inv0) * remainder) >> 12)) >> step_shift;
    }
}
