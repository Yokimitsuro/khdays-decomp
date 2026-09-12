/* Ov022_UnpackChannelGrid -- read a channel grid and its channels out of a
 * stream of words, then reset the grid.
 *
 * Every field of the stream is one 32-bit word, narrowed to the field it
 * lands in. The header gives the mode and the channel count; the channels
 * are allocated from the default heap and each read in turn: five words,
 * two flag bits, a level clamped to 3, and a tail whose layout the grid
 * mode picks (mode 0 four words and a halfword and two bytes, mode 1 a
 * byte, a word and two bytes, mode 2 two bytes and six words). The grid is
 * then reset with every cell cleared.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

#define MODE_COUNT 3
#define LEVEL_MAX 3

/* Ov022ChannelTail0 */
struct ChannelTail0 {
    int nA;                      /* 0x00 */
    int nB;                      /* 0x04 */
    int nC;                      /* 0x08 */
    int nD;                      /* 0x0c */
    u16 nE;                      /* 0x10 */
    u8 nF;                       /* 0x12 */
    u8 nG;                       /* 0x13 */
};

/* Ov022ChannelTail1 */
struct ChannelTail1 {
    u8 nA;                       /* 0x00 */
    u8 pad01[3];
    int nB;                      /* 0x04 */
    u8 nC;                       /* 0x08 */
    u8 nD;                       /* 0x09 */
};

/* Ov022ChannelTail2 */
struct ChannelTail2 {
    u8 nA;                       /* 0x00 */
    u8 nB;                       /* 0x01 */
    u8 pad02[2];
    int nC;                      /* 0x04 */
    int nD;                      /* 0x08 */
    int nE;                      /* 0x0c */
    int nF;                      /* 0x10 */
    int nG;                      /* 0x14 */
    int nH;                      /* 0x18 */
};

/* Ov022Channel */
struct Channel {
    int nA;                      /* 0x00 */
    int nB;                      /* 0x04 */
    int nC;                      /* 0x08 */
    int nD;                      /* 0x0c */
    int nE;                      /* 0x10 */
    u8 bFlag0 : 1;               /* 0x14 bit 0 */
    u8 bFlag1 : 1;               /* bit 1 */
    u8 nRest14 : 6;
    s8 nLevel;                   /* 0x15 */
    u8 pad16[2];
    union {
        struct ChannelTail0 t0;
        struct ChannelTail1 t1;
        struct ChannelTail2 t2;
    } tail;                      /* 0x18 */
    u8 pad34[0x14];
};

/* Ov022ChannelGrid */
struct ChannelGrid {
    u16 nId;                     /* 0x00 */
    u8 nMode;                    /* 0x02 */
    u8 nField03;                 /* 0x03 */
    int nField04;                /* 0x04 */
    int nField08;                /* 0x08 */
    int nField0c;                /* 0x0c */
    int nField10;                /* 0x10 */
    int nField14;                /* 0x14 */
    int nField18;                /* 0x18 */
    int nField1c;                /* 0x1c */
    u8 nField20;                 /* 0x20 */
    u8 pad21[3];
    int nField24;                /* 0x24 */
    int nField28;                /* 0x28 */
    int nField2c;                /* 0x2c */
    short nCount;                /* 0x30 */
    u8 pad32[2];
    struct Channel *pChannels;   /* 0x34 */
};

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void func_ov022_020b064c(struct ChannelGrid *pGrid);                     /* Ov022_ResetChannelGrid */

void func_ov022_020b0160(struct ChannelGrid *pGrid, int nUnused, int *pSrc)
{
    struct Channel *pChannel;
    struct ChannelTail0 *pTail0;
    struct ChannelTail1 *pTail1;
    struct ChannelTail2 *pTail2;
    int i;

    pGrid->nId = pSrc[0];
    pGrid->nMode = pSrc[1];
    pGrid->nField03 = pSrc[2];
    pGrid->nField04 = pSrc[3];
    pGrid->nField08 = pSrc[4];
    pGrid->nField0c = pSrc[5];
    pGrid->nField10 = pSrc[6];
    pGrid->nField14 = pSrc[7];
    pGrid->nField18 = pSrc[8];
    pGrid->nField1c = pSrc[9];
    pGrid->nField20 = pSrc[10];
    pGrid->nField24 = pSrc[11];
    pGrid->nField28 = pSrc[12];
    pGrid->nField2c = pSrc[13];
    pGrid->nCount = pSrc[14];
    pSrc += 15;
    pGrid->pChannels = NNSi_FndAllocFromDefaultExpHeap(pGrid->nCount * sizeof(struct Channel));
    for (i = 0; i < pGrid->nCount; i++) {
        pChannel = &pGrid->pChannels[i];
        pChannel->nA = pSrc[0];
        pChannel->nB = pSrc[1];
        pChannel->nC = pSrc[2];
        pChannel->nD = pSrc[3];
        pChannel->nE = pSrc[4];
        pChannel->bFlag0 = (u8)pSrc[5];
        pChannel->bFlag1 = (u8)pSrc[6];
        pChannel->nLevel = pSrc[7];
        pSrc += 8;
        if (pChannel->nLevel >= LEVEL_MAX + 1) {
            pChannel->nLevel = LEVEL_MAX;
        }
        switch (pGrid->nMode) {
        case 0:
            pTail0 = &pChannel->tail.t0;
            pTail0->nA = pSrc[0];
            pTail0->nB = pSrc[1];
            pTail0->nC = pSrc[2];
            pTail0->nD = pSrc[3];
            pTail0->nE = pSrc[4];
            pTail0->nF = pSrc[5];
            pTail0->nG = pSrc[6];
            pSrc += 7;
            break;
        case 1:
            pTail1 = &pChannel->tail.t1;
            pTail1->nA = pSrc[0];
            pTail1->nB = pSrc[1];
            pTail1->nC = pSrc[2];
            pTail1->nD = pSrc[3];
            pSrc += 4;
            break;
        case 2:
            pTail2 = &pChannel->tail.t2;
            pTail2->nA = pSrc[0];
            pTail2->nB = pSrc[1];
            pTail2->nC = pSrc[2];
            pTail2->nD = pSrc[3];
            pTail2->nE = pSrc[4];
            pTail2->nF = pSrc[5];
            pTail2->nG = pSrc[6];
            pTail2->nH = pSrc[7];
            pSrc += 8;
            break;
        }
    }
    func_ov022_020b064c(pGrid);
}
