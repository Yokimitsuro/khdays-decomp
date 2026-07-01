typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void GX_VRAMCNT_SetLCDC_(u32 bankBits);

struct VRAMState {
    u16 field0;
    u16 pad2;
    u16 pad4;
    u16 pad6;
    u16 pad8;
    u16 fieldA;
};

extern struct VRAMState data_020446d4;

static inline void writeE(u8 v) { *(volatile u8 *)0x04000244 = v; }
static inline void writeF(u8 v) { *(volatile u8 *)0x04000245 = v; }
static inline void writeG(u8 v) { *(volatile u8 *)0x04000246 = v; }

void GX_BeginLoadOBJExtPltt(int bank) {
    data_020446d4.field0 = (u16)(((data_020446d4.field0 | data_020446d4.fieldA)) & ~bank);
    data_020446d4.fieldA = (u16)bank;
    switch (bank) {
    case 0x00:
        break;
    case 0x60:
        writeG(0x8b);
        /* fallthrough */
    case 0x20:
        writeF(0x83);
        break;
    case 0x40:
        writeG(0x83);
        break;
    case 0x70:
        writeG(0x9b);
        /* fallthrough */
    case 0x30:
        writeF(0x93);
        /* fallthrough */
    case 0x10:
        writeE(0x83);
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_020446d4.field0);
}
