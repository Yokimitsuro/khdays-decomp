extern void INITi_CpuClear32_0x01ff86fc();
extern int data_ov002_0207fa20;

void func_ov002_0207682c(void) {
    INITi_CpuClear32_0x01ff86fc(0, *(int *)((char *)&data_ov002_0207fa20 + 4) + 0x7c, 0x100);
}
