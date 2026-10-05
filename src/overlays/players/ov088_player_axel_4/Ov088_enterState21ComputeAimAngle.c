/* State 0x21 handler: picks the attack command by variant, faces the locked target (turning the
 * display object once) and returns the fire-attack step. */

extern int Ov022_ValidateTargetRef(int this);
extern int func_ov022_020ad0c0(int this);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern void VEC_Normalize(void *a, void *b);
extern int FX_Atan2Idx(int x, int z);
extern void Ov088_ActorFireAttack(void);

void *Ov088_enterState21ComputeAimAngle(int this, int param_2) {
    void *retval = 0;
    if (param_2 == 0x21) {
        int local[3];
        retval = (void *)Ov088_ActorFireAttack;
        if (*(int *)(this + 0x2c2c) != 0) {
            (*(void (**)(int, int))(this + 0x664))(this, 0x30);
        } else {
            (*(void (**)(int, int))(this + 0x664))(this, 0x2f);
        }
        if (Ov022_ValidateTargetRef(this) != 0) {
            unsigned short angle;
            int *obj;
            VEC_Subtract((void *)func_ov022_020ad0c0(this), (void *)(this + 0x48c), local);
            if (VEC_Mag(local) != 0) {
                VEC_Normalize(local, local);
            }
            angle = (unsigned short)FX_Atan2Idx(-local[0], -local[2]);
            obj = *(int **)(this + 0x20);
            if ((*obj & 0x20) == 0) {
                *(short *)((int)obj + 0x80) = angle + 0x8000;
                *(unsigned short *)((int)obj + 4) |= 0x20;
            }
        }
    }
    return retval;
}
