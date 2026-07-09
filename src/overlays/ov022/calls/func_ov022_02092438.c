extern void func_ov022_02089584(int arg0, int arg1);
void func_ov022_02092438(int arg0, int arg1) {
    int i = 0;
    do {
        int e = ((int *)arg0)[i];
        if (e != 0) func_ov022_02089584(e, arg1);
        i++;
    } while (i < 6);
}
