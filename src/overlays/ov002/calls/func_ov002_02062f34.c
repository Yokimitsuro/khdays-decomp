/*
 * Return 1 only when the mode word at (*(&data+4))+0xc is 0; a value of 2 (or any
 * nonzero) returns 0.
 */
extern int data_ov002_0207f62c;

int func_ov002_02062f34(void) {
    int v = *(int *)(*(int *)((char *)&data_ov002_0207f62c + 4) + 0xc);

    if (v != 2 && v == 0) {
        return 1;
    }
    return 0;
}
