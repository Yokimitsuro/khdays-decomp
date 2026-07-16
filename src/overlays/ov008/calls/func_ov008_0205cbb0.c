/* func_ov008_0205cbb0 -- push the tag-3 row's position: x = 0x78000 (Q12), y = the entry's own
 * y (func_ov008_02054820(list, param_1) +4) biased by 0x8000. */
extern int  func_ov008_02050c54(void);
extern int  func_ov008_02054820(int list, int key);
extern int  func_ov008_02054788(int list, int tag);
extern void func_ov008_02054858(int list, int row, int *pos);

void func_ov008_0205cbb0(int param_1) {
    int pos[2];
    int list = func_ov008_02050c54();
    int entry = func_ov008_02054820(list, param_1);
    pos[0] = 0x78000;
    pos[1] = *(int *)(entry + 4) + 0x8000;
    {
        int row = func_ov008_02054788(list, 3);
        func_ov008_02054858(list, row, pos);
    }
}
