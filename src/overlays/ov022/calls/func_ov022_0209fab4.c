/* 0xd90 and 0xda0 are 0x10 apart -- two adjacent sub-objects, so an array of two,
 * not two unrelated fields. */
typedef struct {
    char pad00[0x10];
} Ov022Sub;

typedef struct {
    int flags;        /* +0x00 */
    char pad04[0x30];
    int f34;          /* +0x34 */
    int f38;          /* +0x38 */
} Ov022Inner;

typedef struct {
    char pad000[0x20];
    char *owner;          /* +0x20; the inner block starts at owner+0x24 */
    char padd24[0xd6c];
    Ov022Sub sub[2];      /* +0xd90, +0xda0 */
    char paddb0[0x18bc];
    char pad266c[0];      /* +0x266c is a sub-struct, +0x2684 a heap pointer */
} Ov022Root;

extern void func_0202df30(void *p);
extern void func_02014e2c(Ov022Inner *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_ov022_0209cee8(void *p);
extern void func_ov022_0209c6c4(void *p);
extern void func_ov022_020b18e0(void *p);
extern void func_ov022_020b1c08(void *p);
extern void func_ov022_0209f0b8(void *p);
extern void func_ov022_0209cc68(void *p);
extern void func_ov022_0209d278(void *p);

void func_ov022_0209fab4(char *root) {
    Ov022Inner *in;

    func_0202df30(root + 0x266c);
    func_02014e2c((Ov022Inner *)(*(char **)(root + 0x20) + 0x24));
    in = (Ov022Inner *)(*(char **)(root + 0x20) + 0x24);
    if (in->f38 == 0) {
        in->flags &= ~1;
    }
    in->f34 = 0;
    NNSi_FndFreeFromDefaultHeap(*(void **)(root + 0x2684));
    func_ov022_0209cee8(root);
    func_ov022_0209c6c4(root);
    func_ov022_020b18e0(root + 0xd90);
    func_ov022_020b1c08(root + 0xda0);
    func_ov022_0209f0b8(root);
    func_ov022_0209cc68(root);
    func_ov022_0209d278(root);
}
