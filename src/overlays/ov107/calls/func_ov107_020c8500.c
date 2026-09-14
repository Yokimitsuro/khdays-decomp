typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Path {
    char name[10];
} Path;

typedef struct Record {
    s16 field_00;
    u8 field_02;
    u8 field_03;
    u8 field_04;
    u8 field_05;
    u8 field_06;
    u8 field_07;
} Record;

typedef struct RecordFile {
    u16 field_00;
    Record records[1]; /* Variable-length file table. */
} RecordFile;

typedef struct StateEntry {
    s16 field_00;
    u8 field_02_low : 2;
    u8 field_02_high : 4;
    u8 field_02_top : 2;
    u8 field_03;
} StateEntry;

/* Partial description of the data referenced by AiState +0x1a0. */
typedef struct StateData {
    s16 field_00;
    char pad002[2];
    StateEntry field_04[8];
    s16 field_24[8];
    char pad034[0x53 - 0x34];
    u8 field_53;
    s16 field_54;
    s16 field_56;
    s16 field_58;
    s16 field_5a;
    u8 field_5c_bit0 : 1;
    u8 field_5c_bit1 : 1;
    u8 field_5c_bit2 : 1;
    u8 field_5c_high : 5;
    u8 field_5d;
    s16 field_5e;
    s16 field_60;
    s16 field_62;
} StateData;

struct AiState;
typedef void (*UpdateFn)(struct AiState *self, int index, int value);
typedef void (*NotifyFn)(struct AiState *self, int value);

typedef struct OutputEntry {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 field_03;
    u8 pad04[2];
} OutputEntry;

/* Partial AiState layout; the arrays are established by this function. */
typedef struct AiState {
    char pad000[0x54];
    int field_54;
    int field_58;
    char pad05c[0x19c - 0x5c];
    u8 field_19c;
    u8 field_19d;
    u8 field_19e;
    u8 field_19f;
    StateData *field_1a0;
    char pad1a4[0xa];
    u16 field_1ae;
    u16 field_1b0;
    int field_1b4[4];
    char pad1c4[0x14];
    UpdateFn field_1d8;
    char pad1dc[0x14];
    NotifyFn field_1f0;
    char pad1f4[0x24];
    s16 field_218;
    s16 field_21a;
    char pad21c[0x70];
    OutputEntry field_28c[8];
    s16 field_2bc[8];
    char pad2cc[0xc];
    int field_2d8;
    char pad2dc[0x94];
    s16 field_370[10];
} AiState;

extern const char data_ov107_020cb638[10];
extern int OS_IsThreadAvailable_0x020c9848(void);
extern void *func_0201ef9c(char *name, u32 heap);
extern void NNSi_FndFreeFromDefaultHeap(void *user_ptr);
extern int func_02020400(int value, int percent);
extern void func_ov107_020c8958(char *self, u32 mask);
typedef struct ModeFlags { u8 flags; } ModeFlags;
extern ModeFlags data_0204c240;

static inline s16 ReadRecord(const Record *record, u8 *byte3, u8 *byte4)
{
    s16 scale = record->field_00;
    *byte3 = record->field_03;
    *byte4 = record->field_04;
    return scale;
}

static inline int ApplyFlags(u8 flags, int value)
{
    int multiplier = flags & 4;
    if (multiplier != 0) {
        if (multiplier != 0) {
            multiplier = 3;
        } else {
            multiplier = 1;
        }
        value *= multiplier;
    }
    if ((flags & 2) == 0) {
        value = func_02020400(value * 0x50, 100);
    }
    return value;
}

