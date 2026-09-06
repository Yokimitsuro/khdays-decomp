/* Resets the five animation slots of the ov038 scene block and re-arms them
 * from their five descriptors, then hands the shared parameter block to the
 * actor's own slot. Same routine as the matched ov048 sibling with five slots
 * rather than three and two extra counters cleared. */
extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov094_020bc240;
extern int data_ov094_020bc1d4;
extern int data_ov094_020bc1e8;
extern int data_ov094_020bc1fc;
extern int data_ov094_020bc210;
extern int data_ov094_020bc224;

typedef struct { int w[5]; } Params;
extern Params data_ov094_020bc12c;

void func_ov094_020badc0(int self) {
    Params p;
    char *blk;
    int base = *(int *)&data_ov094_020bc240;
    blk = (char *)(base + 0x2c + 0x2c00);
    *(int *)(blk + 0x228) = 0;
    *(int *)(blk + 0xc) = 0;
    *(int *)(blk + 0x118) = 0;
    *(int *)(blk + 0x338) = 0;
    *(int *)(blk + 0x444) = 0;
    *(int *)(blk + 8) = 0;
    *(int *)(blk + 0x550) = 0;
    func_0202a634((int)(blk + 0x22c), &data_ov094_020bc1d4, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x10), &data_ov094_020bc1e8, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x11c), &data_ov094_020bc1fc, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x33c), &data_ov094_020bc210, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x448), &data_ov094_020bc224, 1,
                  *(unsigned char *)(base + 9) + 7);
    p = data_ov094_020bc12c;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &p);
}
