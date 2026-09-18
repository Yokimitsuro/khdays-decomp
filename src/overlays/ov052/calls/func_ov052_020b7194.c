/* Mission start of the ov032 script (and its byte-identical twins): clears the +0x2e78 block
 * of the mission root (its +0x114 byte and first two words), binds its +0xc entry to the
 * overlay's descriptor with the root's +9 slot plus 7, registers the actor's +0x2648 item
 * (kind 5) with the overlay's parameter set and runs the first stage (4da4). */
extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov052_020b75a4(int a);
extern int data_ov052_020b80c0;
extern int data_ov052_020b807c;

typedef struct { int w[5]; } Params;
extern Params data_ov052_020b7f24;

void func_ov052_020b7194(int self)
{
    int base = *(int *)&data_ov052_020b80c0;
    Params p;
    char *blk;

    blk = (char *)(base + 0x2e78);
    *(signed char *)(blk + 0x114) = 0;
    *(int *)blk = 0;
    *(int *)(blk + 4) = 0;
    func_0202a634((int)(blk + 0xc), &data_ov052_020b807c, 1, *(unsigned char *)(base + 9) + 7);
    p = data_ov052_020b7f24;
    func_ov022_02092384(self + 0x2648, *(unsigned char *)(self + 9), 5, &p);
    func_ov052_020b75a4(base);
}
