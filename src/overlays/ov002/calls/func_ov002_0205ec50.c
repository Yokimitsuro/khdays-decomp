/* Arm or disarm the tracker node for tag 0xc.
 *
 * The node is looked up by tag, given the word the context keeps at 0x69c, and then armed or
 * disarmed with the caller's flag. Arming also runs an extra setup step with 0xf and 0x16.
 *
 * The context pointer is bound before the lookup even though its field is not read until after:
 * the original dereferences the global into the same register that later holds the node, so the
 * two lifetimes never overlap. */

typedef unsigned int u32;

extern char *data_ov002_0207f624;
extern void *func_ov002_020536bc(int tag);
extern void func_ov002_0205376c(void *node, u32 value);
extern void func_ov002_02053720(void *node, int a, int b);
extern void func_ov002_020536dc(void *node, int armed);

void func_ov002_0205ec50(int armed) {
    char *ctx = data_ov002_0207f624;
    void *node = func_ov002_020536bc(0xc);

    func_ov002_0205376c(node, *(u32 *)(ctx + 0x69c));
    if (armed != 0) {
        func_ov002_02053720(node, 0xf, 0x16);
    }
    func_ov002_020536dc(node, armed);
}
