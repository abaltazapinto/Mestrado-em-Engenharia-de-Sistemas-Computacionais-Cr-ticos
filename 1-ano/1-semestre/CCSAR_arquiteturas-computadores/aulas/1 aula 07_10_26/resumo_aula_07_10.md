
# CCSAR — Aula 1 — 07/10/2026

## RISC-V Instruction Encoding

**Prioridade aplicada:** `SRT > slides/PDF > notas pessoais`. Li o SRT completo; a parte útil da aula vai aproximadamente até aos 77 minutos, depois há conversa não relacionada com a matéria. Os slides foram usados para resolver nomes, campos e diagramas que ficaram pouco claros na transcrição.

---

# 1. Reconstruct the Lecture

## 1.1 Ideia de partida: Assembly não é o que o processador executa

A aula começa pela passagem:

```text
Assembly
   ↓ assembler
Machine code
   ↓
bits interpretados pelo CPU
```

Nós escrevemos algo como:

```asm
add s2, s3, s4
```

mas a máquina recebe uma palavra binária.

Na base **RV32I** estudada nesta aula, cada instrução ocupa **32 bits**. Esses 32 bits são divididos em **fields**.

Os campos fundamentais apresentados foram:

| Campo      | Significado              |
| ---------- | ------------------------ |
| `opcode` | grupo/tipo da operação |
| `rd`     | destination register     |
| `rs1`    | source register 1        |
| `rs2`    | source register 2        |
| `funct3` | refina a operação      |
| `funct7` | refina a operação      |
| `imm`    | immediate / constante    |

O professor insiste desde cedo numa regra:

> os campos que aparecem em vários formatos são mantidos, sempre que possível, **nas mesmas posições**.

Esse é o princípio de **regularidade** que vai explicar praticamente todos os formatos. aula 1 07_10_26

---

## 1.2 Número do registo ≠ conteúdo do registo

Isto foi explicitamente salientado.

Se uma instrução contém:

```text
rs1 = 20
```

isso significa:

```text
usar x20
```

Não significa:

```text
o valor 20 está dentro do registo
```

Além disso, nomes ABI como:

```text
s0
s1
t0
ra
```

são convenientes para o programador, mas na instrução são codificados os **números reais dos registos `x0...x31`**.

### Porquê 5 bits?

Existem 32 registos:

\[
2^5 = 32
\]

Logo:

```text
00000 → x0
...
11111 → x31
```

Portanto:

```text
rd  = 5 bits
rs1 = 5 bits
rs2 = 5 bits
```

O professor relacionou isto com um compromisso de arquitetura: mais registos exigiriam mais bits em cada instrução, deixando menos espaço para outras informações. aula 1 07_10_26

---

## 1.3 Bit 0 à direita, bit 31 à esquerda

Nos diagramas:

```text
31                              0
MSB                            LSB
```

Isto representa a **posição dos bits dentro da palavra de instrução**.

O professor avisou que isto não deve ser confundido com a forma como os bytes são organizados fisicamente em memória/endianess.

---

## 1.4 Opcode: por onde começa o decoding

O `opcode` tem **7 bits**.

Mais precisamente:

```text
bits [6:0]
```

São os **7 bits menos significativos** da instrução.

O CPU usa o opcode para perceber que tipo/grupo de instrução está a interpretar e, consequentemente, como deve interpretar os restantes bits.

Mas:

> **opcode não identifica necessariamente a operação completa.**

Por exemplo, `add` e `sub` pertencem ao mesmo grupo.

Então entra:

```text
opcode
   +
funct3
   +
funct7
```

para distinguir a operação concreta.

Foi precisamente por isso que o professor mostrou `add` e `sub`: podem partilhar `opcode` e `funct3`, sendo necessário olhar para `funct7`. aula 1 07_10_26

---

# 1.5 R-format — operações registo-registo

Exemplo central:

```asm
add x9, x20, x21
```

Significa:

```text
x9 = x20 + x21
```

Formato:

