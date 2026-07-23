/* func_ov008_0205714c -- prime the menu sub-scene from the current cursor plus a difficulty.
 * Snapshots the current cursor triple (func_ov008_0204ed20); a negative argument clears the
 * sub-scene, otherwise it selects page `arg`, stamps the difficulty byte into the high half
 * of the triple's second short, and hands the triple over.
 *
 * The snapshot is a STRUCT COPY, not three element assignments: the ROM issues both of the
 * first two halfword loads before either store, which is the shape mwcc gives a 6-byte
 * struct assignment and not the shape it gives element-by-element copies (those pair each
 * load with its own store, in the opposite order). */
extern int   func_02030788(void);
extern unsigned short *func_ov008_0204ed20(void);
extern void  func_ov008_0204ec34(unsigned short *init);
extern void  func_ov008_02050e2c(int page);

typedef struct { unsigned short a, b, c; } Cursor0205714c;

void func_ov008_0205714c(int arg) {
    Cursor0205714c init;
    unsigned short *cur;

    func_02030788();
    cur = func_ov008_0204ed20();
    init = *(Cursor0205714c *)cur;

    if (arg < 0) {
        func_ov008_0204ec34(0);
        return;
    }
    func_ov008_02050e2c(arg);
    *((char *)&init + 3) = (char)arg;
    func_ov008_0204ec34((unsigned short *)&init);
}
