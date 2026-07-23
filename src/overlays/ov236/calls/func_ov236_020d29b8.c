/* Publish the pounce landing: send the canned 4-byte block from the config table to the owner's
 * notify hook, play animation 6 and clear the byte at +0x74 before handing off.
 *
 * Matched byte-exact 2026-07-23, closing an old park. The config pair is a STRUCT-TYPED GLOBAL
 * copied with a plain struct assignment, and `node` is loaded BEFORE that copy: the copy is then
 * one unit for the scheduler, so the node load drops into the gap between the two halfword loads
 * and the two halfword stores, which is where the ROM has it.
 *
 * One of two byte-identical siblings. */
struct Pair16 { unsigned short a, b; };

extern int func_ov107_020c9264(int obj, int a, int b);
extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov236_020d2a28(int self);
struct Blk { unsigned short pad[10]; struct Pair16 p; };
extern struct Blk data_ov236_020d63e8;

void func_ov236_020d29b8(int self) {
    struct Pair16 local;
    int *node;
    void (*method)(int, void *, int);
    node = *(int **)(self + 4);
    local = data_ov236_020d63e8.p;
    method = *(void (**)(int, void *, int))(*node + 0x24);
    if (method != 0) {
        method(*node, &local, 4);
    }
    func_ov107_020c9264(*node, 6, 0);
    *(unsigned char *)((char *)node + 0x74) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov236_020d2a28);
}
