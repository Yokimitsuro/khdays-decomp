extern int OS_SPrintf();
extern int data_ov002_0207f0d4;
extern int data_ov002_0207f100;

void func_ov002_02072820(int arg0, int arg1) {
    OS_SPrintf(arg1, &data_ov002_0207f0d4, &data_ov002_0207f100, *(signed char *)(arg0 + 1));
}
