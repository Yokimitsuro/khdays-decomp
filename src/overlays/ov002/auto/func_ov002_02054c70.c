typedef struct {
    unsigned char pad : 1;
    unsigned char active : 1;
} Ov002Flags;

/* Sets the "active" bit of the object's flag byte from a boolean. */
void func_ov002_02054c70(char *obj, int on) {
    ((Ov002Flags *)(obj + 0x2c))->active = (on != 0);
}
