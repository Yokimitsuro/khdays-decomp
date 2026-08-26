typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov022SelectionResult {
    u32 selectionFlags00;
    s32 type04;
    void *candidate08;
    void *comparison0c;
    u32 field10;
    void *source14;
    void *actor18;
    s32 scanDistance1c;
    s32 selectedIndex20;
    s32 selectedValue24;
} Ov022SelectionResult;

extern int func_ov022_020881d8(void);
extern int func_ov022_0208868c(void);
extern int func_020358f4(int slot, int parameter);
extern int func_ov022_02084fe8(u32 *selectionFlags, int slot);
extern void func_ov022_02086748(u8 *output, Ov022SelectionResult *selection);

int func_ov022_02086688(u8 *output, int slot)
{
    Ov022SelectionResult selection;

    if (func_ov022_020881d8() != 0 ||
        func_ov022_0208868c() != 0) {
        return 0;
    }

    selection.scanDistance1c = 0x9000;
    selection.selectedIndex20 = -1;
    selection.selectedValue24 = 0;
    if (func_020358f4(slot, 0x55) != 0) {
        selection.scanDistance1c =
            (s32)(((s64)selection.scanDistance1c * 0x1800 + 0x800) >> 12);
    }

    if (func_ov022_02084fe8(&selection.selectionFlags00, slot) == 0) {
        output[0] = 0;
        return 0;
    }

    func_ov022_02086748(output, &selection);
    return 1;
}
