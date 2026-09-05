typedef unsigned char u8;
typedef unsigned int u32;

struct Ov008MenuSlot {
    u8 pad00[2];
    u8 padFlags : 2;
    u8 unavailable : 1;
    u8 padFlagsHi : 5;
    u8 state;
};

extern u32 func_ov008_0204ec18(void);
extern int func_ov008_0204ebf0(void);
extern int func_ov008_0207baf8(void);
extern struct Ov008MenuSlot *func_ov008_0204ecd8(int slot);

int
func_ov008_020570c0(void)
{
    int slot;
    int selectedCount = 0;
    int readyCount = 0;
    u32 selectedMask = func_ov008_0204ec18();

    if (func_ov008_0204ebf0() == 0) {
        return 0;
    }
    if (func_ov008_0207baf8() != 0) {
        return 1;
    }

    for (slot = 1; slot < 4; slot++) {
        struct Ov008MenuSlot *record = func_ov008_0204ecd8(slot);

        if ((selectedMask & (1 << slot)) != 0) {
            selectedCount++;
        }
        if (record->unavailable == 0 && record->state == 8) {
            readyCount++;
        }
    }

    if (selectedCount <= 0) {
        return 0;
    }
    return selectedCount == readyCount;
}
