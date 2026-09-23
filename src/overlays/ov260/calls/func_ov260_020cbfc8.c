/* Node callback of the ov260 model: when the node's key (its +0xae byte when flag bit 4 is set,
 * else -1) matches the actor's +0x414 slot, the +0x3e4 transform is rebuilt from the actor's +0xa0
 * rotation at the current matrix's translation; a match on the +0x410 slot does the same for the
 * +0x3b8 transform. */
typedef unsigned char u8;
typedef unsigned int u32;
struct Vecx32 { int x, y, z; };
struct MtxFx43 { int m[9]; struct Vecx32 t; };

extern void func_02016294(struct MtxFx43 *dst, void *src);
extern void func_0203c960(void *transform);
extern void func_0203c9d0(void *transform, void *quat);
extern void func_0203ca30(void *transform, struct Vecx32 *pos);

void func_ov260_020cbfc8(char *node)
{
    char *actor = *(char **)(*(int *)(node + 4) + 0x2c);
    struct MtxFx43 mtx;

    if (*(u32 *)(actor + 0x414) == ((*(u32 *)(node + 8) & 0x10) ? *(u8 *)(node + 0xae) : 0xffffffff)) {
        func_02016294(&mtx, 0);
        func_0203c960(actor + 0x3e4);
        func_0203c9d0(actor + 0x3e4, actor + 0xa0);
        func_0203ca30(actor + 0x3e4, &mtx.t);
        return;
    }
    if (*(u32 *)(actor + 0x410) != ((*(u32 *)(node + 8) & 0x10) ? *(u8 *)(node + 0xae) : 0xffffffff)) {
        return;
    }
    func_02016294(&mtx, 0);
    func_0203c960(actor + 0x3b8);
    func_0203c9d0(actor + 0x3b8, actor + 0xa0);
    func_0203ca30(actor + 0x3b8, &mtx.t);
}
