typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

u16 func_02018830(const void *resource, u32 info, u32 frame)
{
    const u8 *values;
    u32 last_interp;
    u32 idx;
    u32 idx_sub;
    u32 value;
    u32 value_sub;

    if (info & 0x20000000) {
        return (u16)info;
    }

    values = (const u8 *)resource + (u16)info;

    if (!(info & 0xc0000000)) {
        return values[frame];
    }

    last_interp = (info & 0x1fff0000) >> 16;

    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                return values[(last_interp >> 1) + 1];
            } else {
                value = values[frame >> 1];
                value_sub = values[(frame >> 1) + 1];
                return (u16)((value + value_sub) >> 1);
            }
        } else {
            return values[frame >> 1];
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                const u8 *tail = values + (last_interp >> 2);
                return tail[frame & 3];
            }

            if (frame & 1) {
                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }

                value = values[idx];
                value_sub = values[idx_sub];
                return (u16)((value + value + value + value_sub) >> 2);
            } else {
                value = values[frame >> 2];
                value_sub = values[(frame >> 2) + 1];
                return (u16)((value + value_sub) >> 1);
            }
        } else {
            return values[frame >> 2];
        }
    }
}
