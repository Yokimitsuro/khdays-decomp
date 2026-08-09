typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

u16 func_01ff9fd4(const void *resource, u32 info, u32 frame)
{
    const u16 *values;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;

    if (info & 0x20000000) {
        return (u16)info;
    }

    values = (const u16 *)((const u8 *)resource + (u16)info);

    if (!(info & 0xc0000000)) {
        return values[frame];
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                return values[(last_interp >> 1) + 1];
            } else {
                idx = frame >> 1;
                goto COLOR_INTERP_2;
            }
        } else {
            return values[frame >> 1];
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                const u16 *tail = values + (last_interp >> 2);
                return tail[frame & 3];
            }

            if (frame & 1) {
                u32 value;
                u32 value_sub;

                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }

                value = values[idx];
                value_sub = values[idx_sub];
                {
                    u32 redBlue;
                    u32 green;
                    green = value & 0x03e0;
                    redBlue = value & 0x7c1f;
                    green *= 3;
                    green += value_sub & 0x03e0;
                    redBlue *= 3;
                    redBlue += value_sub & 0x7c1f;
                    return (u16)(((redBlue >> 2) & 0x7c1f) |
                                 ((green >> 2) & 0x03e0));
                }
            } else {
                idx = frame >> 2;
                goto COLOR_INTERP_2;
            }
        } else {
            return values[frame >> 2];
        }
    }

COLOR_INTERP_2:
    {
        u32 value = values[idx];
        u32 value_sub = values[idx + 1];
        return (u16)((((value & 0x7c1f) + (value_sub & 0x7c1f)) >> 1) & 0x7c1f |
                     (((value & 0x03e0) + (value_sub & 0x03e0)) >> 1) & 0x03e0);
    }

}
