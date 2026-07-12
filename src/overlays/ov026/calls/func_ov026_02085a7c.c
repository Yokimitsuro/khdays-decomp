/* Clear the +0xc118/+0xc11c words of the ov026 global object. */
extern int data_ov026_02091368;
void func_ov026_02085a7c(void) {
    *(int *)(data_ov026_02091368 + 0xc118) = 0;
    *(int *)(data_ov026_02091368 + 0xc11c) = 0;
}
