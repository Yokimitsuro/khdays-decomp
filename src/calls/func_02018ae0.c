typedef unsigned char u8;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;

fx32 func_02018ae0(const u8 *pArrayBase, u32 info, u32 constOrOffset, u32 frame)
{
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (info & 0x20000000) {
        return (fx32)constOrOffset;
    }

    pArrayBase = pArrayBase + constOrOffset;

    if (!(info & 0xc0000000)) {
        idx = frame;
        goto NONINTERP;
    }

    last_interp = info & 0xffff;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto NONINTERP;
            } else {
                idx = frame >> 1;
                goto INTERP_2;
            }
        } else {
            idx = frame >> 1;
            goto NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (frame & 3) + (last_interp >> 2);
                goto NONINTERP;
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

                if (info & 0x10000000) {
                    const fx16 *p = (const fx16 *)pArrayBase;
                    v = p[idx];
                    v_sub = p[idx_sub];
                } else {
                    const fx32 *p = (const fx32 *)pArrayBase;
                    v = p[idx];
                    v_sub = p[idx_sub];
                }
                return (v + v + v + v_sub) >> 2;
            } else {
                idx = frame >> 2;
                goto INTERP_2;
            }
        } else {
            idx = frame >> 2;
            goto NONINTERP;
        }
    }

NONINTERP:
    if (info & 0x10000000) {
        const fx16 *p = (const fx16 *)pArrayBase;
        return p[idx];
    } else {
        const fx32 *p = (const fx32 *)pArrayBase;
        return p[idx];
    }

INTERP_2:
    {
        fx32 v1, v2;
        if (info & 0x10000000) {
            const fx16 *p = (const fx16 *)pArrayBase;
            v1 = p[idx];
            v2 = p[idx + 1];
        } else {
            const fx32 *p = (const fx32 *)pArrayBase;
            v1 = p[idx];
            v2 = p[idx + 1];
        }
        return (v1 + v2) >> 1;
    }
}