```text
31        25 24   20 19   15 14  12 11    7 6      0
+-----------+-------+-------+------+--------+--------+
|  funct7   |  rs2  |  rs1  |funct3|   rd   | opcode |
+-----------+-------+-------+------+--------+--------+
    7          5       5       3      5        7
```

Neste exemplo:

```text
rd  = x9
rs1 = x20
rs2 = x21
```

A instrução apresentada nos slides é codificada campo a campo até chegar à palavra binária/hexadecimal.

### O que o professor quer que saibas

Não é decorar:

```text
opcode(add) = 0110011
```

O essencial é conseguir pensar:

```text
add usa:
2 registos fonte
1 registo destino
nenhum immediate
→ R-format
```

---

# 1.6 I-format — um registo + immediate

Foram usados principalmente:

```asm
addi
lw
```

Formato:

```text
31                   20 19   15 14  12 11    7 6      0
+----------------------+-------+------+--------+--------+
|     imm[11:0]        |  rs1  |funct3|   rd   | opcode |
+----------------------+-------+------+--------+--------+
          12              5       3      5        7
```

### `addi`

```asm
addi rd, rs1, imm
```

conceptualmente:

```text
rd = rs1 + imm
```

Exemplo da aula:

```asm
addi s1, s0, 6
```

---

### `lw`

Também é I-format:

```asm
lw rd, offset(rs1)
```

Significado:

```text
rd = Mem[rs1 + offset]
```

Exemplo:

```asm
lw s0, 20(s2)
```

Aqui:

```text
rs1 = s2          base address
imm = 20          offset
rd  = s0          recebe o valor da memória
```

### Porque são 12 bits de immediate?

Porque depois de reservar:

```text
opcode = 7
rd     = 5
rs1    = 5
funct3 = 3
```

sobram:

\[
32-(7+5+5+3)=12
\]

Logo:

```text
imm = 12 bits
```

O professor usou este exemplo precisamente para mostrar que os tamanhos dos campos resultam de compromissos dentro dos 32 bits.

---

## 1.7 Sign extension do immediate

Os immediates assinados precisam de ser usados juntamente com valores de 32 bits.

Por isso, o valor de 12 bits é **sign-extended** antes da operação.

Modelo simples:

```text
12-bit immediate
      ↓ sign extension
32-bit value
      ↓
operação
```

O professor salientou isto porque mais tarde a posição do **sign bit** vai influenciar os formatos B e J.

---

## 1.8 Caso especial: shifts imediatos

O professor também explicou que um shift numa arquitetura de 32 bits não necessita realmente de um immediate completo de 12 bits.

Para deslocar uma palavra de 32 bits basta representar valores aproximadamente até 31:

```text
5 bits
```

Apesar disso, a instrução continua encaixada no formato I de 32 bits.

Foi apresentado como um detalhe mais específico; **não era o foco principal da aula**.

---

# 1.9 S-format — stores

Aqui aparece uma das ideias mais importantes da aula.

Exemplo:

```asm
sw s2, 48(s1)
```

Significado:

```text
Mem[s1 + 48] = s2
```

Um `store` precisa de:

```text
rs1 → endereço base
rs2 → valor que vai ser escrito
imm → offset
```

Mas não precisa de:

```text
rd
```

porque não escreve nenhum resultado no register file.

aula 1 07_10_26

---

## Então onde colocamos o immediate?

O problema é:

```text
precisamos rs1
precisamos rs2
precisamos 12 bits de immediate
```

RISC-V decide **não mover rs1 nem rs2**.

Em vez disso, parte o immediate:

```text
31       25 24   20 19   15 14 12 11      7 6      0
+----------+-------+-------+-----+-----------+--------+
|imm[11:5] |  rs2  |  rs1  |funct3|imm[4:0]| opcode |
+----------+-------+-------+-----+-----------+--------+
     7        5       5       3      5          7
```

Portanto:

```text
imm[11:5] → 7 bits
imm[4:0]  → 5 bits

7 + 5 = 12 bits
```

