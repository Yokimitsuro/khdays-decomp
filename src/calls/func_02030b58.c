/*
 * MsgQueue_RecvDispatch - handle one incoming message from a peer.
 *
 * The message starts with a header byte packed as {kind:2, channel:3, hi:3}.
 *   - kind 2 (ack): mark the matching outgoing slot received
 *     (MsgQueue_MarkSlotReceived, func_020314a4).
 *   - kind 1 (data): if the message sequence (halfword at +2) equals the channel's
 *     expected receive counter (ctx+0x60, stride 2), invoke the registered channel
 *     handler - a function pointer in the table at ctx+0xc indexed by the sub-id
 *     byte at +1 - as handler(payload = msg+4, size - 4), stash the message pointer
 *     at ctx+0x70 for the handler, then bump the counter (wrapping at 0xffff). If
 *     our counter has caught up to (>=) the sender's sequence, send an ack back
 *     through MsgQueue_SendGate (func_02031258, type 0xb).
 *
 * ctx = data_0204c22c (the pool word holds the ctx pointer; used directly).
 */

extern int *data_0204c22c;
extern int func_02030788(void);
extern void func_020314a4(unsigned int handle, unsigned int playerIndex, unsigned int bit);
extern int func_02031258(int type, unsigned short *hdr, unsigned short size);

typedef struct {
    unsigned char kind:2, ch:3, hi:3;
} RxHdr;

typedef struct {
    unsigned char kind:2, mid:3, hi:3;
    unsigned char type;
    unsigned short seq;
} AckMsg;

void func_02030b58(unsigned char *param_1, int param_2)
{
    int *ctx = data_0204c22c;
    RxHdr *m = (RxHdr *)param_1;
    unsigned int ch;
    AckMsg msg;

    switch (m->kind) {
    case 1:
        ch = m->ch;
        if (*(unsigned short *)((char *)ctx + ch * 2 + 0x60) == *(unsigned short *)(param_1 + 2)) {
            if (*(int *)((char *)ctx + param_1[1] * 4 + 0xc) != 0) {
                *(unsigned char **)((char *)ctx + 0x70) = param_1;
                (*(void (**)(unsigned char *, unsigned int))((char *)ctx + param_1[1] * 4 + 0xc))(param_1 + 4, (param_2 - 4) & 0xff);
            }
            ch = m->ch;
            *(unsigned short *)((char *)ctx + 0x60 + ch * 2) = *(unsigned short *)((char *)ctx + 0x60 + ch * 2) + 1;
            ch = m->ch;
            if (*(unsigned short *)((char *)ctx + ch * 2 + 0x60) == 0xffff) {
                *(unsigned short *)((char *)ctx + ch * 2 + 0x60) = 0;
            }
        }
        ch = m->ch;
        if (*(unsigned short *)(param_1 + 2) <= *(unsigned short *)((char *)ctx + ch * 2 + 0x60)) {
            msg.kind = 2;
            msg.hi = func_02030788();
            msg.mid = m->ch;
            msg.type = 0xb;
            msg.seq = *(unsigned short *)(param_1 + 2);
            func_02031258(0xb, (unsigned short *)&msg, 4);
        }
        break;
    case 2:
        func_020314a4(*(unsigned short *)(param_1 + 2), m->ch, m->hi);
        break;
    }
}
