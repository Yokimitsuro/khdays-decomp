typedef struct {
    char pad[0xb46fc];
    unsigned char field_b46fc;
} S_020335a4;

extern S_020335a4 *data_0204c234;

int func_020335a4(void) {
    return data_0204c234->field_b46fc == 1;
}