Não são dois immediates.

É **um único immediate de 12 bits dividido em dois campos**.

Esta foi uma das ideias centrais verbalizadas pelo professor: preservar os campos comuns reduz a complexidade da descodificação. aula 1 07_10_26

---

# 1.10 Load vs Store

A aula reforçou implicitamente uma característica load/store de RISC-V.

Para calcular algo que está em memória:

```text
memory
 ↓ lw
register
 ↓ operação ALU
register
 ↓ sw
memory
```

Exemplo dos slides:

```asm
lw   x9, 120(x10)
add  x9, x21, x9
addi x9, x9, 1
sw   x9, 120(x10)
```

E aparecem sucessivamente:

```text
I-format
R-format
I-format
S-format
```

O objetivo não era decorar os bits de cada linha, mas perceber **porque cada instrução precisa daquele formato**.

---

# 1.11 A regra de design que aparece aqui

Neste ponto, o professor repete a ideia principal:

```text
manter:
opcode
rs1
rs2
rd
funct3
```

sempre que esses campos existam, nas mesmas posições.

Se um formato não precisa de determinado campo:

```text
reutilizar esse espaço
```

em vez de redesenhar toda a instrução.

Resultado:

```text
mais trabalho para assembler/encoding
              ↓
hardware de decoding mais regular
              ↓
hardware mais simples
```

Segundo o professor, esta é uma expressão da filosofia RISC:

> colocar complexidade preferencialmente no software em vez de complicar o hardware. aula 1 07_10_26

---

# 1.12 U-format — constantes maiores

Chega então o problema:

```text
12 bits de immediate nem sempre chegam.
```

Daí instruções como:

```asm
lui
```

O U-format tem:

```text
+---------------------------+-------+--------+
|      immediate 20 bits    |  rd   | opcode |
+---------------------------+-------+--------+
             20                5       7
```

### `lui`

A ideia explicada:

```text
20-bit immediate
        ↓
bits superiores do registo
        ↓
lower 12 bits = 0
```

Assim é possível construir valores de 32 bits usando mais de uma instrução.

O professor relacionou isto com a pseudo-instrução:

```asm
li
```

que pode ser transformada pelo assembler em múltiplas instruções reais.

Também foi referido:

```asm
auipc
```

para construção de valores relativos ao `PC`.

---

# 1.13 Resumo R, I, S, U

Esta síntese é central:

| Formato     | Informação essencial                       |
| ----------- | -------------------------------------------- |
| **R** | `rs1`, `rs2`, `rd`                     |
| **I** | `rs1`, `rd`, immediate 12 bits           |
| **S** | `rs1`, `rs2`, immediate 12 bits dividido |
| **U** | `rd`, immediate 20 bits                    |

Todos têm:

```text
opcode
```

e procuram manter campos equivalentes nas mesmas posições. aula 1 07_10_26

---

# 1.14 B-format — branches

Depois a aula passa a controlo de fluxo.

Exemplo:

```asm
bne s3, s4, L1
```

Um branch precisa de:

```text
rs1
rs2
offset
```

e altera o fluxo aproximadamente como:

```text
if condition:
    PC = PC + offset
```

A `label`:

```asm
L1
```

não aparece diretamente na instrução.

O assembler calcula:

```text
distância entre a instrução e L1
```

e codifica essa distância.

---

## Relação B ↔ S

O professor explica o B-format como uma variante do S-format.

```text
S-format
rs1 + rs2 + split immediate

B-format
rs1 + rs2 + split/reordered branch offset
```

A estrutura é mantida e os bits do immediate são rearranjados.

---

# 1.15 Por que o bit 0 do branch não é armazenado?

Este ponto recebeu bastante explicação.

Targets de instruções estão alinhados pelo menos a **2 bytes**.

Portanto, o offset é sempre múltiplo de 2:

```text
...0₂
```

O bit 0 será sempre:

```text
0
```

Logo, não precisamos armazená-lo.

