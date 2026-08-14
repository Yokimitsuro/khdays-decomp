
/mnt/data/func_ov264_020cc1fc_BYTE_EXACT_MATCH/matched.o:	file format elf32-littlearm

Disassembly of section .text:

00000000 <func_ov264_020cc1fc>:
       0: e92d41f8     	push	{r3, r4, r5, r6, r7, r8, lr}
       4: e24dd04c     	sub	sp, sp, #76
       8: e59f5364     	ldr	r5, [pc, #0x364]        @ 0x374 <func_ov264_020cc1fc+0x374>
       c: e1a04000     	mov	r4, r0
      10: e8b5000f     	ldm	r5!, {r0, r1, r2, r3}
      14: e28d6038     	add	r6, sp, #56
      18: e8a6000f     	stm	r6!, {r0, r1, r2, r3}
      1c: e5955000     	ldr	r5, [r5]
      20: e59f8350     	ldr	r8, [pc, #0x350]        @ 0x378 <func_ov264_020cc1fc+0x378>
      24: e5865000     	str	r5, [r6]
      28: e59f334c     	ldr	r3, [pc, #0x34c]        @ 0x37c <func_ov264_020cc1fc+0x37c>
      2c: e59f134c     	ldr	r1, [pc, #0x34c]        @ 0x380 <func_ov264_020cc1fc+0x380>
      30: e59f034c     	ldr	r0, [pc, #0x34c]        @ 0x384 <func_ov264_020cc1fc+0x384>
      34: e5841008     	str	r1, [r4, #0x8]
      38: e584000c     	str	r0, [r4, #0xc]
      3c: e3e0c005     	mvn	r12, #5
      40: e59f7340     	ldr	r7, [pc, #0x340]        @ 0x388 <func_ov264_020cc1fc+0x388>
      44: e2880017     	add	r0, r8, #23
      48: e2802c32     	add	r2, r0, #12800
      4c: e2835097     	add	r5, r3, #151
      50: e2850c25     	add	r0, r5, #9472
      54: e584701c     	str	r7, [r4, #0x1c]
      58: e59f632c     	ldr	r6, [pc, #0x32c]        @ 0x38c <func_ov264_020cc1fc+0x38c>
      5c: e28c10c3     	add	r1, r12, #195
      60: e5846030     	str	r6, [r4, #0x30]
      64: e59f5324     	ldr	r5, [pc, #0x324]        @ 0x390 <func_ov264_020cc1fc+0x390>
      68: e2811b0b     	add	r1, r1, #11264
      6c: e5845034     	str	r5, [r4, #0x34]
      70: e59f631c     	ldr	r6, [pc, #0x31c]        @ 0x394 <func_ov264_020cc1fc+0x394>
      74: e59f531c     	ldr	r5, [pc, #0x31c]        @ 0x398 <func_ov264_020cc1fc+0x398>
      78: e58461d0     	str	r6, [r4, #0x1d0]
      7c: e58451dc     	str	r5, [r4, #0x1dc]
      80: e59f6314     	ldr	r6, [pc, #0x314]        @ 0x39c <func_ov264_020cc1fc+0x39c>
      84: e59f5314     	ldr	r5, [pc, #0x314]        @ 0x3a0 <func_ov264_020cc1fc+0x3a0>
      88: e58461e0     	str	r6, [r4, #0x1e0]
      8c: e58451e4     	str	r5, [r4, #0x1e4]
      90: e3a06b05     	mov	r6, #5120
      94: e5846070     	str	r6, [r4, #0x70]
      98: e3a05000     	mov	r5, #0
      9c: e5845064     	str	r5, [r4, #0x64]
      a0: e5846068     	str	r6, [r4, #0x68]
      a4: e58d8020     	str	r8, [sp, #0x20]
      a8: e28d7020     	add	r7, sp, #32
      ac: e58dc024     	str	r12, [sp, #0x24]
      b0: e584506c     	str	r5, [r4, #0x6c]
      b4: e2846f7f     	add	r6, r4, #508
      b8: e58d3028     	str	r3, [sp, #0x28]
      bc: e58d202c     	str	r2, [sp, #0x2c]
      c0: e58d1030     	str	r1, [sp, #0x30]
      c4: e58d0034     	str	r0, [sp, #0x34]
      c8: e8b7000f     	ldm	r7!, {r0, r1, r2, r3}
      cc: e8a6000f     	stm	r6!, {r0, r1, r2, r3}
      d0: e8970003     	ldm	r7, {r0, r1}
      d4: e8860003     	stm	r6, {r0, r1}
      d8: e3a00001     	mov	r0, #1
      dc: e5c401c9     	strb	r0, [r4, #0x1c9]
      e0: e1d436b0     	ldrh	r3, [r4, #96]
      e4: e1a01005     	mov	r1, r5
      e8: e2842c01     	add	r2, r4, #256
      ec: e3c35cff     	bic	r5, r3, #65280
      f0: e1a03803     	lsl	r3, r3, #16
      f4: e1a03c23     	lsr	r3, r3, #24
      f8: e3833020     	orr	r3, r3, #32
      fc: e1a03c03     	lsl	r3, r3, #24
     100: e1853823     	orr	r3, r5, r3, lsr #16
     104: e1c436b0     	strh	r3, [r4, #96]
     108: e1d23abe     	ldrh	r3, [r2, #174]
     10c: e1a00004     	mov	r0, r4
     110: e3833008     	orr	r3, r3, #8
     114: e1c23abe     	strh	r3, [r2, #174]
     118: eb000000     	bl	0x120 <func_ov264_020cc1fc+0x120> @ imm = #0x0
			00000118:  R_ARM_PC24	func_ov107_020c9440-0x8
     11c: eb000000     	bl	0x124 <func_ov264_020cc1fc+0x124> @ imm = #0x0
			0000011c:  R_ARM_PC24	func_0203b898-0x8
     120: e59f127c     	ldr	r1, [pc, #0x27c]        @ 0x3a4 <func_ov264_020cc1fc+0x3a4>
     124: e5840384     	str	r0, [r4, #0x384]
     128: e5801074     	str	r1, [r0, #0x74]
     12c: e5940384     	ldr	r0, [r4, #0x384]
     130: e5804084     	str	r4, [r0, #0x84]
     134: e594009c     	ldr	r0, [r4, #0x9c]
     138: e5941384     	ldr	r1, [r4, #0x384]
     13c: eb000000     	bl	0x144 <func_ov264_020cc1fc+0x144> @ imm = #0x0
			0000013c:  R_ARM_PC24	func_0203bfb4-0x8
     140: e1a00004     	mov	r0, r4
     144: e3a01001     	mov	r1, #1
     148: eb000000     	bl	0x150 <func_ov264_020cc1fc+0x150> @ imm = #0x0
			00000148:  R_ARM_PC24	func_ov107_020c9440-0x8
     14c: e5941384     	ldr	r1, [r4, #0x384]
     150: e1a02000     	mov	r2, r0
     154: e5911088     	ldr	r1, [r1, #0x88]
     158: e2840fe2     	add	r0, r4, #904
     15c: e3a0300c     	mov	r3, #12
     160: eb000000     	bl	0x168 <func_ov264_020cc1fc+0x168> @ imm = #0x0
			00000160:  R_ARM_PC24	func_0202a388-0x8
     164: e5940384     	ldr	r0, [r4, #0x384]
     168: e2841fe2     	add	r1, r4, #904
     16c: eb000000     	bl	0x174 <func_ov264_020cc1fc+0x174> @ imm = #0x0
			0000016c:  R_ARM_PC24	func_0203b9ac-0x8
     170: e5940384     	ldr	r0, [r4, #0x384]
     174: e59f122c     	ldr	r1, [pc, #0x22c]        @ 0x3a8 <func_ov264_020cc1fc+0x3a8>
     178: eb000000     	bl	0x180 <func_ov264_020cc1fc+0x180> @ imm = #0x0
			00000178:  R_ARM_PC24	func_0203bdfc-0x8
     17c: e5840438     	str	r0, [r4, #0x438]
     180: e1a00004     	mov	r0, r4
     184: e3a0100a     	mov	r1, #10
     188: eb000000     	bl	0x190 <func_ov264_020cc1fc+0x190> @ imm = #0x0
			00000188:  R_ARM_PC24	func_ov107_020c9440-0x8
     18c: eb000000     	bl	0x194 <func_ov264_020cc1fc+0x194> @ imm = #0x0
			0000018c:  R_ARM_PC24	func_0203b898-0x8
     190: e59f1214     	ldr	r1, [pc, #0x214]        @ 0x3ac <func_ov264_020cc1fc+0x3ac>
     194: e5840420     	str	r0, [r4, #0x420]
     198: e580106c     	str	r1, [r0, #0x6c]
     19c: e5940420     	ldr	r0, [r4, #0x420]
     1a0: e3a01000     	mov	r1, #0
     1a4: e5804084     	str	r4, [r0, #0x84]
     1a8: e5940420     	ldr	r0, [r4, #0x420]
     1ac: eb000000     	bl	0x1b4 <func_ov264_020cc1fc+0x1b4> @ imm = #0x0
			000001ac:  R_ARM_PC24	func_0203c7ac-0x8
     1b0: e5940420     	ldr	r0, [r4, #0x420]
     1b4: e59f11f4     	ldr	r1, [pc, #0x1f4]        @ 0x3b0 <func_ov264_020cc1fc+0x3b0>
     1b8: eb000000     	bl	0x1c0 <func_ov264_020cc1fc+0x1c0> @ imm = #0x0
			000001b8:  R_ARM_PC24	func_0203bdfc-0x8
     1bc: e5840434     	str	r0, [r4, #0x434]
     1c0: e3a01000     	mov	r1, #0
     1c4: e3a00b05     	mov	r0, #5120
     1c8: e58d0008     	str	r0, [sp, #0x8]
     1cc: e58d1004     	str	r1, [sp, #0x4]
     1d0: e58d100c     	str	r1, [sp, #0xc]
     1d4: e3a00b03     	mov	r0, #3072
     1d8: e58d0000     	str	r0, [sp]
     1dc: e1a00004     	mov	r0, r4
     1e0: e3a02002     	mov	r2, #2
     1e4: e28d3004     	add	r3, sp, #4
     1e8: eb000000     	bl	0x1f0 <func_ov264_020cc1fc+0x1f0> @ imm = #0x0
			000001e8:  R_ARM_PC24	func_ov107_020c92b0-0x8
     1ec: e3a00000     	mov	r0, #0
     1f0: e58d0004     	str	r0, [sp, #0x4]
     1f4: e58d000c     	str	r0, [sp, #0xc]
     1f8: e2400b05     	sub	r0, r0, #5120
     1fc: e58d0008     	str	r0, [sp, #0x8]
     200: e59f11ac     	ldr	r1, [pc, #0x1ac]        @ 0x3b4 <func_ov264_020cc1fc+0x3b4>
     204: e1a00004     	mov	r0, r4
     208: e58d1000     	str	r1, [sp]
     20c: e3a01002     	mov	r1, #2
     210: e3a02003     	mov	r2, #3
     214: e28d3004     	add	r3, sp, #4
     218: eb000000     	bl	0x220 <func_ov264_020cc1fc+0x220> @ imm = #0x0
			00000218:  R_ARM_PC24	func_ov107_020c92b0-0x8
     21c: e59f1194     	ldr	r1, [pc, #0x194]        @ 0x3b8 <func_ov264_020cc1fc+0x3b8>
     220: e1a00004     	mov	r0, r4
     224: e58d1000     	str	r1, [sp]
     228: e3a01001     	mov	r1, #1
     22c: e3a02002     	mov	r2, #2
     230: e3a03000     	mov	r3, #0
     234: eb000000     	bl	0x23c <func_ov264_020cc1fc+0x23c> @ imm = #0x0
			00000234:  R_ARM_PC24	func_ov107_020c92b0-0x8
     238: e1a07ba8     	lsr	r7, r8, #23
     23c: e59f8178     	ldr	r8, [pc, #0x178]        @ 0x3bc <func_ov264_020cc1fc+0x3bc>
     240: e3a06000     	mov	r6, #0
     244: e28d5038     	add	r5, sp, #56
     248: e3560000     	cmp	r6, #0
     24c: ca00000a     	bgt	0x27c <func_ov264_020cc1fc+0x27c> @ imm = #0x28
     250: eb000000     	bl	0x258 <func_ov264_020cc1fc+0x258> @ imm = #0x0
			00000250:  R_ARM_PC24	OS_IsThreadAvailable_0x020c9848-0x8
     254: e5900088     	ldr	r0, [r0, #0x88]
     258: e7951106     	ldr	r1, [r5, r6, lsl #2]
     25c: e2800902     	add	r0, r0, #32768
     260: e0000008     	and	r0, r0, r8
     264: e1a00380     	lsl	r0, r0, #7
     268: e0011007     	and	r1, r1, r7
     26c: e3800102     	orr	r0, r0, #-2147483648
     270: e1810000     	orr	r0, r1, r0
     274: eb000000     	bl	0x27c <func_ov264_020cc1fc+0x27c> @ imm = #0x0
			00000274:  R_ARM_PC24	func_0203b898-0x8
     278: ea000003     	b	0x28c <func_ov264_020cc1fc+0x28c> @ imm = #0xc
     27c: e7951106     	ldr	r1, [r5, r6, lsl #2]
     280: e1a00004     	mov	r0, r4
     284: eb000000     	bl	0x28c <func_ov264_020cc1fc+0x28c> @ imm = #0x0
			00000284:  R_ARM_PC24	func_ov107_020c9440-0x8
     288: eb000000     	bl	0x290 <func_ov264_020cc1fc+0x290> @ imm = #0x0
			00000288:  R_ARM_PC24	func_0203b898-0x8
     28c: e0841186     	add	r1, r4, r6, lsl #3
     290: e5810440     	str	r0, [r1, #0x440]
     294: e1a01000     	mov	r1, r0
     298: e1a00004     	mov	r0, r4
     29c: eb000000     	bl	0x2a4 <func_ov264_020cc1fc+0x2a4> @ imm = #0x0
			0000029c:  R_ARM_PC24	func_ov107_020c9074-0x8
     2a0: e0840186     	add	r0, r4, r6, lsl #3
     2a4: e5901440     	ldr	r1, [r0, #0x440]
     2a8: e2866001     	add	r6, r6, #1
     2ac: e591005c     	ldr	r0, [r1, #0x5c]
     2b0: e3560005     	cmp	r6, #5
     2b4: e3800002     	orr	r0, r0, #2
     2b8: e581005c     	str	r0, [r1, #0x5c]
     2bc: baffffe1     	blt	0x248 <func_ov264_020cc1fc+0x248> @ imm = #-0x7c
     2c0: e1a00004     	mov	r0, r4
     2c4: e3a0100e     	mov	r1, #14
     2c8: eb000000     	bl	0x2d0 <func_ov264_020cc1fc+0x2d0> @ imm = #0x0
			000002c8:  R_ARM_PC24	func_ov107_020c9440-0x8
     2cc: e3a01022     	mov	r1, #34
     2d0: eb000000     	bl	0x2d8 <func_ov264_020cc1fc+0x2d8> @ imm = #0x0
			000002d0:  R_ARM_PC24	func_0203c1b0-0x8
     2d4: e58403c4     	str	r0, [r4, #0x3c4]
     2d8: e1a01000     	mov	r1, r0
     2dc: e1a00004     	mov	r0, r4
     2e0: eb000000     	bl	0x2e8 <func_ov264_020cc1fc+0x2e8> @ imm = #0x0
			000002e0:  R_ARM_PC24	func_ov107_020c9074-0x8
     2e4: e59423c4     	ldr	r2, [r4, #0x3c4]
     2e8: e1a00004     	mov	r0, r4
     2ec: e592105c     	ldr	r1, [r2, #0x5c]
     2f0: e3811002     	orr	r1, r1, #2
     2f4: e582105c     	str	r1, [r2, #0x5c]
     2f8: eb000000     	bl	0x300 <func_ov264_020cc1fc+0x300> @ imm = #0x0
			000002f8:  R_ARM_PC24	func_ov264_020ce9fc-0x8
     2fc: e58403c0     	str	r0, [r4, #0x3c0]
     300: e2840064     	add	r0, r4, #100
     304: e28d6010     	add	r6, sp, #16
     308: e890000f     	ldm	r0, {r0, r1, r2, r3}
     30c: e886000f     	stm	r6, {r0, r1, r2, r3}
     310: e59f50a8     	ldr	r5, [pc, #0xa8]         @ 0x3c0 <func_ov264_020cc1fc+0x3c0>
     314: e8950007     	ldm	r5, {r0, r1, r2}
     318: e8860007     	stm	r6, {r0, r1, r2}
     31c: e2840f8b     	add	r0, r4, #556
     320: e3a01010     	mov	r1, #16
     324: e3a02064     	mov	r2, #100
     328: eb000000     	bl	0x330 <func_ov264_020cc1fc+0x330> @ imm = #0x0
			00000328:  R_ARM_PC24	func_01fffca8-0x8
     32c: e58403ac     	str	r0, [r4, #0x3ac]
     330: e1a00006     	mov	r0, r6
     334: eb000000     	bl	0x33c <func_ov264_020cc1fc+0x33c> @ imm = #0x0
			00000334:  R_ARM_PC24	func_ov107_020c319c-0x8
     338: e59423ac     	ldr	r2, [r4, #0x3ac]
     33c: e3a01004     	mov	r1, #4
     340: e5820000     	str	r0, [r2]
     344: e2840f51     	add	r0, r4, #324
     348: e3a02064     	mov	r2, #100
     34c: eb000000     	bl	0x354 <func_ov264_020cc1fc+0x354> @ imm = #0x0
			0000034c:  R_ARM_PC24	func_01fffca8-0x8
     350: e1a05000     	mov	r5, r0
     354: e1a00006     	mov	r0, r6
     358: eb000000     	bl	0x360 <func_ov264_020cc1fc+0x360> @ imm = #0x0
			00000358:  R_ARM_PC24	func_ov107_020c319c-0x8
     35c: e5850000     	str	r0, [r5]
     360: e58403b0     	str	r0, [r4, #0x3b0]
     364: e59f0058     	ldr	r0, [pc, #0x58]         @ 0x3c4 <func_ov264_020cc1fc+0x3c4>
     368: eb000000     	bl	0x370 <func_ov264_020cc1fc+0x370> @ imm = #0x0
			00000368:  R_ARM_PC24	func_0203355c-0x8
     36c: e28dd04c     	add	sp, sp, #76
     370: e8bd81f8     	pop	{r3, r4, r5, r6, r7, r8, pc}
     374: 00 00 00 00  	.word	0x00000000
			00000374:  R_ARM_ABS32	data_ov264_020cebc4
     378: f5 e6 ff ff  	.word	0xffffe6f5
     37c: 3c e0 ff ff  	.word	0xffffe03c
     380: 00 00 00 00  	.word	0x00000000
			00000380:  R_ARM_ABS32	func_ov264_020cc5c4
     384: 00 00 00 00  	.word	0x00000000
			00000384:  R_ARM_ABS32	func_ov264_020cc61c
     388: 00 00 00 00  	.word	0x00000000
			00000388:  R_ARM_ABS32	func_ov264_020cc6a8
     38c: 00 00 00 00  	.word	0x00000000
			0000038c:  R_ARM_ABS32	func_ov264_020cca58
     390: 00 00 00 00  	.word	0x00000000
			00000390:  R_ARM_ABS32	func_ov264_020cc8e4
     394: 00 00 00 00  	.word	0x00000000
			00000394:  R_ARM_ABS32	func_ov264_020ccab4
     398: 00 00 00 00  	.word	0x00000000
			00000398:  R_ARM_ABS32	func_ov264_020cc9e0
     39c: 00 00 00 00  	.word	0x00000000
			0000039c:  R_ARM_ABS32	func_ov264_020ccde8
     3a0: 00 00 00 00  	.word	0x00000000
			000003a0:  R_ARM_ABS32	func_ov264_020cce14
     3a4: 00 00 00 00  	.word	0x00000000
			000003a4:  R_ARM_ABS32	func_ov264_020cbfc8
     3a8: 00 00 00 00  	.word	0x00000000
			000003a8:  R_ARM_ABS32	data_ov264_020cec2c
     3ac: 00 00 00 00  	.word	0x00000000
			000003ac:  R_ARM_ABS32	func_ov264_020cc09c
     3b0: 00 00 00 00  	.word	0x00000000
			000003b0:  R_ARM_ABS32	data_ov264_020cec38
     3b4: 9a 09 00 00  	.word	0x0000099a
     3b8: cd 0c 00 00  	.word	0x00000ccd
     3bc: fc ff ff 00  	.word	0x00fffffc
     3c0: 00 00 00 00  	.word	0x00000000
			000003c0:  R_ARM_ABS32	data_02041dc8
     3c4: 5d 01 00 00  	.word	0x0000015d
