extern void func_02027ac8(void);
extern void func_02027af0(void);
extern void func_01ffba90(void);
extern void func_01ffbbac(void);
extern void func_01ffbbf0(void);
extern void func_01ffc0d0(void);
extern void func_01ffc164(void);
extern void func_02027b18(void);
extern void func_02027d7c(void);
extern void func_01ffc450(void);
extern void func_0202803c(void);
extern void func_01ffcbac(void);
extern void func_020280a4(void);
extern void func_02028314(void);
extern void srand_0x02016284(unsigned seed);
extern void *data_027e0660[];

/* Publishes the archive backend's 14-entry vtable and seeds the RNG. */
void func_020285f0(void) {
    data_027e0660[0] = (void *)&func_02027ac8;
    data_027e0660[1] = (void *)&func_02027af0;
    data_027e0660[2] = (void *)&func_01ffba90;
    data_027e0660[3] = (void *)&func_01ffbbac;
    data_027e0660[4] = (void *)&func_01ffbbf0;
    data_027e0660[5] = (void *)&func_01ffc0d0;
    data_027e0660[6] = (void *)&func_01ffc164;
    data_027e0660[7] = (void *)&func_02027b18;
    data_027e0660[8] = (void *)&func_02027d7c;
    data_027e0660[9] = (void *)&func_01ffc450;
    data_027e0660[10] = (void *)&func_0202803c;
    data_027e0660[11] = (void *)&func_01ffcbac;
    data_027e0660[12] = (void *)&func_020280a4;
    data_027e0660[13] = (void *)&func_02028314;
    srand_0x02016284(1);
}
