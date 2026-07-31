/*
 * Ov002_UpdatePendingRequest - advance the pending-request record at root-context+0x8dc0
 * (a u16 slot at +0x8dc0 and a u8 tag at +0x8dc2). Called from the ov002 gameplay constructor
 * (func_ov002_020679d4).
 *
 * If the session is active (func_02030694 != 0) and the record's tag matches the current
 * source id (func_01fff974): when the slot is unallocated (0xffff) it allocates a new one via
 * func_ov002_0206fb84(0x1a, ...) and stores it; otherwise it polls func_02031440(slot) and,
 * if that returns 0 (complete), marks the request done. If the session is NOT active: when the
 * tag differs it builds a 2-byte notification (tag 0x19 + func_02030788()) and sends it via
 * func_02031258(7, ..., 2); when it matches it marks the request done.
 *
 * On "done" it resets the slot to 0xffff and the tag to 0 and returns the follow-up handler
 * func_ov002_02067f78; otherwise it returns NULL. THUMB. The slot value is passed to
 * func_02031440 (it is not a no-arg call), which is what keeps it in r0 across the poll.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

extern int  func_02030694(void);
extern int  func_01fff974(void);
extern u16  func_ov002_0206fb84(int kind, void *out);
extern int  func_02031440(int slot);
extern int  func_02030788(void);
extern void func_02031258(int a, void *b, int c);
extern void func_ov002_02067f78(void);
extern int  data_ov002_0207fa00;

void *func_ov002_02067d9c(void)
{
    char *ctx = (char *)data_ov002_0207fa00;
    char local[4];
    int ok = 0;

    if (func_02030694() != 0) {
        if (*(u8 *)(ctx + 0x8dc2) == func_01fff974()) {
            u16 slot = *(u16 *)(ctx + 0x8dc0);
            if (slot == 0xffff) {
                *(u16 *)(ctx + 0x8dc0) = func_ov002_0206fb84(0x1a, local);
            } else {
                if (func_02031440(slot) == 0) ok = 1;
            }
        }
    } else {
        if (*(u8 *)(ctx + 0x8dc2) != func_01fff974()) {
            local[1] = 0x19;
            local[2] = func_02030788();
            func_02031258(7, local + 1, 2);
        } else {
            ok = 1;
        }
    }
    if (ok != 0) {
        *(u16 *)(ctx + 0x8dc0) = 0xffff;
        *(u8 *)(ctx + 0x8dc2) = 0;
        return (void *)func_ov002_02067f78;
    }
    return 0;
}
