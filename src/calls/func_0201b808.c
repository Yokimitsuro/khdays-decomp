typedef struct G {
    char pad[0x84];
    char *slots;
} G;

extern G *data_0204ad4c;

void func_0201b808(unsigned int idx, void *value)
{
    *(void **)(data_0204ad4c->slots + idx * 16 + 0x14) = value;
}
