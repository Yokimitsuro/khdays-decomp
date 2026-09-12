typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;

typedef struct {
    u8 id;
    struct {
        u8 bit0 : 1;
        u8 bit1 : 1;
        u8 rest : 6;
    } flags;
    u8 mask;
    s8 mode;
    u32 ownerTag;
    u8 pad[4];
} Ov107Slot;

typedef struct {
    u8 pad00[0x4c];
    s16 count;          /* +0x4c */
    u8 pad4e[2];
    Ov107Slot slots[1]; /* +0x50 */
} Ov107Object;

extern void OS_Terminate(void);

int func_ov107_020c1d3c(Ov107Object *obj, u8 id, u8 mask, int unused, s8 mode, u32 ownerTag) {
    int index = obj->count;

    if (index >= 8) {
        OS_Terminate();
        return -1;
    }

    obj->slots[index].id = id;
    obj->slots[index].flags.bit0 = 1;
    obj->slots[index].flags.bit1 = 0;
    obj->slots[index].mask = mask;
    obj->slots[index].mode = mode;
    obj->slots[index].ownerTag = ownerTag;

    obj->count = obj->count + 1;
    return index;
}