void func_ov107_020c8500(AiState *self, int recordIndex)
{
    void *file;
    u8 recordByte4;
    u8 recordByte3;
    Path path;
    char *src;
    int i;
    const u8 *recordBytes;
    s16 coefficient;
    int scale;

    path = *(const Path *)data_ov107_020cb638;

    file = func_0201ef9c((char *)((((*(u32 *)((char *)OS_IsThreadAvailable_0x020c9848()
                                              + 0x80) + 0x8000) & 0xfffffc) << 7)
                                | ((u32)0x8000 << 16)
                                | (self->field_19c & 0x1ff)), 0xb);
    i = 0;
    src = (char *)file;
    for (; i < 10; i++) {
        self->field_370[i] = *(s16 *)src;
        src += 2;
    }
    NNSi_FndFreeFromDefaultHeap(file);

    self->field_19d = recordIndex;
    file = func_0201ef9c(path.name, 0xb);
    recordBytes = (const u8 *)file + 2;
    recordBytes += self->field_19d * 8;
    coefficient = *(const s16 *)recordBytes;
    recordByte3 = recordBytes[3];
    recordByte4 = recordBytes[4];
    NNSi_FndFreeFromDefaultHeap(file);

    if (self->field_1a0 != 0) {
        if (self->field_19d == 0) {
            scale = 1;
        } else {
            scale = ((coefficient * (self->field_1a0->field_00 << 4)) + 0x800) >> 12;
            if (scale <= 0) {
                scale = 1;
            }
        }

        scale = ApplyFlags(data_0204c240.flags, scale);
        if (scale < 1) {
            scale = 1;
        }
        self->field_218 = (s16)scale;
        self->field_21a = (s16)scale;

        for (i = 0; i < 8; i++) {
            if (self->field_1a0->field_04[i].field_00 != 0) {
                int value;
                if (self->field_19d == 0) {
                    value = 0;
                } else {
                    value = (((self->field_1a0->field_04[i].field_00 << 4)
                              * recordByte3) + 0x800) >> 12;
                }
                if (self->field_1d8 != 0) {
                    self->field_1d8(self, i, value);
                }
                self->field_28c[i].field_01 = self->field_1a0->field_04[i].field_02_low;
                self->field_28c[i].field_02 = self->field_1a0->field_04[i].field_02_high;
                self->field_28c[i].field_03 = self->field_1a0->field_04[i].field_03;
            }
        }

        for (i = 0; i < 8; i++) {
            int value;
            if (self->field_19d == 0) {
                value = 0;
            } else {
                value = ((self->field_1a0->field_24[i] << 4)
                         * recordByte4 + 0x800) >> 12;
            }
            self->field_2bc[i] = (s16)value;
        }

        {
            int value = self->field_1a0->field_53;
            if (self->field_1f0 != 0) {
                self->field_1f0(self, value);
            }
        }
        if (self->field_1a0->field_5c_bit1 != 0) {
            self->field_1ae |= 0x20;
        }
        if (self->field_1a0->field_5c_bit2 != 0) {
            self->field_1ae |= 0x40;
        }
        if (self->field_1a0->field_54 >= 0x100) {
            self->field_1b0 |= 8;
        }
        if (self->field_1a0->field_56 >= 0x100) {
            self->field_1b0 |= 0x80;
        }
        if (self->field_1a0->field_58 >= 0x100) {
            self->field_1b0 |= 0x800;
        }
        if (self->field_1a0->field_5a >= 0x100) {
            self->field_1b0 |= 4;
        }
        self->field_1b4[0] = self->field_1a0->field_56 << 4;
        self->field_1b4[1] = self->field_1a0->field_54 << 4;
        self->field_1b4[2] = self->field_1a0->field_58 << 4;
        self->field_1b4[3] = self->field_1a0->field_5a << 4;
        self->field_19f = self->field_1a0->field_5d;
        self->field_54 = self->field_1a0->field_5e << 4;
        self->field_58 = self->field_1a0->field_60 << 4;
        self->field_2d8 = self->field_1a0->field_62 << 4;
        func_ov107_020c8958((char *)self, 0);
    } else {
        self->field_218 = 1;
        self->field_21a = 1;
        src = (char *)self;
        for (i = 0; i < 8; i++, src += 6) {
            if (self->field_1d8 != 0) {
                self->field_1d8(self, i, 0);
            }
            src[0x28d] = 0;
            src[0x28e] = 0;
        }
        for (i = 0; i < 8; i++) {
            self->field_2bc[i] = 0;
        }
        for (i = 0; i < 4; i++) {
            self->field_1b4[i] = 0;
        }
        if (self->field_1f0 != 0) {
            self->field_1f0(self, 0);
        }
        func_ov107_020c8958((char *)self, 0);
    }
}
