/* Bind channels 0, 2, 4 and 1 of both +0x384 rider rigs to (mode, flag) and re-init them. */
struct Riders { char pad[0x384]; int rider[2]; };

extern void func_0203b9fc(int item, int channel, short a, int b);
extern void func_0203c7ac(int item, int a);

void func_ov254_020d54a4(char *self, int mode, int flag)
{
    int i;

    for (i = 0; i < 2; i++) {
        func_0203b9fc(((struct Riders *)self)->rider[i], 0, mode, flag);
        func_0203b9fc(((struct Riders *)self)->rider[i], 2, mode, flag);
        func_0203b9fc(((struct Riders *)self)->rider[i], 4, mode, flag);
        func_0203b9fc(((struct Riders *)self)->rider[i], 1, mode, flag);
        func_0203c7ac(((struct Riders *)self)->rider[i], 0);
    }
}
