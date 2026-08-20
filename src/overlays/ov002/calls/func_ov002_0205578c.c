extern char *data_ov002_0207f614;

extern int func_ov002_02059240(int nSlot);
extern void func_ov002_02057260(int nSlot, int nMode);

/* Tick the four slot timers. When one reaches zero the slot is retired, with
 * the mode chosen by whether it is still occupied. */
void func_ov002_0205578c(void)
{
    char *pBase;
    int nTimer;
    int i;

    pBase = *(char **)&data_ov002_0207f614;

    for (i = 0; i < 4; i++) {
        nTimer = *(unsigned char *)(pBase + i + 0x65);
        if (nTimer != 0) {
            *(unsigned char *)(pBase + i + 0x65) = nTimer - 1;
            if (((nTimer - 1) & 0xff) == 0) {
                func_ov002_02057260(i, func_ov002_02059240(i) == 0 ? 2 : 0);
            }
        }
    }
}
