/*
 * func_ov002_0207c020 - queue a "first touch" input record for an idle object (ARM).
 *
 * Only acts while the object is idle (both the pending flag and the touch counter are 0). It builds
 * a small event record { kind=1, code=ev[0] } on the stack and submits it through
 * func_ov002_020766e0 (tag 6). On a successful submit it bumps the touch counter and raises the
 * pending flag. Always returns 0; the two idle-guard/submit-fail exits share one return so mwcc
 * branches to a single tail as the ROM does.
 */
typedef struct {
    char _0[0x2c0];
    unsigned char touchCount;   /* +0x2c0 */
    unsigned char pending;      /* +0x2c1 */
} Ov002InputObj;

extern int func_ov002_020766e0(int obj, int record, int tag);

int func_ov002_0207c020(Ov002InputObj *obj, unsigned char *ev)
{
    unsigned char rec[8];
    if (obj->pending != 0 || obj->touchCount != 0)
        goto ret0;
    rec[0] = 1;
    rec[4] = ev[0];
    if (func_ov002_020766e0((int)obj, (int)rec, 6) == 0)
        goto ret0;
    obj->touchCount = obj->touchCount + 1;
    obj->pending = 1;
    return 0;
ret0:
    return 0;
}
