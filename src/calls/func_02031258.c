/*
 * MsgQueue_SendGate - route an outgoing message by session state and type.
 *
 * Reads the current session/card state (CARD_GetResultCode). Behaviour:
 *   - state 2: for message types 3 and 0x12 only, pack a header word in a stack
 *     buffer (bits 1-5 = type, bits 6-15 = size), append the payload after it and
 *     hand it to the local dispatcher func_02030d2c; do NOT enqueue.
 *   - state 3: enqueue only for the whitelisted message types (the switch); the
 *     rest are dropped.
 *   - any other state: enqueue unconditionally.
 * Enqueue goes through MsgQueue_Enqueue (func_02030fdc) and its result is returned.
 *
 * The header is a packed 16-bit field {f0:1, type:5, size:10}. `size` is taken as
 * `unsigned short` so the field write is a clean insert (a wider source would add a
 * redundant halfword narrow); the two field writes go through an inline
 * (MsgHdr *)buf cast so the buffer pointer is rematerialised for the dispatcher
 * argument rather than held across the copy call.
 */

extern int CARD_GetResultCode_0x0203065c(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void func_02030d2c(int hdr, int size);
extern int func_02030fdc(int type, int size, unsigned short *hdr);

typedef struct {
    unsigned short f0:1;
    unsigned short type:5;
    unsigned short size:10;
} MsgHdr;

int func_02031258(int param_1, unsigned short *param_2, unsigned short param_3)
{
    unsigned short buf[48];
    int doSend;
    int ret;

    ret = 0;
    doSend = 1;
    switch (CARD_GetResultCode_0x0203065c()) {
    case 2:
        if (param_1 == 3 || param_1 == 0x12) {
            ((MsgHdr *)buf)->type = param_1;
            ((MsgHdr *)buf)->size = param_3;
            MI_CpuCopy8(param_2, (unsigned char *)buf + 2, param_3);
            func_02030d2c((int)buf, param_3 + 2);
            doSend = 0;
        }
        break;
    case 3:
        doSend = 0;
        switch (param_1) {
        case 0: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        case 0xb: case 0xd: case 0xe: case 0x10: case 0x11: case 0x12: case 0x13:
            doSend = 1;
            break;
        default:
            break;
        }
        break;
    }
    if (doSend) {
        ret = func_02030fdc(param_1, param_3, param_2);
    }
    return ret;
}
