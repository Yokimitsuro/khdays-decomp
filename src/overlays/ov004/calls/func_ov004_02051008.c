typedef struct {
    unsigned char opaque0000[0x5550];
    int transitionComplete;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;

void func_ov004_02051008(void)
{
    if (!data_ov004_02051384->transitionComplete)
        data_ov004_02051384->transitionComplete = 1;
}