Em vez de desperdiçar um bit:

```text
encoded bits + implicit 0
```

permitem representar uma distância maior.

### Porque não eliminar também o bit 1?

O professor explicou a razão:

RISC-V possui a extensão de instruções comprimidas, com instruções de **16 bits = 2 bytes**.

Logo, um target válido pode ser apenas alinhado a dois bytes:

```text
...10₂
```

Não podemos assumir que os dois últimos bits são sempre zero.

Este detalhe aparece também nas tuas notas, embora de forma bastante condensada. aula 1 07_10_26

---

# 1.16 Sign bit e regularidade

Branches podem saltar:

```text
para a frente
ou
para trás
```

Logo, o offset é signed.

O professor explicou que o bit de sinal dos immediates assinados é mantido numa posição regular, no bit mais significativo da instrução:

```text
instruction bit 31
```

Isto permite ao hardware começar a fazer **sign extension** em paralelo com outras partes do decoding.

Aqui volta a mesma filosofia:

> reorganizamos os bits para simplificar hardware futuro.

---

# 1.17 J-format — jumps

O formato J é apresentado com:

```asm
jal
```

`jal` faz aproximadamente:

```text
rd = PC + 4
PC = PC + offset
```

O J-format reutiliza a ideia do U-format:

```text
U → large immediate + rd
J → reordered jump immediate + rd
```

Tal como no branch:

```text
bit 0 do offset não é codificado
```

porque o target é pelo menos 2-byte aligned.

O immediate codificado tem 20 bits, representando efetivamente um offset signed de 21 bits com o zero implícito.

---

# 1.18 Grande ideia de B e J

Não deves memorizar isto como:

```text
B é estranho
J é estranho
```

O raciocínio ensinado foi:

```text
S já tem rs1 + rs2 + immediate
        ↓
é uma boa base para branch
        ↓
B reutiliza S

U já tem rd + large immediate
        ↓
é uma boa base para jump
        ↓
J reutiliza U
```

Só se reorganizam bits do immediate para otimizar o offset PC-relative.

---

# 1.19 Disassembly

A última grande parte da aula inverte o processo:

```text
Assembly → machine code
```

passa a:

```text
machine code → assembly
```

Isto é **disassembly**.

O professor dá exemplos de aplicações:

- debugging/inspection;
- reverse engineering;
- malware analysis;
- verificar código produzido pelo compilador;
- analisar aquilo que realmente vai executar no hardware.

Isto torna-se particularmente relevante para sistemas críticos porque o compilador aplica otimizações, e o código efetivamente executado pode ser bastante diferente do C original. O professor ligou isto à dificuldade de analisar comportamento temporal/WCET. aula 1 07_10_26

---

# 1.20 Disassembly ≠ recuperar o código C

Este é um ponto importante.

O caminho:

```text
C
 ↓ compiler
Assembly
 ↓ assembler
Machine code
```

pode ser parcialmente invertido:

```text
Machine code
 ↓ disassembler
Assembly
```

Mas não:

```text
Machine code
 ↓
C original perfeito
```

Perdem-se coisas como:

```text
nomes das variáveis
nomes das funções
comentários
tipos
estrutura original do programa
```

e as otimizações do compilador podem:

```text
reordenar instruções
eliminar variáveis
inline funções
transformar completamente certas expressões
```

Daí o assembly recuperado poder diferir muito do source original.

---

# 1.21 Como fazer decoding manual

O procedimento ensinado no fim da aula é muito importante para práticas:

```text
machine word
    ↓
converter/ver em binário
    ↓
olhar bits [6:0]
    ↓
opcode
    ↓
determinar grupo/formato
    ↓
funct3/funct7 se necessário
    ↓
separar os restantes campos
    ↓
interpretar rd / rs1 / rs2 / imm
    ↓
assembly
```

O professor menciona `objdump` como exemplo de disassembler em Linux. aula 1 07_10_26

---

## Raciocínio para aulas práticas

Não comeces por decorar a tabela toda.

