extern void func_ov027_02082960(void);
extern void func_ov027_02082ac0(void);
extern void func_ov027_02082ad8(void);
extern void func_ov027_02082b08(void);
extern void func_ov027_02082b24(void);
extern void func_ov027_02082b38(void);
extern void func_ov027_02082af0(void);
extern void func_ov027_02082b48(void);

/* Fills in the scene's vtable. */
void func_ov027_02083dbc(void **vt) {
    vt[0] = (void *)&func_ov027_02082960;
    vt[1] = (void *)&func_ov027_02082ac0;
    vt[2] = (void *)&func_ov027_02082ad8;
    vt[3] = (void *)&func_ov027_02082b08;
    vt[4] = (void *)&func_ov027_02082b24;
    vt[5] = (void *)&func_ov027_02082b38;
    vt[6] = (void *)&func_ov027_02082af0;
    vt[7] = 0;
    vt[9] = (void *)&func_ov027_02082b48;
    vt[10] = 0;
}
