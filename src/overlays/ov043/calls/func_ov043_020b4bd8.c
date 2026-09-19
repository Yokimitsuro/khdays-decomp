/* Seeds the two request rows of the node (+0x12c, stride 0x240) from the local tables:
 * each row's +0x214 vector, +0x230 (zero), +0x234 speed -- scaled by 1.5 on difficulty 1 --
 * and +0x220 value come from data_ov043_020b57a4 / 576c / 577c by row index, and the +0x23c
 * counter is cleared. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 v[4]; } VecTable4;
typedef struct { int n[4]; } IntTable4;

extern int func_02023c40(void);
extern const VecTable4 data_ov043_020b57a4;
extern const IntTable4 data_ov043_020b576c;
extern const IntTable4 data_ov043_020b577c;

void func_ov043_020b4bd8(char *node)
{
    VecTable4 tblVec;
    IntTable4 tblZero = {0};
    IntTable4 tblA;
    IntTable4 tblB;
    int i;
    char *pRow;

    tblVec = data_ov043_020b57a4;
    tblA = data_ov043_020b576c;
    tblB = data_ov043_020b577c;
    pRow = node + 0x12c;
    for (i = 0; i < 2; i++) {
        *(Vec3 *)(pRow + 0x214) = tblVec.v[i];
        *(int *)(pRow + 0x230) = tblZero.n[i];
        *(int *)(pRow + 0x234) = tblA.n[i];
        *(int *)(pRow + 0x220) = tblB.n[i];
        if (func_02023c40() == 1) {
            *(int *)(pRow + 0x234) = (int)(((long long)*(int *)(pRow + 0x234) * 0x1800 + 0x800) >> 12);
        }
        *(int *)(pRow + 0x23c) = 0;
        pRow += 0x240;
    }
}
