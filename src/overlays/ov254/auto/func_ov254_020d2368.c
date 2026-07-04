struct s { signed char _pad[0x1c6]; signed char a; signed char b; };
void func_ov254_020d2368(int *p)
{
    struct s *st = (struct s *)*p;
    if (st->a == 1 || st->b == 1)
        st->b = 2;
}