### Assembly → machine code

Pensa sempre:

```text
1. Que informação a instrução precisa?
2. Há rd?
3. Há rs1?
4. Há rs2?
5. Há immediate?
6. É data processing, memory ou control flow?
7. Isso conduz a R / I / S / U / B / J.
```

### Machine code → assembly

Faz o contrário:

```text
opcode → formato → funct → operandos → instrução
```

Essa é exatamente a lógica que a aula tentou construir.

---

# 2. Explain difficult parts simply

## A. Porque é que o S-format parte o immediate?

Imagina uma estante com posições fixas.

No formato R tens:

```text
[ funct7 ][ rs2 ][ rs1 ][ funct3 ][ rd ][ opcode ]
```

Um `store` não precisa de `rd`.

Mas precisa de um offset.

Em vez de mover tudo:

```text
rs1
rs2
funct3
opcode
```

o RISC-V mete parte do offset no espaço que ficou disponível e outra parte noutro espaço.

```text
[ imm ][ rs2 ][ rs1 ][ funct3 ][ imm ][ opcode ]
```

**O immediate sofre. O decoder beneficia.**

---

## B. Porque `opcode` não chega?

Pensa no opcode como uma **categoria**.

```text
opcode = arithmetic-register
```

Dentro dessa categoria podem existir:

```text
add
sub
and
or
xor
...
```

Então:

```text
opcode → família
funct3/funct7 → membro concreto
```

---

## C. Porque os branches não guardam bit 0?

Se sabes antecipadamente que um número termina sempre em:

```text
0
```

não vale a pena armazenar esse zero.

Exemplo conceptual:

```text
encoded: 101101
real:    1011010
```

Ganhei alcance sem aumentar a instrução.

---

## D. Porque os formatos estranhos simplificam o hardware?

À primeira vista:

```text
split immediate
reordered immediate
```

parece mais complicado.

É mais complicado para **quem codifica a instrução**.

Mas o hardware encontra:

```text
rs1 sempre aqui
rs2 sempre aqui
rd sempre aqui
opcode sempre aqui
```

Isso é precisamente a regularidade pretendida.

---

## E. Porque não conseguimos recuperar o C original?

Compilar é uma transformação com perda de informação.

Por exemplo:

```c
int total = a + b;
```

depois da compilação pode não existir qualquer conceito chamado:

```text
"total"
```

Só existem registos, endereços e instruções.

O disassembler recupera essas instruções, não a intenção original do programador.

---

# 3. Detect and correct issues

## Correção 1 — “o CPU olha para os primeiros 7 bits”

As notas dizem isso. aula 1 07_10_26

Mais rigoroso:

```text
opcode = bits [6:0]
```

ou seja, **os 7 bits menos significativos**, à direita nos diagramas.

“Primeiros” é ambíguo.

---

## Correção 2 — “todos os formatos têm 32 bits”

Para o contexto principal desta aula:

> **as instruções base RV32I analisadas têm 32 bits.**

Mas o próprio professor depois refere a extensão comprimida, que permite instruções de **16 bits**.

Portanto, escrever simplesmente:

```text
RISC-V = todas as instruções têm sempre 32 bits
```

seria demasiado geral.

---

## Correção 3 — `rd` no load/store

Nas tuas notas aparece próximo do load/store:

> “rd não há registo do destino”. aula 1 07_10_26

Isto só é correto para **store**.

```asm
lw rd, imm(rs1)
```

tem `rd`.

```asm
sw rs2, imm(rs1)
```

não tem `rd`.

Esta distinção é importante.

---

## Correção 4 — opcode não identifica sempre a instrução completa

A formulação:

```text
opcode → instrução
```

é demasiado forte.

Melhor:

```text
opcode → grupo/formato
opcode + funct3/funct7 → operação concreta, quando necessário
```

`add` e `sub` são precisamente o exemplo mostrado pelo professor.

---

## Correção 5 — U-format

Nas notas a frase final pode dar a impressão errada sobre onde entram os bits. aula 1 07_10_26

