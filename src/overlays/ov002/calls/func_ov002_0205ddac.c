extern void func_ov002_0205b5e4(void);
extern void func_ov002_0205d214(unsigned int kind, int arg);
extern char *data_ov002_0207f620;
/* If the HUD context is live, rebuild its tile row and refresh the local player's sub-updater. */
void func_ov002_0205ddac(void) {
    int ctx = (int)data_ov002_0207f620;
    if (ctx != 0) {
        func_ov002_0205b5e4();
        func_ov002_0205d214(*(unsigned char *)(ctx + 1), -1);
    }
}
