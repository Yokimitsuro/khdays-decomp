typedef struct {
    char pad[0x64];
    unsigned int b64_0 : 2;
    unsigned int b64_2 : 1;
    unsigned int b64_rest : 29;
    char pad2[0x80 - 0x68];
    unsigned int b80_0 : 2;
    unsigned int b80_2 : 1;
    unsigned int b80_rest : 29;
} Obj;

int func_ov026_020842cc(Obj *o) {
    if (o->b64_2) {
        if (o->b80_2) {
            return 1;
        }
    }
    return 0;
}
