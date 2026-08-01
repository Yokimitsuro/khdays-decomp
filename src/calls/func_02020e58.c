/*
 * Game_RunActionScript - per-tick action/command interpreter for one entry of the gameplay action
 * system. Called from the ov002 gameplay tick (Ov002_TickGameplayState). st is the action-system
 * state: a 0x48-byte Entry array at st+4 (indexed by the depth counter st+0x124), each Entry with a
 * command-script pointer (+0x10), an "action" slot (+0x18/0x1c) and five callback slots
 * (+0x20.. in 8-byte {fn,arg} pairs).
 *
 * Steps on the current entry (cur = &entries[count]):
 *  - if both st+0x584 and st+0x588 are set, run func_02020d44 first;
 *  - fire the five callback slots (cur+0x20..): call fn(st, arg); clear the pair if it returns
 *    nonzero;
 *  - fire the action slot (cur+0x18): result 1 advances the script pointer, result 2 clears the
 *    slot, result 0 jumps straight to the frame tail;
 *  - then interpret the command script: cmd = entry->script; opcode = cmd[0];
 *    handler = data_020425ec[opcode]; hb = handler + cmd[1]*8. The 16-bit word at cmd+2 packs the
 *    instruction length (bits 0..10, in words) and a slot field (bits 11..15). When the field is
 *    non-zero it installs/clears hb+4 into entry slot[field] and advances; when zero it calls the
 *    handler and dispatches on its 0..6 result (0/6 -> frame tail, 1/2 -> clear+advance/loop,
 *    3 -> return 0, 4 -> pop the entry queue (st+0 -= entry+4; count--), 5/other -> loop).
 *  - the frame tail (shared by result 0 and case 6) pings func_020217d4 for the current
 *    controller (st+0x128, indexed by data_0204be04*0x104) and, when func_02020a84()==2 and
 *    func_02020a9c() has neither of bits 0x102, func_02020e20 for the same slot; returns 1.
 *
 * THUMB. Matching notes (all branch-orientation / register-web levers): the opcode is read back
 * through entry->script rather than the cached cmd so the entry pointer keeps the low register
 * (r4) and cmd the high one (r5), matching the original; every two-way test is written with the
 * fall-through arm the compiler keeps first (handler present, field!=0, callback result==0,
 * count>0); the result switch has an explicit default->loop so its own unsigned bound check covers
 * r>6 (no extra signed compare); and each frame-tail address is accumulated into one temp
 * (arg = base; arg += idx*0x104) so the base load is scheduled first and lands in the high
 * register like the original.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef int (*Fn)(void *st, int arg);

extern int  func_02020d44(void *st);
extern int  data_020425ec;
extern u8   data_0204be04;
extern void func_020217d4(int a);
extern int  func_02020a84(void);
extern int  func_02020a9c(void);
extern void func_02020e20(int a);

int func_02020e58(char *st)
{
    char *cur;
    char *e;
    char *cmd;
    char *hb;
    int i;
    int r;

    cur = st + 4 + *(int *)(st + 0x124) * 0x48;
    if (*(int *)(st + 0x588) != 0 && *(int *)(st + 0x584) != 0) {
        func_02020d44(st);
    }
    for (i = 0, e = cur; i < 5; i++, e += 8) {
        Fn f = *(Fn *)(e + 0x20);
        if (f != 0 && f(st, *(int *)(e + 0x24)) != 0) {
            *(int *)(e + 0x20) = 0;
            *(int *)(e + 0x24) = 0;
        }
    }
    {
        Fn af = *(Fn *)(cur + 0x18);
        if (af != 0) {
            r = af(st, *(int *)(cur + 0x1c));
            switch (r) {
            case 0:
                goto frame_tail;
            case 1:
                cmd = *(char **)(cur + 0x10);
                *(char **)(cur + 0x10) = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
                break;
            case 2:
                *(int *)(cur + 0x18) = 0;
                break;
            }
        }
    }

mainloop:
    e = st + 4 + *(int *)(st + 0x124) * 0x48;
    cmd = *(char **)(e + 0x10);
    {
        int h = (&data_020425ec)[*(u8 *)*(char **)(e + 0x10)];
        if (h != 0) {
            hb = (char *)h + *(u8 *)(cmd + 1) * 8;
        } else {
            *(int *)(e + 0x18) = 0;
            *(char **)(e + 0x10) = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
            goto mainloop;
        }
    }
    if (((*(u16 *)(cmd + 2) >> 0xb) & 0x1f) != 0) {
        Fn hf = *(Fn *)hb;
        r = hf(st, (int)(cmd + 4));
        {
            u8 field = (u8)((*(u16 *)(cmd + 2) >> 0xb) & 0x1f);
            if (r == 0) {
                *(int *)(e + (field << 3) + 0x18) = *(int *)(hb + 4);
                *(int *)(e + (field << 3) + 0x1c) = *(int *)(e + 0x1c);
            } else {
                *(int *)(e + (field << 3) + 0x18) = 0;
                *(int *)(e + (field << 3) + 0x1c) = 0;
            }
        }
        *(int *)(e + 0x18) = 0;
        *(char **)(e + 0x10) = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
        goto mainloop;
    } else {
        Fn hf = *(Fn *)hb;
        if (hf == 0) goto mainloop;
        r = hf(st, (int)(cmd + 4));
        switch ((unsigned)r) {
        case 0:
            *(int *)(e + 0x18) = *(int *)(hb + 4);
            goto frame_tail;
        case 1:
            *(int *)(e + 0x18) = 0;
            *(char **)(e + 0x10) = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
            goto mainloop;
        case 2:
            *(int *)(e + 0x18) = 0;
            goto mainloop;
        case 3:
            return 0;
        case 4:
            if (*(int *)(st + 0x124) > 0) {
                *(int *)st = *(int *)st - *(int *)(e + 4);
                *(int *)(st + 0x124) = *(int *)(st + 0x124) - 1;
                {
                    char *pe = st + 4 + *(int *)(st + 0x124) * 0x48;
                    *(int *)(pe + 0x18) = 0;
                    *(char **)(pe + 0x10) = *(char **)(pe + 0x10)
                        + ((*(u16 *)(*(char **)(pe + 0x10) + 2) & 0x7ff) << 2);
                }
                goto mainloop;
            }
            *(int *)(st + 0x12c) = 2;
            return 0;
        case 5:
            goto mainloop;
        case 6:
            *(char **)(e + 0x10) = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
            goto frame_tail;
        default:
            goto mainloop;
        }
    }

frame_tail:
    {
        int arg = *(int *)(st + 0x128) + 0x30;
        int idx = *(u8 *)&data_0204be04;
        arg += (idx + (idx << 6)) << 2;
        func_020217d4(arg);
    }
    if (func_02020a84() == 2 && (func_02020a9c() & 0x102) == 0) {
        int arg = *(int *)(st + 0x128) + 0x30;
        int idx = *(u8 *)&data_0204be04;
        arg += (idx + (idx << 6)) << 2;
        func_02020e20(arg);
    }
    return 1;
}
