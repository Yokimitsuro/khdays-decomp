/* Clears seven counters in the ov057 scene block, registers its five sequence
 * objects from the E0/E1/E2/E4/E5 resource paths, then initializes actor slot 5
 * from the shared five-word slot parameter block. */
extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern int data_ov057_020b74a0;
extern int data_ov057_020b7434;
extern int data_ov057_020b7448;
extern int data_ov057_020b745c;
extern int data_ov057_020b7470;
extern int data_ov057_020b7484;

typedef struct { char *pszResourcePath; int resourceKind; int reserved[3]; } Ov022SlotInitParams;
extern Ov022SlotInitParams data_ov057_020b738c;

void func_ov057_020b6020(int self) {
    Ov022SlotInitParams params;
    char *blk;
    int base = *(int *)&data_ov057_020b74a0;
    blk = (char *)(base + 0x2c + 0x2c00);
    *(int *)(blk + 0x228) = 0;
    *(int *)(blk + 0xc) = 0;
    *(int *)(blk + 0x118) = 0;
    *(int *)(blk + 0x338) = 0;
    *(int *)(blk + 0x444) = 0;
    *(int *)(blk + 8) = 0;
    *(int *)(blk + 0x550) = 0;
    func_0202a634((int)(blk + 0x22c), &data_ov057_020b7434, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x10), &data_ov057_020b7448, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x11c), &data_ov057_020b745c, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x33c), &data_ov057_020b7470, 1,
                  *(unsigned char *)(base + 9) + 7);
    func_0202a634((int)(blk + 0x448), &data_ov057_020b7484, 1,
                  *(unsigned char *)(base + 9) + 7);
    params = data_ov057_020b738c;
    func_ov022_02092384(self + 0x248 + 0x2400, *(unsigned char *)(self + 9), 5, &params);
}
