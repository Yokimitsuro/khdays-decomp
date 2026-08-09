typedef unsigned int u32;
typedef volatile u32 vu32;

void func_01ff8664(u32 channel, u32 source, u32 destination, u32 control)
{
    vu32 *registers = (vu32 *)(0x040000b0 + channel * 12);

    registers[0] = source;
    registers[1] = destination;
    registers[2] = control;

    (void)*(vu32 *)0x040000b0;
    (void)*(vu32 *)0x040000b0;

    if (channel == 0) {
        registers[0] = 0;
        registers[1] = 0;
        registers[2] = 0x81400001;
    }

    (void)*(vu32 *)0x040000b0;
    (void)*(vu32 *)0x040000b0;
}
