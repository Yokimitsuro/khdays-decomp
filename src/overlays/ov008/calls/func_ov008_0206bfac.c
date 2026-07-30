/* func_ov008_0206bfac -- Ov008_LayoutMissionEntries (752 B, 51 relocs).
 * Builds the mission/pause menu entry layout. Copies two 4-word template arrays (a tag list from
 * data_ov008_0208f648 and a transform seed from data_ov008_0208f658), fetches the layout object,
 * and runs a long FindEntryById + slot-op sequence: seeds the transform (func_ov008_02054744),
 * loads and processes blocks (0x28/0x29 tags), positions entry 0x2b by (0xf0000 - entry.f4),
 * copies two 8-byte glyph blocks out of ctx+0x20c/0x214, and toggles entry 0x80 visible. When a
 * session exists and is active it shows entry 2 and hides entry 1 (each with the c08/c80 pair).
 * It binds the resolve callbacks func_ov008_0206e818/0206e848 to entries 0x2b/0x2c, and -- only
 * when REG_POWCNT1 bit 15 (display swap) is clear -- pushes their subitem sets. Finally it copies
 * four 8-byte blocks from ctx+0x21c.. into the entries named by the tag list.
 *
 * func_02030670 (session-active) takes func_02030640's result implicitly: the ROM leaves it in r0,
 * so both read as zero-arg calls here. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct W4 { u32 a, b, c, d; } W4;
typedef struct Point { int x, y; } Point;

extern W4 data_ov008_0208f648;
extern W4 data_ov008_0208f658;
extern void func_ov008_0206e818(void);
extern void func_ov008_0206e848(void);

extern int   func_ov008_02050c64(void);
extern int   func_ov008_02050f08(int tag);
extern void *func_ov008_02050f84(int a);
extern void  func_ov008_02054744(int obj, u32 *tmpl);
extern void  func_ov008_0205475c(int obj, void *p);
extern void  func_ov008_02054678(int obj, void *p, int n);
extern int   func_ov008_02054788(int obj, int id);
extern void  func_ov008_02054d90(int obj, int entry, int n);
extern int   func_ov008_0205489c(int obj, int entry);
extern void  func_ov008_020548bc(int obj, int entry, Point *pt);
extern void  func_ov008_02054c08(int obj, int entry);
extern void  func_ov008_02054c80(int obj, int entry, int n);
extern void  func_ov008_02054ba4(int obj, int entry, int n);
extern void  func_ov008_02054b18(int obj, int entry, int n);
extern void  func_ov008_0205476c(int obj, int id, void *fn);
extern int   func_02030640(void);
extern int   func_02030670(void);
extern void  MI_CpuCopy8(void *dst, void *src, int n);

void func_ov008_0206bfac(int ctx)
{
    int    local_28[4];
    u32    block2[4];
    Point  pt;
    int    obj, entry, block, i;

    *(W4 *)local_28 = data_ov008_0208f648;
    *(W4 *)block2 = data_ov008_0208f658;
    obj = func_ov008_02050c64();
    block2[0] = func_ov008_02050f08(0x28);
    func_ov008_02054744(obj, block2);
    func_ov008_0205475c(obj, func_ov008_02050f84(2));
    func_ov008_02054678(obj, (void *)func_ov008_02050f08(0x29), 0x42);
    func_ov008_02054d90(obj, func_ov008_02054788(obj, 0x51), 3);

    entry = func_ov008_02054788(obj, 0x2b);
    block = func_ov008_0205489c(obj, entry);
    pt.x = 0;
    pt.y = 0xf0000 - *(int *)(block + 4);
    func_ov008_020548bc(obj, func_ov008_02054788(obj, 0x2b), &pt);

    entry = func_ov008_02054788(obj, 0x4a);
    func_ov008_02054c08(obj, entry);
    func_ov008_02054c80(obj, entry, 3);

    entry = func_ov008_02054788(obj, 0x29);
    MI_CpuCopy8((void *)func_ov008_0205489c(obj, entry), (void *)(ctx + 0x20c), 8);
    entry = func_ov008_02054788(obj, 0x51);
    MI_CpuCopy8((void *)func_ov008_0205489c(obj, entry), (void *)(ctx + 0x214), 8);

    func_ov008_02054ba4(obj, func_ov008_02054788(obj, 0x80), 1);

    if (func_02030640() != 0 && func_02030670() != 0) {
        func_ov008_02054ba4(obj, func_ov008_02054788(obj, 2), 1);
        func_ov008_02054c08(obj, func_ov008_02054788(obj, 2));
        func_ov008_02054c80(obj, func_ov008_02054788(obj, 2), 0);
        func_ov008_02054ba4(obj, func_ov008_02054788(obj, 1), 0);
        func_ov008_02054c08(obj, func_ov008_02054788(obj, 1));
        func_ov008_02054c80(obj, func_ov008_02054788(obj, 1), 0);
    }

    func_ov008_0205476c(obj, 0x2b, (void *)func_ov008_0206e818);
    func_ov008_0205476c(obj, 0x2c, (void *)func_ov008_0206e848);

    if ((int)(*(u16 *)0x04000304 & 0x8000) >> 0xf == 0) {
        func_ov008_02054b18(obj, func_ov008_02054788(obj, 0x2b), 1);
        func_ov008_02054b18(obj, func_ov008_02054788(obj, 0x2c), 1);
    }

    i = 0;
    do {
        entry = func_ov008_02054788(obj, local_28[i]);
        MI_CpuCopy8((void *)func_ov008_0205489c(obj, entry),
                    (void *)(ctx + 0x21c + i * 8), 8);
        i++;
    } while (i < 4);
}
