/* Per-frame update over entity[index]'s three intrusive lists (head slots at
 * data_0204c208+index*4+{0x64,0x84,0xa4}): run func_0202aa9c on active nodes,
 * snapshot each active node's +0xb4 vec into +0x168 and run func_0202df34, then
 * a second func_0202aa9c pass, and finally func_020287e8 over the +0xa4 list. */
extern int data_0204c208;
extern void func_0202aa9c(void *);
extern void func_0202df34(void *);
extern void func_02028768(void);
extern void func_020287e8(void *);

struct V3 { int a, b, c; };

void func_0202bc90(int index) {
    int *p;
    for (p = *(int **)(data_0204c208 + index * 4 + 0x64); p != 0; p = *(int **)p) {
        if ((*(unsigned char *)(p + 2) & 8) && (p[3] & 0x20) == 0) {
            func_0202aa9c(p + 4);
        }
    }
    for (p = *(int **)(data_0204c208 + index * 4 + 0x84); p != 0; p = *(int **)p) {
        if ((*(unsigned char *)(p + 2) & 0x18) == 0x18) {
            *(struct V3 *)((char *)p + 0x168) = *(struct V3 *)((char *)p + 0xb4);
            func_0202df34((char *)p + 0x168);
        }
    }
    for (p = *(int **)(data_0204c208 + index * 4 + 0x84); p != 0; p = *(int **)p) {
        if ((*(unsigned char *)(p + 2) & 8) && (p[3] & 0x20) == 0) {
            func_0202aa9c(p + 4);
        }
    }
    p = *(int **)(data_0204c208 + index * 4 + 0xa4);
    if (p != 0) {
        func_02028768();
        do {
            func_020287e8(p + 3);
            p = *(int **)p;
        } while (p != 0);
    }
}
