/*
 * Ov002_UpdatePartyEntries - per-frame party/entry updater in the ov002 gameplay slice (dep of
 * the constructor func_ov002_020679d4). No-op unless the pending slot at root-context+0x8bcc is
 * live (!= -1).
 *
 * Publishes a scaled timeout ((Ov002_GetTimeoutTicks()<<6)/0x82ea) into data_0204c4d8+0x14, then,
 * unless the phase at ctx+0x8bb4 is 0 or 3, walks the four 0x104-byte entries at data_0204c678:
 * copies the 8-byte head into a scratch, recomputes its 4th halfword from func_ov022_020882e0 (or
 * the entry's +0xe field, gated on func_ov022_020886f8 and data_0204c240 & 4), writes the head
 * back, and - depending on the same flag - refreshes the entry (func_01fffde0) and, if
 * func_ov002_02069a7c reports it changed, notifies func_ov002_02069b14.
 *
 * THUMB. The 64-bit divide is the runtime helper func_02020368(u64, divisor, 0) called directly
 * (the / operator would emit an unresolved _ll_sdiv). The head read/write are struct copies so
 * mwcc keeps the read and write cursors in separate registers (r7/r5, same address); with fp++
 * emitted between the two 0x104 increments the divide constant is re-materialized, matching the
 * original. state==0||3 is a materialized bool.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct { u16 a, b, c, d; } Head;

extern int  data_ov002_0207fa00;
extern unsigned long long func_ov002_0206f604(void);
extern int  func_02020368(unsigned long long value, unsigned int divisor, int arg3);
extern int  func_01fffde0(int i);
extern int  func_ov022_020882e0(int i);
extern int  func_ov022_020886f8(int i);
extern int  func_ov002_02069a7c(int i);
extern void func_ov002_02069b14(int i);
extern int  data_0204c4d8;
extern u16  data_0204c678;
extern u8   data_0204c240;

void func_ov002_020692a8(void)
{
    char *ctx = (char *)data_ov002_0207fa00;
    unsigned long long t;
    int i;
    Head buf;
    int flags[4];
    int *fp;
    char *rdp;
    char *wrp;

    if (*(int *)(ctx + 0x8bcc) == -1) return;
    t = func_ov002_0206f604();
    *(int *)((char *)&data_0204c4d8 + 0x14) = func_02020368(t << 6, 0x82ea, 0);
    {
        int state = *(int *)(ctx + 0x8bb4);
        int done = 0;
        if (state == 0 || state == 3) done = 1;
        if (done != 0) return;
    }
    i = 0;
    fp = flags;
    rdp = (char *)&data_0204c678;
    wrp = (char *)&data_0204c678;
    for (; i < 4; i++) {
        if (func_01fffde0(i) == 0) return;
        buf = *(Head *)rdp;
        buf.d = func_ov022_020882e0(i);
        *fp = 0;
        if (buf.d == 0) {
            buf.d = *(u16 *)(wrp + 0xe);
            *fp = 1;
        } else if (flags[0] != 0 && (data_0204c240 & 4) == 0 && func_ov022_020886f8(i) != 0) {
            buf.d = *(u16 *)(wrp + 0xe);
        }
        *(Head *)wrp = buf;
        if ((*fp == 0 && (data_0204c240 & 4) != 0) ||
            (flags[0] == 0 && (data_0204c240 & 4) == 0)) {
            func_01fffde0(i);
            if (func_ov002_02069a7c(i) != 0) {
                func_ov002_02069b14(i);
            }
        }
        rdp += 0x104;
        fp++;
        wrp += 0x104;
    }
}
