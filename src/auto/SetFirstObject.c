struct S {
    void *p0;       /* 0x00 */
    void *p4;       /* 0x04 */
    unsigned short h8;  /* 0x08 */
    unsigned short ha;  /* 0x0a */
};

void SetFirstObject(struct S *r0, char *r1)
{
    unsigned short off = r0->ha;
    *(int *)(r1 + off + 4) = 0;
    *(int *)(r1 + off) = 0;
    r0->p0 = r1;
    r0->p4 = r1;
    r0->h8++;
}
