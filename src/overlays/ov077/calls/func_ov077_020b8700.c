/* Resets the five animation slots of the ov077 scene block and re-arms them
 * from their five descriptors, then hands the shared parameter block to the
 * actor's own slot. Same routine as the matched overlay siblings with five slots
 * rather than three and two extra counters cleared. */
extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov077_020b9b80;
extern int data_ov077_020b9b14;
extern int data_ov077_020b9b28;
extern int data_ov077_020b9b3c;
extern int data_ov077_020b9b50;
extern int data_ov077_020b9b64;

typedef struct { int w[5]; } Params;
extern Params data_ov077_020b9a6c;

void func_ov077_020b8700(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov077_020b9b80;
    blk = (char *)(base + 0x2c + 0x2c00);
    *(int *)(blk + 0x228) = 0;
    *(int *)(blk + 0xc) = 0;
    *(int *)(blk + 0x118) = 0;
    *(int *)(blk + 0x338) = 0;
    *(int *)(blk + 0x444) = 0;
    *(int *)(blk + 8) = 0;
    *(int *)(blk + 0x550) = 0;
    func_0202a634((int)(blk + 0x22c), &data_ov077_020b9b14, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x10), &data_ov077_020b9b28, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x11c), &data_ov077_020b9b3c, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x33c), &data_ov077_020b9b50, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x448), &data_ov077_020b9b64, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov077_020b9a6c;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
}
