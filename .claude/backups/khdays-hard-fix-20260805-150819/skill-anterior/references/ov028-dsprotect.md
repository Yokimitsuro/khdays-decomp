# ov028 = DS Protect 1.10 (IDENTIFICADO Y VERIFICADO, 2026-07-19)

ov028 no es codigo del juego: es **DS Protect 1.10**, una libreria antipirateria comercial
que detecta emuladores y flashcarts, usada por 300+ titulos de DS. Identificada por un
usuario del Discord de decomp.me y **verificada aqui descifrando los cuerpos**.

Fuente de referencia (decompilacion publica, NO copiamos codigo suyo al repo, solo nombres
y semantica): https://github.com/taxicat1/dsprot rama `1.10`.

## Por que esto importa

Explica de golpe tres rarezas que llevaban meses documentadas sin causa:
- **Por que `0208a994` (RC4_Init) exige compilarse con mwcc 1.2 sp4** y no con el 3.0 del
  juego: es middleware precompilado de un tercero, no lo compilo el estudio.
- **Por que el `0x88888889`** (reciproco de /15) en el descifrador: es `if (i % 15 == 0)
  key[i] ^= 0xFF` en la derivacion de clave.
- **Por que el KSA de RC4 iba al reves** (i de 255 a 0): es una modificacion deliberada de
  DS Protect sobre el RC4 estandar; el propio fuente lo comenta.

El patron `0x88888889` aparece en NUEVE overlays (ov005/028/039/058/078/095/115/116...), asi
que todo eso es el mismo producto y se puede nombrar igual.

## El mapa de nombres (probado, no inferido)

`.text` en claro:

| direccion | nombre real | notas |
|---|---|---|
| `0208a7e0` | `Encryptor_StartRange` | descifra el rango; clave = palabra anterior |
| `0208a8ac` | `Encryptor_EndRange` | vuelve a cifrar |
| `0208a994` | `RC4_Init` | KSA modificado (i: 255 -> 0). **mwcc 1.2 sp4** |
| `0208aa08` | `RC4_InitSBox` | `sbox[i] = i ^ 0x01` |
| `0208aa54` | `RC4_Byte` | |
| `0208aa78` | `RC4_EncryptInstructions` | descifrar == cifrar |
| `0208ab14` | veneer de interworking a `aa78` | vive en `libs/nitro/wm/` |
| `0208ab20` | `RC4_InitAndEncryptInstructions` | |
| `0208ab78` | `RC4_InitAndDecryptInstructions` | |

`.rodata` (cuerpos cifrados; siguen siendo `data(any)`, ver abajo):

| direccion | nombre real | tarea que encola |
|---|---|---|
| `0208abd0` | `MACOwner_IsBad` | (es la tarea) |
| `0208af30` | `ROMTest_IsBad` | (es la tarea) |
| `0208b040` | `DSProt_DetectFlashcart` | `af30` |
| `0208b120` | `DSProt_DetectNotFlashcart` | `af30` |
| `0208b200` | `DSProt_DetectEmulator` | `abd0` |
| `0208b2e0` | `DSProt_DetectNotEmulator` | `abd0` |
| `0208b3c0` | `DSProt_DetectDummy` | cola vacia |
| `0208b490` | `DSProt_DetectNotDummy` | cola vacia |

El orden de direcciones sigue el orden de declaracion de `dsprot_main.c`. Los `Not*` son la
misma funcion con la polaridad del resultado invertida. Los `Dummy` no encolan nada, por eso
son 208 B en vez de 224.

## Como se verifico (repetible)

`python tools/dsprot_decrypt.py` reimplementa el algoritmo y descifra los cuerpos
(el `scratchpad/dsprot.py` original era de una sesion y ya no existe):

1. El prologo en claro acaba en `mov r0,#6; add r0,pc,r0,lsl#1; bl 0208a7e0`. El `b` que
   viene despues salta la palabra clave; **su destino es el inicio del cuerpo cifrado**.
   (Calcular el inicio desde el `bl` da basura: hay que seguir el `b`.)
2. Clave: `key_ins` = palabra anterior al cuerpo; `key[i] = key_ins >> ((i%4)*8)`, con
   `key[i] ^= 0xFF` si `i % 15 == 0`.
3. Tamano: avanzar hasta que reaparezca `key_ins` (esa es la marca de fin).
4. Por cada palabra: byte 0 y 1 con RC4, byte 2 `^ 0x01`, **byte 3 intacto**. Por eso el
   opcode alto se lee en claro y los prologos parecen validos en la ROM estatica.

El resultado es ARM limpio que mapea linea por linea contra `dsprot_main.c`: `sub r0,r0,#0x320`
es `func_queue[i] -= DSP_OBFS_OFFSET` (el 0x320 del fuente aparece literal en el prologo),
`blx r0` la llamada a la tarea, `add`+`lsl #1` el acumulador, y `cmp sl,#0 / cmpne sb,#0 /
blx sl` el `if (callback != NULL && ret)`.

## Lo que NO cambia

⚠ **Sigue sin tocarse la clasificacion `.rodata` del blob.** Saber que hay dentro no lo
convierte en `.text`: en la ROM estatica los cuerpos estan cifrados, `dsd delink` peta con
`IllegalIns @0x0208ac00` si se marca como codigo (probado y revertido el 2026-07-10), y los
simbolos `kind:data(any)` ya resuelven los 17 relocs `module:none`. La identificacion es para
**nombrar y entender**, no para recolocar secciones.

ov028 ya esta 9/9 en `.text`, asi que esto no suma funciones casadas. Lo que suma es que ocho
simbolos dejan de llamarse `Ov028_ProtectedPredicate_bNNN` y pasan a tener su nombre real, y
que los otros ocho overlays con el mismo patron se pueden nombrar sin volver a analizarlos.

## Credito

Los nombres y la semantica salen de la decompilacion de taxicat1
(https://github.com/taxicat1/dsprot). Si algo de DS Protect acaba documentado en el README
del proyecto, hay que citarla.
