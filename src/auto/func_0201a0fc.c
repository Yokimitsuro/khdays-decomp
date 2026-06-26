struct S { unsigned char *volatile p; };

void func_0201a0fc(struct S *s, unsigned char v)
{
    if (s->p) {
        s->p[0x41] = v;
    }
}
