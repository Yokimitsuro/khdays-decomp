/* Resets save record `slot` (func_02035328), then stamps `kind` into byte 1 of its 8-byte header
 * (copied out and back as a whole); records 1 and 2 also clear their 0x48-byte extra block
 * (data_0204c500).
 * Codegen: built with `opt_common_subs off` (push/pop scoped); with CSE on mwcc swaps the record
 * base and element pointer registers of the 8-byte header copy. */
#pragma thumb on
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 id;
    u8 kind;
    u16 w1;
    u16 w2;
    u16 w3;
} SlotHeader;

typedef struct {
    SlotHeader header;
    u8 pad[0x104 - 8];
} SlotRecord;

typedef struct {
    u8 data[0x48];
} SlotExtra;

extern void func_02035328(int slot, int a, int b);
extern void MI_CpuFill8(void *dst, u8 val, unsigned int size);
extern SlotRecord data_0204c678[];
extern SlotExtra data_0204c500[];

#pragma push
#pragma opt_common_subs off
void func_020353e0(int slot, u8 kind, int a, int b)
{
    SlotHeader h;

    func_02035328(slot, a, b);
    h = data_0204c678[slot].header;
    h.kind = kind;
    data_0204c678[slot].header = h;
    if (slot > 0 && slot - 1 < 2) {
        MI_CpuFill8(&data_0204c500[slot - 1], 0, sizeof(SlotExtra));
    }
}
#pragma pop
