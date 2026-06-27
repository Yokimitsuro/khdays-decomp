extern void SND_PrepareSeq(int playerNo);
extern void SND_SetTrackAllocatableChannel(int playerNo, unsigned int mask, int unused);
extern void func_0201a680(void *p);
extern unsigned int func_020089e8(void);

typedef struct {
    char _0[0x1c];
    int hasMask;
} SeqInfo_0201a568;

typedef struct {
    char _0[4];
    SeqInfo_0201a568 *seqInfo;
    char _8[0x24];
    unsigned char state;
    char _2d[2];
    unsigned char ready;
    unsigned int tag;
    char _34[8];
    unsigned char player;
} Obj0201a568;

void func_0201a568(Obj0201a568 *p)
{
    SeqInfo_0201a568 *seqInfo = p->seqInfo;

    SND_PrepareSeq(p->player);

    if (seqInfo->hasMask != 0)
        SND_SetTrackAllocatableChannel(p->player, 0xffff, seqInfo->hasMask);

    func_0201a680(p);
    p->tag = func_020089e8();
    p->ready = 1;
    p->state = 1;
}