A ideia correta ensinada é:

```text
U-format:
20-bit immediate → bits superiores
lower 12 bits → 0
```

Não são “5 bits mais significativos”.

---

## Correção 6 — branch alignment

A ideia:

```text
instruções = 4 bytes
→ endereço termina em 00
```

é apenas parcialmente suficiente.

O professor corrige isso na própria aula:

```text
RISC-V compressed → instruções de 2 bytes
```

Por isso B/J só podem assumir com segurança:

```text
bit 0 = 0
```

e **não**:

```text
bits 1:0 = 00
```

---

## Correção 7 — `gcc -s` / `gcc -S`

A transcrição/notas no final não permitem determinar com confiança se o professor disse `-s` ou `-S`.

**Not clearly covered in the lecture.**

O ponto efetivamente ensinado foi apenas que se pode compilar um pequeno programa, observar assembly e depois experimentar um disassembler.

---

## Material do PDF que não considero matéria principal reconstruída

Os slides incluem uma secção explícita sobre **Addressing Modes**.

No SRT, essa secção não aparece claramente como tópico explicado em aula.

**Not clearly covered in the lecture.**

Por isso não a tratei como núcleo da reconstrução, apesar de estar no PDF.

---

# 4. 30-Min Notebook Summary

## RISC-V — Instruction Encoding

### Base

- Assembly → assembler → machine code.
- RV32I base: instrução = 32 bits.
- Bit `31` = MSB; bit `0` = LSB.
- Campos:
  - `opcode`
  - `rd`
  - `rs1`
  - `rs2`
  - `funct3`
  - `funct7`
  - `imm`
- `x0...x31` → 32 registos → **5 bits** por número de registo.
- Número do registo ≠ valor dentro do registo.
- ABI names (`s0`, `t0`, etc.) → convertidos para números `xN`.

### Decoding

```text
opcode = bits [6:0]
```

- opcode identifica grupo/formato.
- `funct3/funct7` refinam operação.
- manter campos comuns nas mesmas posições → hardware mais simples.

### R-format

```text
funct7 | rs2 | rs1 | funct3 | rd | opcode
```

- 2 sources.
- 1 destination.
- Ex.: `add rd, rs1, rs2`.

### I-format

```text
imm[11:0] | rs1 | funct3 | rd | opcode
```

- immediate = 12 bits.
- `addi`.
- `lw`.
- immediate signed → sign extension.

```text
lw rd, imm(rs1)
rd = Mem[rs1 + imm]
```

### S-format

```text
imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode
```

- store.
- não existe `rd`.
- `rs1` = base.
- `rs2` = valor a guardar.
- immediate = 12 bits dividido.

```text
sw rs2, imm(rs1)
Mem[rs1 + imm] = rs2
```

### U-format

```text
imm[31:12] | rd | opcode
```

- immediate = 20 bits.
- grandes constantes.
- `lui`.
- lower 12 bits = zero.
- `auipc` → PC-relative.

### Resumo

```text
R → rs1 + rs2 + rd
I → rs1 + rd + imm12
S → rs1 + rs2 + imm12 split
U → rd + imm20
```

### Control flow

- B = branches.
- J = jumps.
- PC-relative:

```text
target = PC + offset
```

### B-format

- semelhante ao S.
- `rs1`, `rs2`.
- immediate reorganizado.
- signed offset.
- bit 0 implícito = 0.
- label → assembler calcula offset.

### J-format

- semelhante ao U.
- `jal`.
- `rd = PC + 4`.
- `PC = PC + offset`.
- immediate reorganizado.
- bit 0 implícito.

### Porquê só omitir bit 0?

- compressed RISC-V pode ter instruções de 16 bits.
- targets podem estar alinhados a 2 bytes.
- bit 0 = sempre zero.
- bit 1 não necessariamente zero.

### Princípio central

```text
Simplicity favors regularity
```

- manter fields no mesmo sítio.
- encoding pode ser mais complexo.
- decoder/hardware torna-se mais simples.

