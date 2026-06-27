asm void MTX_Copy44To43_(void *src, void *dst)
{
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    add r0, r0, #4
    stmia r1!, {r2, r3, ip}
    bx lr
}
