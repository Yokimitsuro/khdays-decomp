extern void func_ov027_02083c40(int table, int idx);
/* Fill slot `idx` (stride 0x18) of the table with the six draw parameters (the second is doubled),
 * then commit it. */
void func_ov027_02083c1c(int table, int idx, int a, int b, int c, int d, int e, int f) {
    int slot = table + idx * 0x18;
    *(int *)(slot + 8) = a;
    *(int *)(slot + 0xc) = b << 1;
    *(int *)(slot + 0x10) = c;
    *(int *)(slot + 0x14) = d;
    *(int *)(slot + 0x18) = e;
    *(int *)(slot + 0x1c) = f;
    func_ov027_02083c40(table, idx);
}
