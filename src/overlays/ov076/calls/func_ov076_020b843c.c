extern void func_ov076_020b9220(int a, int *b);
extern void func_ov076_020b947c(int a, int *b);
extern void func_ov076_020b9234(int a, int *b);
extern void func_ov022_020a384c(int a, int b);
extern int data_ov076_020b9d00;

void func_ov076_020b843c(int self, int req) {
    int *blk = (int *)(*(int *)&data_ov076_020b9d00 + 0x2c + 0x2c00);
    int st = -1;
    int doAnim = 1;
    switch (req) {
    case 0x2e:
        if (*(int *)(self + 0x6bc) != req) {
            func_ov076_020b9220(self, blk);
        }
        break;
    case 0x2f:
        blk[0x45] = 0;
        if (*(int *)(self + 0x6bc) != req) {
            func_ov076_020b947c(self, blk);
        }
        break;
    case 0x30:
        blk[0x45] = 1;
        if (*(int *)(self + 0x6bc) == req) {
            doAnim = 0;
        } else {
            func_ov076_020b9234(self, blk);
            func_ov076_020b947c(self, blk);
        }
        st = 0x30;
        req = 0x2f;
        break;
    }
    if (doAnim != 0) {
        func_ov022_020a384c(self, req);
    }
    if (st >= 0) {
        *(int *)(self + 0x6bc) = st;
    }
}
