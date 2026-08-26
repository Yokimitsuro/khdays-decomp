typedef struct Ov022Bits4e8 {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char rest : 3;
} Ov022Bits4e8;

typedef struct Ov022RootBits {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char rest : 5;
} Ov022RootBits;

typedef struct Ov022ResourceWord {
    unsigned int low4 : 4;
    unsigned int mid10 : 10;
    unsigned int high10 : 10;
    unsigned int bit24 : 1;
    unsigned int bit25 : 1;
    unsigned int bit26 : 1;
    unsigned int rest : 5;
} Ov022ResourceWord;

typedef struct Ov022RowFlags {
    unsigned short low15 : 15;
    unsigned short highBit : 1;
} Ov022RowFlags;

typedef struct Ov022ResourceEntry {
    short facing;
    unsigned short flags;
    unsigned int packedWord;
    unsigned short packedHalfword;
    unsigned short reserved;
} Ov022ResourceEntry;

typedef struct Ov022ResourceView {
    char padding000[0x14];
    Ov022ResourceEntry entries[1];
} Ov022ResourceView;

typedef struct Ov022Node {
    unsigned long long flags;
    char padding008[0xa];
    unsigned short field012;
    char padding014[4];
    unsigned short flags018;
    unsigned short flags01a;
    char padding01c[0x45c];
    short facing478;
    char padding47a[0x5c];
    unsigned char packedLow4_4d6;
    char padding4d7;
    unsigned short packedMid10_4d8;
    unsigned short packedHigh10_4da;
    char padding4dc[0xc];
    Ov022Bits4e8 stateBits4e8;
    char padding4e9[7];
    unsigned char packedLow2_4f0;
    unsigned char packedHigh_4f1;
    unsigned char packedLowShift3_4f2;
    unsigned char padding4f3;
    int packedBit2_4f4;
    char padding4f8[0x19c];
    unsigned char stateFlags694;
} Ov022Node;

typedef struct Ov022Root {
    unsigned int flags;
    char padding004[0x38];
    Ov022RootBits stateBits;
} Ov022Root;

extern char data_ov022_020b2e78[];

extern void *func_ov022_0208a278(void);
extern void func_ov022_020acfa4(int node, int bit2, int rowOffset,
                                int packedLowShift3);

void func_ov022_02087890(int nodeAddress, int index)
{
    Ov022Node *node = (Ov022Node *)nodeAddress;
    char *resource;
    Ov022Root *root = *(Ov022Root **)(data_ov022_020b2e78 + 4);
    unsigned char *available;

    resource = func_ov022_0208a278();
    available = (unsigned char *)(resource + 0x10);

    if (available[index] != 0) {
        {
            char *packedBase;
            int rowOffset;
            char *record6;
            unsigned char sourceBit26;

            record6 = resource + index * 6;
            rowOffset = index;
            rowOffset *= 0xc;
            *(unsigned short *)((char *)node + 0x18) =
                *(unsigned short *)(record6 + 0x86);
            *(unsigned short *)((char *)node + 0x1a) =
                *(unsigned short *)(record6 + 0x84);
            packedBase = resource + 0x18;
            node->packedLow4_4d6 =
                ((Ov022ResourceWord *)(packedBase + rowOffset))->low4;
            node->packedMid10_4d8 =
                ((Ov022ResourceWord *)(packedBase + rowOffset))->mid10;
            node->packedHigh10_4da =
                ((Ov022ResourceWord *)(packedBase + rowOffset))->high10;
            node->stateBits4e8.bit2 =
                ((Ov022ResourceWord *)(packedBase + rowOffset))->bit24;
            node->stateBits4e8.bit4 =
                ((Ov022ResourceWord *)(packedBase + rowOffset))->bit25;
            sourceBit26 =
                ((Ov022ResourceWord *)(packedBase + rowOffset))->bit26;
            node->stateFlags694 =
                (node->stateFlags694 & ~8) |
                (((unsigned int)sourceBit26 << 31) >> 28);

            if (node->field012 == 0) {
                node->stateFlags694 &= ~8;
            }
        }

        {
            int secondRowOffset;
            char *secondPackedBase;
            unsigned int packedLowShift3;

            secondRowOffset = index;
            secondRowOffset *= 0xc;
            secondPackedBase = resource + 0x1c;
            node->stateBits4e8.bit0 =
                ((Ov022RowFlags *)&((Ov022ResourceView *)resource)->entries[index].flags)->highBit;
            node->facing478 =
                ((Ov022ResourceView *)resource)->entries[index].facing;
            node->packedLow2_4f0 =
                (unsigned int)(*(unsigned short *)(secondPackedBase + secondRowOffset) << 30) >> 30;
            node->packedHigh_4f1 =
                (unsigned int)(*(unsigned short *)(secondPackedBase + secondRowOffset) << 16) >> 24;
            packedLowShift3 =
                (unsigned int)(*(unsigned short *)(secondPackedBase + secondRowOffset) << 24) >> 27;
            node->packedLowShift3_4f2 = packedLowShift3;
            node->packedBit2_4f4 =
                (unsigned int)(*(unsigned short *)(secondPackedBase + secondRowOffset) << 29) >> 31;
            func_ov022_020acfa4((int)node, node->packedBit2_4f4,
                                secondRowOffset, packedLowShift3);
        }

        available[index] = 0;
        if ((root->flags & 1) != 0) {
            node->flags018 = 0;
            node->flags01a = 0;
        }
        if (root->stateBits.bit0 && index == 0) {
            node->flags018 = 0;
            node->flags01a = 0;
        }
        if (root->stateBits.bit2) {
            node->flags018 = 0;
            node->flags01a = 0;
        }
    }
}

