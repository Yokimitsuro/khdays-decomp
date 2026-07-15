/* func_ov006_02056154 -- title top-level state (Start dispatch), ov006. Polls the title
 * input (func_ov006_02051f6c), stores it in heap[1], and on Start (1) requests scene 0x13
 * (main menu), on reset (2) requests scene 1 (logo). Returns the spawn sentinel (-2) on a
 * transition, else 0 (stay). */
extern int *data_ov006_02056668;
extern int  func_ov006_02051f6c(void);
extern void func_02020a78(int scene, int arg);
void *func_ov006_02056154(void) {
    int result = 0;
    data_ov006_02056668[1] = func_ov006_02051f6c();
    switch (data_ov006_02056668[1]) {
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
