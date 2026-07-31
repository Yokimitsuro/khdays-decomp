/* func_020314a4 = MsgQueue_MarkSlotReceived (ARM). For the incoming message whose
 * handle == param1 destined for local player param2, record that remote player
 * `bit` has acknowledged it (slot->flags |= 1 << bit). When every expected player
 * has acked -- all bits set (== the expected mask from func_01fff974) while the
 * session is ready, or just bit0 when not ready -- mark the slot complete in the
 * queue's free/done mask at ctx+0xc. No-op if param2 is not the local player, the
 * handle is not present, or the slot is already marked complete.
 *
 * ctx (data_0204c230): done-mask u32 @0xc, MsgSlot[32] @0x10 (stride 6). The scan
 * walks a pointer from ctx+0xc reading the handle at +4 (== slot[i].handle), while
 * the matched slot pointer is recomputed as ctx+0x10 + i*6. flags |= 1<<bit is
 * written without a (u8) cast so mwcc fuses `orr rD, rN, #1, lsl bit`. */
typedef struct { unsigned short handle; unsigned short size; unsigned char type; unsigned char flags; } MsgSlot;

extern char *data_0204c230;
extern unsigned short func_02030788(void);   /* Session_GetLocalPlayerIndex */
extern int func_02030694(void);              /* Session_IsReady */
extern unsigned short func_01fff974(void);   /* expected-ack mask */

void func_020314a4(unsigned int handle, unsigned int playerIndex, unsigned int bit)
{
    char *ctx = data_0204c230;
    MsgSlot *found = 0;
    char *p;
    int i;
    int done = 0;

    if (playerIndex != func_02030788()) {
        return;
    }
    p = ctx + 0xc;
    for (i = 0; i < 0x20; i++) {
        if (handle == *(unsigned short *)(p + 4)) {
            found = (MsgSlot *)(ctx + 0x10 + i * 6);
            break;
        }
        p += 6;
    }
    if (found == 0) {
        return;
    }
    if ((*(unsigned int *)(ctx + 0xc) & (0x80000000U >> i)) != 0) {
        return;
    }
    found->flags |= 1 << bit;
    if (func_02030694() != 0) {
        if (found->flags == func_01fff974()) {
            done = 1;
        }
    } else if ((found->flags & 1) > 0) {
        done = 1;
    }
    if (done != 0) {
        *(unsigned int *)(ctx + 0xc) |= (0x80000000U >> i);
    }
}