### Disassembly

```text
machine code → disassembler → assembly
```

Não recupera:

- C original;
- nomes de variáveis;
- comentários;
- tipos;
- estrutura original.

Compiler optimizations podem alterar muito o assembly.

### Manual decoding

```text
hex/binary
→ opcode
→ format
→ funct3/funct7
→ rd/rs1/rs2/imm
→ assembly
```

`objdump` foi referido como exemplo de disassembler.

---

# 5. Explain Core Concepts — hard ones only

## 1. Regularidade

O objetivo não é fazer cada formato individualmente “bonito”.

É fazer os vários formatos parecerem-se.

```text
mesmos campos
→ mesmas posições
→ menos lógica de seleção
→ decoding mais simples
```

---

## 2. Split immediate

No S-format:

```text
imm[11:5] ........ imm[4:0]
```

são duas partes do **mesmo número**.

Mentalmente:

```text
juntar → immediate de 12 bits
```

---

## 3. Opcode + funct

Não penses:

```text
opcode = instrução
```

Pensa:

```text
opcode = família
funct = variante
```

Exemplo:

```text
opcode → operação R
funct3/funct7 → add ou sub
```

---

## 4. B/J e o zero implícito

O offset representa sempre múltiplos de 2.

Logo:

```text
bit0 = 0
```

não precisa de ser armazenado.

Esse espaço efetivamente aumenta o alcance do salto.

---

## 5. Disassembly

Disassembler resolve:

```text
bits → instruções
```

Não resolve:

```text
instruções → intenção original do programador
```

É a diferença essencial entre **disassembly** e reconstruir source code.

---

# 6. Essential Exam Questions — 5 total

### 1 — Conceptual

**Porque `rd`, `rs1` e `rs2` têm 5 bits?**

**Resposta:** porque RISC-V tem 32 registos identificados de `x0` a `x31`.

**Raciocínio:** \(2^5=32\), logo 5 bits representam todos os números de registo.

---

### 2 — Conceptual

**Porque o immediate do S-format está dividido em dois campos?**

**Resposta:** para manter `rs1`, `rs2`, `funct3` e `opcode` nas mesmas posições dos outros formatos.

**Raciocínio:** a codificação fica menos conveniente, mas o hardware de decoding fica mais regular.

---

### 3 — Practical

Dada:

```asm
sw x7, -6(x19)
```

**Qual o formato e o significado dos operandos?**

**Resposta:**

```text
S-format
rs1 = x19
rs2 = x7
imm = -6
não existe rd
```

**Raciocínio:** store precisa do endereço base, do valor a escrever e do offset.

---

### 4 — Practical

Dada:

```asm
add x9, x20, x21
```

**Identifica os campos principais.**

**Resposta:**

```text
R-format
rd  = x9
rs1 = x20
rs2 = x21
```

**Raciocínio:** `add` opera sobre dois registos fonte e escreve num registo destino.

---

### 5 — Multiple choice

Um disassembler recebe um executável. O que consegue normalmente reconstruir?

**A)** O C original completo
**B)** Assembly correspondente ao machine code
**C)** Comentários e nomes originais das variáveis
**D)** Tipos C originais

**Resposta: B.**

**Raciocínio:** o machine code preserva as instruções, mas muita informação do source desaparece durante compilação.

---

# 6. Common Pitfalls

1. **Confundir número e conteúdo do registo.**`rs1 = 20` significa `x20`, não “valor 20”.
2. **Pensar que store tem `rd`.**`lw` tem destino; `sw` não tem.
3. **Pensar que o S-format possui dois immediates.**`imm[11:5]` e `imm[4:0]` formam um único valor.
4. **Achar que opcode sozinho identifica sempre a operação.**Muitas vezes também são necessários `funct3`/`funct7`.
5. **Confundir disassembly com recuperação do source original.**
   O disassembler recupera assembly, não comentários, nomes, tipos ou necessariamente a estrutura original do C.
