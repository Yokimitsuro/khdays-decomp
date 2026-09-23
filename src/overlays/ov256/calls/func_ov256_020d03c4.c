/* Constructor tail of an ov256 shard: installs its handlers (+8 020d04f4, +0xc 020d0510, +0x30
 * 020d0560, +0x1d0 hit reaction 020d05bc), sets bits 1-2 and 6 of the +0x60 high byte and bit 2 of
 * +0x1ae, +0x70 = 0xa00, +0x54 / +0x58 clear; its model (+0x384) loads from the +0x398 owner's kit
 * entry 0x53, registers with the +0x9c scene and plays tracks 0-2 looped, the +0xa0 pose scales 2.0 and
 * a placement goes into a +0x22c pool slot at +0x388 (bit 1 set). */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern int func_ov107_020c9440(char *self, int kind);
extern int func_0203b898(int item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int model, int track, int pose, int flag);
extern void func_0203ca9c(void *srt, int scale);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *placement);
extern void func_ov256_020d04f4(void);
extern void func_ov256_020d0510(void);
extern void func_ov256_020d0560(void);
extern void func_ov256_020d05bc(void);

void func_ov256_020d03c4(char *self)
{
    char *owner = *(char **)(self + 0x398);

    *(void **)(self + 8) = func_ov256_020d04f4;
    *(void **)(self + 0xc) = func_ov256_020d0510;
    *(void **)(self + 0x30) = func_ov256_020d0560;
    *(void **)(self + 0x1d0) = func_ov256_020d05bc;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x46) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = 0xa00;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x53));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203ca9c(self + 0xa0, 0x2000);
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((B8 *)(*(char **)(self + 0x388) + 8))->f |= 2;
}
