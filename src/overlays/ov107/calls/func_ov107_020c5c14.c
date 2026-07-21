/* Stores a status byte at +0x179, and while the node is active (state 1) emits a 4-byte packet
 * {node.id (u16 at +2), 10, status} through func_02031384. */

extern void func_02031384(int id, unsigned short *buf, int count);

void func_ov107_020c5c14(int node, unsigned char status) {
    unsigned char buf[4];

    *(unsigned char *)(node + 0x179) = status;
    if (*(int *)(node + 0x50) != 1) {
        return;
    }
    {
        unsigned short id = *(unsigned short *)(node + 2);
        buf[2] = 10;
        *(unsigned short *)buf = id;
        buf[3] = ((unsigned char *)node)[0x179];
    }
    func_02031384(4, (unsigned short *)buf, 4);
}
