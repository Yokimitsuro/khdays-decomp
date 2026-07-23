/* func_ov149_020cfad8 -- broadcast this node's position. When the caller's flag word has both
 * bit 0 and bit 4 set, build the 14-byte message from the template at data_ov149_020d077c, pack
 * the node's position vector into bytes 5..13 (three components, each as sign + 23-bit magnitude
 * split high/mid/low), hand it to the object's message hook with length 0xe, clear the pending
 * byte at +0x1c7 and report success. Head of a 5-member family.
 *
 * Two codegen cracks were needed; both are counter-intuitive enough to be worth recording.
 *
 * 1. THE DEAD STRUCT COPY MUST BE COPIED ONE WORD AT A TIME.
 *    The ROM also stores the vector into a stack copy that nothing ever reads. mwcc does NOT
 *    dead-store-eliminate a struct assignment, but it DOES eliminate scalar ones -- so writing
 *    `v.x = w[0]` (or going through a temporary) drops all three stores and the function comes
 *    out 12 bytes short. Writing it as one 3-word struct copy keeps them, but mwcc then emits a
 *    block `ldm`/`stm` and reloads all three components together to pack them, holding them live
 *    at once: eight callee-saved registers and 4 bytes long.
 *    Copying through a ONE-WORD struct (`*(struct w1 *)&v.x = s[0]`) gets both halves: the copy
 *    survives elimination, and it is emitted as a plain `ldr`/`str` that mwcc fuses with the
 *    packing -- one load per component, packed out of that register, then stored to the dead
 *    copy, exactly as the ROM does. Everything stays in scratch.
 *
 * 2. DO NOT CACHE A POINTER TO THE MESSAGE BUFFER.
 *    With `p = (unsigned char *)&m;` mwcc keeps `p` in a register and addresses the bytes as
 *    `[p, #5]`. Indexing `m` directly at every use lets it fold the whole thing into the frame
 *    pointer, `[sp, #0x11]`, which is what the ROM does and what frees the last register.
 */
struct Msg { unsigned short h[7]; };
struct vec { int x, y, z; };
struct w1 { int v; };
extern struct Msg data_ov149_020d077c;

int func_ov149_020cfad8(int self, int a, unsigned int *flags, int d) {
    int *node = *(int **)(self + 0x214);
    struct Msg m;
    struct vec v;
    struct w1 *s;
    void (*cb)(int, struct Msg *, int);

    if (((unsigned short)*flags & 1) != 0 && ((unsigned short)*flags & 0x10) != 0) {
        m = data_ov149_020d077c;
        s = (struct w1 *)node[1];

        *(struct w1 *)&v.x = s[0];
        ((unsigned char *)&m)[5]  = (unsigned char)(((unsigned int)v.x >> 0x10 & 0x7f) | ((unsigned int)v.x >> 0x18 & 0x80));
        ((unsigned char *)&m)[6]  = (unsigned char)((unsigned int)v.x >> 8);
        ((unsigned char *)&m)[7]  = (unsigned char)v.x;

        *(struct w1 *)&v.y = s[1];
        ((unsigned char *)&m)[8]  = (unsigned char)(((unsigned int)v.y >> 0x10 & 0x7f) | ((unsigned int)v.y >> 0x18 & 0x80));
        ((unsigned char *)&m)[9]  = (unsigned char)((unsigned int)v.y >> 8);
        ((unsigned char *)&m)[10] = (unsigned char)v.y;

        *(struct w1 *)&v.z = s[2];
        ((unsigned char *)&m)[11] = (unsigned char)(((unsigned int)v.z >> 0x10 & 0x7f) | ((unsigned int)v.z >> 0x18 & 0x80));
        ((unsigned char *)&m)[12] = (unsigned char)((unsigned int)v.z >> 8);
        ((unsigned char *)&m)[13] = (unsigned char)v.z;

        cb = *(void (**)(int, struct Msg *, int))(*node + 0x24);
        if (cb != 0) {
            cb(*node, &m, 0xe);
        }
        *(signed char *)(*node + 0x1c7) = 0;
        return 1;
    }
    return 0;
}
