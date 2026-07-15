/* func_ov008_02081ec4 -- title top-level state (Start dispatch), ov006. Polls the title
 * input (func_ov008_0207dcc0), stores it in heap[1], and on Start (1) requests scene 0x13
 * (main menu), on reset (2) requests scene 1 (logo). Returns the spawn sentinel (-2) on a
 * transition, else 0 (stay). */
extern int *data_ov008_02090fa8;
extern int  func_ov008_0207dcc0(void);
extern void func_02020a78(int scene, int arg);
void *func_ov008_02081ec4(void) {
    int result = 0;
    data_ov008_02090fa8[1] = func_ov008_0207dcc0();
    switch (data_ov008_02090fa8[1]) {
    case 0:
        break;
    case 1:
        func_02020a78(0x13, 0);
        result = -2;
        break;
    case 2:
        func_02020a78(1, 0);
        result = -2;
        break;
    }
    return (void *)result;
}
