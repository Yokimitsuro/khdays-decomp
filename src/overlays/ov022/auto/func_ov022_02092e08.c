struct s { unsigned char _pad[0x135]; unsigned char flag; };
void func_ov022_02092e08(int p)
{
    struct s *st = (struct s *)p;
    if (st->flag == 0)
        return;
    st->flag = 0;
    *(int *)(p + 0x168) = 0;
    *(int *)(p + 0x174) = 0x3000;
}
