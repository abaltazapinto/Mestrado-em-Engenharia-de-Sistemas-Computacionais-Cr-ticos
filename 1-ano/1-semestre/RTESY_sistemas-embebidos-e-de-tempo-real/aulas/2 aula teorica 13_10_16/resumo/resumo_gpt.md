
# RTESY — Aula de 13/10/2026

## Total Bandwidth Server (TBS) → Constant Bandwidth Server (CBS)

Usei como **fonte principal os dois SRT** (`RTESY_1.srt` e `Exercício RTESY 13 outubro.srt`). Os slides servem para confirmar fórmulas/estrutura e as tuas notas apenas como apoio. Há vários erros de transcrição automática — por exemplo, “Total Band with Sonor”, “Constant band-aid server”, “declines” — que pelo contexto correspondem claramente a **TBS, CBS e deadlines**. As tuas notas captaram os pontos centrais: TBS recalcula deadlines à chegada, exige conhecer o tempo de execução e não controla overruns; CBS aparece precisamente para resolver esses problemas. notas_13_10_26 notas_13_10_26

---

# 1. Reconstrução da aula

## 1.1 De onde vem esta matéria?

O professor começa por fazer ligação aos **servidores para tarefas aperiódicas** vistos anteriormente.

A ideia essencial de um servidor continua a mesma:

> reservar uma determinada quantidade de CPU para executar trabalho aperiódico sem deixar esse trabalho destruir a escalonabilidade das tarefas periódicas.

Na aula anterior tinham sido vistos servidores associados a **prioridades fixas**. Nesta aula, a questão passa para **prioridades dinâmicas**, particularmente **EDF — Earliest Deadline First**.

No EDF não existe uma prioridade fixa do género:

```text
τ1 > τ2 > servidor
```

A prioridade resulta da **deadline absoluta**:

```text
menor deadline absoluta
        ↓
maior prioridade
        ↓
executa primeiro
```

Isto aparece também explicitamente nas tuas notas: em EDF executa quem tiver a deadline mais próxima. notas_13_10_26

---

# 1.2 Total Bandwidth Server — TBS

O primeiro mecanismo novo da aula é o **Total Bandwidth Server**.

O objetivo apresentado pelo professor é tratar pedidos aperiódicos dentro de EDF **o mais cedo possível**, mas limitar o impacto deles através de uma bandwidth/utilização reservada ao servidor.

O parâmetro fundamental é:

\[
U_s
\]

a utilização/bandwidth reservada ao servidor.

Nos slides aparece:

\[
\boxed{d_k=\max(t_k,d_{k-1})+\frac{c_k}{U_s}}
\]

onde:

- \(t_k\) = instante de chegada do novo job;
- \(c_k\) = execution time desse job;
- \(d_{k-1}\) = deadline atribuída ao job anterior do servidor;
- \(U_s\) = utilização reservada ao servidor;
- \(d_k\) = nova deadline absoluta.

Para o primeiro job:

\[
d_0=0
\]

na explicação utilizada pelo professor.

### Intuição

O servidor está essencialmente a dizer:

> “Este job precisa de \(c_k\) unidades de CPU. Como só tenho direito a uma fração \(U_s\) do processador, vou atribuir-lhe uma deadline suficientemente distante para respeitar essa bandwidth.”

---

## 1.3 Exemplo numérico feito na aula

O professor usa:

\[
Q_s=3
\]

\[
T_s=20
\]

Logo:

\[
U_s=\frac{Q_s}{T_s}
=\frac{3}{20}
=0.15
\]

Ou seja:

\[
\boxed{U_s=15\%}
\]

Chega um job em:

\[
t_1=4
\]

necessitando:

\[
c_1=2
\]

Como é o primeiro:

\[
d_0=0
\]

Então:

\[
d_1=\max(4,0)+\frac{2}{0.15}
\]

\[
d_1=4+13.333
\]

\[
\boxed{d_1\approx17.33}
\]

A tua anotação escreveu `13.333...` como resultado de \(2/(3/20)\), mas isso é apenas **o incremento da deadline**, não a deadline final. notas_13_10_26

Portanto:

\[
\boxed{\frac{2}{U_s}=13.33}
\]

mas

\[
\boxed{d_1=17.33}
\]

Este é um detalhe que vale a pena corrigir nas notas.

---

# 1.4 O TBS continua a usar EDF normal

Depois de atribuir a deadline ao servidor, o escalonamento continua essencialmente EDF.

Supondo:

```text
τ1 deadline = 10
τ2 deadline = 15
server deadline = 17.33
```

executa:

```text
τ1 → τ2 → server
```

Se posteriormente o servidor tiver:

```text
server deadline = 12
```

então pode passar à frente de \(\tau_2\).

Isto explica o gráfico mostrado nos slides: os jobs aperiódicos recebem deadlines e depois **competem na mesma ready queue EDF** que as tarefas periódicas.

---

# 1.5 Porque funciona a bandwidth?

O servidor comporta-se, para efeitos de análise, como carga correspondente a:

\[
U_s
\]

Assim, para EDF, o professor apresenta a condição:

\[
\boxed{U_p+U_s\le1}
\]

onde:

\[
U_p=\sum_i\frac{C_i}{T_i}
\]

é a utilização das tarefas periódicas.

Portanto:

```text
Periodic workload
        +
Server bandwidth
        ≤
100% CPU
```

O servidor limita quanto workload aperiódico é introduzido no sistema.

---

# 1.6 Vantagem importante do TBS

A implementação é relativamente simples.

Quando chega um novo pedido:

1. conhece-se \(t_k\);
2. conhece-se \(c_k\);
3. calcula-se \(d_k\);
4. EDF trata do resto.

Não é necessário gerir continuamente um budget durante a execução.

O professor também refere que o **average response time** dos pedidos aperiódicos tende a ser bom.

---

# 1.7 Problema fundamental nº 1 do TBS

Aqui aparece a primeira grande limitação:

\[
\boxed{\text{é necessário conhecer }c_k\text{ antes da execução}}
\]

Isto foi bastante enfatizado.

Para calcular:

\[
d_k=\max(t_k,d_{k-1})+\frac{c_k}{U_s}
\]

precisamos de \(c_k\).

Mas para trabalho aperiódico/dinâmico pode ser precisamente isso que **não sabemos**.

Exemplo:

```text
request arrives
      ↓
“How long will you execute?”
      ↓
???
```

E o professor salienta precisamente que servidores são interessantes quando o workload é irregular e não conhecemos tudo antecipadamente.

As tuas notas captam esta desvantagem explicitamente. notas_13_10_26

---

# 1.8 Problema fundamental nº 2 — overrun

Ainda pior:

imaginemos que o job declara:

\[
c_k=2
\]

O TBS calcula a deadline usando esses 2.

Mas o job realmente executa:

\[
3
\]

Temos:

```text
expected execution = 2
actual execution   = 3
                         ↑
                      overrun
```

A deadline já foi calculada assumindo 2.

O job mantém uma prioridade baseada nessa deadline e continua a consumir CPU.

Consequência:

> pode interferir mais do que estava previsto com as restantes tarefas.

O professor chama explicitamente a isto **overrun**.

As tuas notas dizem corretamente que o TBS não controla quando uma task executa mais tempo e isso pode estragar o escalonamento. notas_13_10_26

---

# 1.9 É aqui que aparece o CBS

A pergunta feita na aula é essencialmente:

> Como resolvemos estes dois problemas?

Resposta:

\[
\boxed{\text{Constant Bandwidth Server — CBS}}
\]

O CBS continua a ser um servidor de prioridade dinâmica, mas agora passa a existir **capacity management**.

Os parâmetros são:

\[
(Q_s,T_s)
\]

e:

\[
U_s=\frac{Q_s}{T_s}
\]

onde:

- \(Q_s\) = budget/capacidade;
- \(T_s\) = server period;
- \(U_s\) = bandwidth reservada.

---

# 1.10 A grande mudança conceptual do CBS

No TBS perguntávamos:

> “Quanto CPU este novo job vai precisar?”

No CBS a pergunta muda para:

> “Quanto budget ainda resta ao servidor?”

Isto é uma diferença muito importante.

### TBS

Precisa de:

\[
c_k
\]

**antes** de executar.

### CBS

Mantém:

\[
c_s
\]

que representa o **remaining capacity/budget**.

Portanto:

```text
TBS
job → estima C → calcula deadline

CBS
job → observa budget restante → gere deadline/budget
```

---

# 1.11 Quando chega um job e o CBS está idle

O professor apresenta o teste dos slides:

\[
\boxed{t_k+\frac{c_s}{U_s}\le d_s^{current}}
\]

onde:

- \(t_k\) = instante de chegada;
- \(c_s\) = capacidade restante;
- \(U_s\) = utilização do servidor;
- \(d_s^{current}\) = deadline atual do servidor.

### Se for verdadeiro

Mantemos:

\[
\boxed{d_s}
\]

e mantemos o budget restante.

### Se for falso

O servidor é reinicializado:

\[
\boxed{d_s=t_k+T_s}
\]

\[
\boxed{c_s=Q_s}
\]

Mentalmente:

```text
Ainda consigo usar o budget restante
sem violar a bandwidth?
        │
   ┌────┴────┐
   │         │
  SIM       NÃO
   │         │
keep ds    ds = tk + Ts
keep cs    cs = Qs
```

---

# 1.12 Quando o servidor já está ocupado

Se chega outro job enquanto o servidor está ativo, esse job:

\[
\boxed{\text{fica queued}}
\]

e executará depois do job atual.

Ou seja, não precisamos imediatamente de criar um servidor novo.

---

# 1.13 O ponto central: budget vai diminuindo

Enquanto o servidor executa:

\[
c_s\downarrow
\]

Por exemplo:

```text
Qs = 2

executa 0.5 → cs = 1.5
executa 0.5 → cs = 1.0
executa 0.5 → cs = 0.5
executa 0.5 → cs = 0
```

Isto é algo que o TBS não fazia.

O CBS tem de manter registo de **quanto efetivamente executou**. É precisamente por isso que o professor refere maior overhead. notas_13_10_26

---

# 1.14 Quando \(c_s=0\)

Esta foi uma das partes mais importantes da aula e do exercício.

Quando:

\[
\boxed{c_s=0}
\]

o budget esgotou.

Na variante teórica explicada na aula, imediatamente:

\[
\boxed{d_s=d_s+T_s}
\]

e:

\[
\boxed{c_s=Q_s}
\]

Isto é:

```text
budget exhausted
      ↓
postpone deadline
      ↓
replenish budget
      ↓
continue according to EDF
```

A consequência crítica é que ao empurrar:

\[
d_s\rightarrow d_s+T_s
\]

a prioridade do servidor normalmente **diminui**, porque em EDF uma deadline mais distante significa menor prioridade.

Portanto, se o job estiver a consumir CPU demais, o CBS não o deixa manter indefinidamente uma deadline muito urgente.

---

# 1.15 É assim que o CBS controla overruns

Esta é provavelmente a mensagem central da aula.

### TBS

```text
job says C=1
     ↓
deadline calculated for C=1
     ↓
job actually runs C=2
     ↓
continues with same deadline
     ↓
can disturb periodic tasks
```

### CBS

```text
job executes
     ↓
budget decreases
     ↓
budget = 0
     ↓
deadline postponed
budget replenished
     ↓
priority reduced
```

Logo:

\[
\boxed{\text{CBS enforces bandwidth isolation}}
\]

O workload aperiódico pode querer executar mais, mas não consegue manter uma prioridade incompatível com a bandwidth que lhe foi reservada.

---

# 1.16 Deadline absoluta vs deadline relativa

O professor faz aqui uma distinção importante.

Para uma tarefa periódica, podemos ter:

\[
D_i=10
\]

como deadline relativa fixa.

Se chega em \(r_i\):

\[
d_i=r_i+D_i
\]

No servidor, segundo a explicação da aula, **não estamos simplesmente a usar uma deadline relativa fixa do job**.

A deadline absoluta do servidor é calculada e pode ser alterada dinamicamente pelas regras do servidor.

As tuas notas registam precisamente:

> “para os servidores não tem deadline relativo, quando chega calculo deadline absoluto” notas_13_10_26

---

# 1.17 CBS vs TBS

|                           | TBS                             | CBS                             |
| ------------------------- | ------------------------------- | ------------------------------- |
| Scheduling                | EDF                             | EDF                             |
| Prioridade                | dinâmica                       | dinâmica                       |
| Bandwidth                 | \(U_s\)                         | \(Q_s/T_s\)                     |
| Precisa conhecer\(c_k\)?  | **Sim**                   | **Não da mesma forma**   |
| Controla execução real? | Não                            | **Sim**                   |
| Overrun protection        | ❌                              | ✅                              |
| Remaining budget          | não é o mecanismo central     | **mantido continuamente** |
| Deadline pode ser adiada  | à chegada segundo fórmula TBS | chegada/regras de budget        |
| Complexidade              | menor                           | maior                           |
| Overhead                  | menor                           | maior                           |
| Bandwidth isolation       | vulnerável a overrun           | **enforced**              |

---

# 1.18 Relação com Linux

O professor liga explicitamente esta matéria ao Linux.

A mensagem dada na aula foi:

> `SCHED_DEADLINE` não deve ser mentalmente entendido apenas como “EDF puro”.

Foi referido que o Linux utiliza um mecanismo evoluído relacionado com CBS/GRUB para controlar bandwidth.

As tuas notas registam esta ligação: `SCHED_DEADLINE` usa uma variante/evolução baseada no princípio CBS. notas_13_10_26

Para esta aula, basta guardar:

\[
\boxed{\text{SCHED\_DEADLINE ≠ simplesmente EDF sem controlo de runtime}}
\]

Existe também controlo de bandwidth/runtime.

O detalhe exato da implementação Linux **não foi desenvolvido suficientemente nesta aula para justificar aprofundamento agora**.

---

# 2. Explicação simples das partes difíceis

## Analogia: uma conta bancária

Pensa no CBS como uma conta bancária de CPU.

Tens:

```text
budget = €2
period = 10 dias
```

Enquanto gastas:

```text
€2 → €1.5 → €1 → €0.5 → €0
```

Chegaste a zero.

Não podes simplesmente continuar a gastar mantendo as mesmas condições.

O sistema diz:

> “Posso dar-te novo crédito, mas a tua próxima deadline vai para mais tarde.”

Isto equivale a:

\[
c_s=Q_s
\]

\[
d_s=d_s+T_s
\]

A tarefa recebe mais CPU, mas perde prioridade.

---

# 3. Correções e pontos pouco claros

### Correção 1 — cálculo das tuas notas

Tens:

> `d1 = 4 + (2/(3/20)) ... isto dá 13.333`

Não exatamente.

\[
\frac{2}{3/20}=13.333
\]

mas:

\[
d_1=4+13.333=\boxed{17.333}
\]

notas_13_10_26

### Correção 2 — “CBS desliga a task”

Nas notas aparece algo como “desliga-se a task / pomos a task IDLE”. notas_13_10_26

A formulação segura para esta matéria é:

> **o CBS impede que a tarefa continue a consumir CPU com o mesmo budget/deadline; na variante estudada, quando o budget chega a zero, replenishes o budget e postpone a deadline.**

Não memorizes simplesmente “mata/desliga a task”.

### Correção 3 — Hard CBS

O professor menciona uma variante **Hard CBS**, mas indica que **não será a variante estudada**. As tuas notas registam isso explicitamente. notas_13_10_26

Portanto:

> **Not clearly covered in the lecture.**

Não vale aprofundar para esta fase.

---

# 4. Exercício do quadro — o que tens realmente de saber fazer

A fotografia final corresponde ao exercício CBS desenvolvido na segunda gravação.

O servidor tem:

\[
U_s=25\%=0.25
\]

e, no exercício, aparece:

\[
Q_s=1
\]

Logo:

\[
T_s=\frac{Q_s}{U_s}
=\frac{1}{0.25}
=\boxed{4}
\]

Isto explica porque o professor está constantemente a deslocar deadlines em **4 unidades**.

---

## Primeira chegada

O primeiro job chega em aproximadamente:

\[
t=2.2
\]

Como é a primeira ativação, a deadline usada no exercício passa para:

\[
d_s=2.2+4
\]

\[
\boxed{d_s=6.2}
\]

---

## Chegada em \(t=7.5\)

Neste ponto:

\[
c_s=0.5
\]

e:

\[
U_s=0.25
\]

É aplicado o teste:

\[
t_k+\frac{c_s}{U_s}\le d_s
\]

Logo:

\[
7.5+\frac{0.5}{0.25}
\]

\[
=7.5+2
\]

\[
=9.5
\]

A deadline anterior já não permite isso, portanto a condição é falsa.

O professor reinicializa:

\[
c_s=Q_s=1
\]

e calcula:

\[
d_s=t_k+T_s
\]

\[
d_s=7.5+4
\]

\[
\boxed{d_s=11.5}
\]

Esta é uma das contas fundamentais do exercício.

---

## Quando o budget posteriormente chega a zero

Aqui há uma regra diferente.

Não usamos:

\[
d_s=t_k+T_s
\]

Usamos:

\[
\boxed{d_s=d_s+T_s}
\]

Ou seja, se:

\[
d_s=11.5
\]

então:

\[
d_s=11.5+4
\]

\[
\boxed{d_s=15.5}
\]

e simultaneamente:

\[
\boxed{c_s=1}
\]

⚠️ Esta distinção foi enfatizada pelo professor porque é fácil confundir:

```text
nova ativação / teste falha:
ds = tk + Ts

budget esgota:
ds = ds + Ts
```

---

## Terceiro job: \(t=10.2\)

A fotografia do quadro mostra precisamente esta conta:

\[
t_k+\frac{c_s}{U_s}\le d_s
\]

Com:

\[
t_k=10.2
\]

\[
c_s=1
\]

\[
U_s=0.25
\]

temos:

\[
10.2+\frac{1}{0.25}
\]

\[
=10.2+4
\]

\[
=\boxed{14.2}
\]

A deadline atual é:

\[
d_s=15.5
\]

Então:

\[
\boxed{14.2\le15.5}
\]

é verdadeiro.

Logo:

\[
\boxed{\text{mantém-se }d_s}
\]

e não é necessário resetar a deadline/budget devido à chegada.

### Este é o raciocínio que tens de conseguir reproduzir.

Não decorar o desenho inteiro.

---

# 5. 📓 Resumo para escrever no caderno — ~30 min

## Servidores

Usados para executar workload **aperiódico/irregular** sem destruir a escalonabilidade das tarefas periódicas.

Reservam uma bandwidth do processador.

---

## EDF

Prioridade dinâmica.

\[
\boxed{\text{earliest absolute deadline → highest priority}}
\]

Não existe necessariamente uma task sempre mais prioritária.

---

## Total Bandwidth Server — TBS

Servidor dinâmico para EDF.

Bandwidth:

\[
U_s
\]

Para cada novo job \(k\):

\[
\boxed{d_k=\max(t_k,d_{k-1})+\frac{c_k}{U_s}}
\]

- \(t_k\): arrival time
- \(c_k\): execution time
- \(d_{k-1}\): previous server deadline
- \(U_s\): server utilization

Depois EDF escalona normalmente.

### Schedulability

\[
\boxed{U_p+U_s\le1}
\]

### Vantagens

- simples;
- deadline calculada apenas à chegada;
- bom average response time.

### Problemas

1. é necessário conhecer \(c_k\) **antes da execução**;
2. não controla **overruns**.

Overrun:

\[
C_{actual}>C_{expected}
\]

Pode provocar interferência excessiva nas tarefas periódicas.

---

## Constant Bandwidth Server — CBS

Resolve os problemas do TBS através de **capacity/budget management**.

Parâmetros:

\[
(Q_s,T_s)
\]

Bandwidth:

\[
\boxed{U_s=\frac{Q_s}{T_s}}
\]

Mantém:

- deadline atual \(d_s\);
- remaining capacity \(c_s\).

---

### Novo job com servidor idle

Testar:

\[
\boxed{t_k+\frac{c_s}{U_s}\le d_s^{current}}
\]

Se verdadeiro:

\[
\boxed{\text{keep }d_s,c_s}
\]

Se falso:

\[
\boxed{d_s=t_k+T_s}
\]

\[
\boxed{c_s=Q_s}
\]

---

### Enquanto executa

Budget diminui:

\[
c_s\downarrow
\]

Quando:

\[
c_s=0
\]

então:

\[
\boxed{d_s=d_s+T_s}
\]

\[
\boxed{c_s=Q_s}
\]

Deadline aumenta ⇒ prioridade EDF diminui.

Isto controla overruns.

---

## TBS vs CBS

```text
TBS
needs future execution estimate
        ↓
ck
        ↓
calculate deadline
        ↓
no overrun control
```

```text
CBS
tracks actual execution
        ↓
remaining budget cs
        ↓
budget exhausted
        ↓
postpone deadline
        ↓
bandwidth isolation
```

CBS:

- maior complexidade;
- maior overhead;
- maiores garantias.

---

## Exercício da aula

\[
U_s=0.25,\qquad Q_s=1
\]

Logo:

\[
T_s=\frac{1}{0.25}=4
\]

Primeiro job:

\[
t=2.2
\]

\[
d_s=2.2+4=\boxed{6.2}
\]

Nova chegada:

\[
t=7.5,\quad c_s=0.5
\]

\[
7.5+\frac{0.5}{0.25}=9.5
\]

Condição falsa ⇒

\[
d_s=7.5+4=\boxed{11.5}
\]

\[
c_s=1
\]

Budget esgota ⇒

\[
d_s=11.5+4=\boxed{15.5}
\]

\[
c_s=1
\]

Nova chegada:

\[
t=10.2
\]

\[
10.2+\frac{1}{0.25}=14.2
\]

\[
14.2\le15.5
\]

Condição verdadeira ⇒ **mantém deadline 15.5**.

---

# 6. Core concepts — só os difíceis

## ① Porque aparece \(c/U_s\) no TBS?

Se tens direito a 25% da CPU:

\[
U_s=0.25
\]

e precisas de:

\[
c=1
\]

para receber 1 unidade de CPU respeitando 25% de bandwidth precisas de uma janela equivalente a:

\[
\frac{1}{0.25}=4
\]

Daí:

\[
\frac{c}{U_s}
\]

---

## ② Porque adiar a deadline reduz prioridade?

EDF escolhe a menor deadline.

Antes:

\[
d_s=11.5
\]

Depois:

\[
d_s=15.5
\]

Se outra task tiver:

\[
d=12
\]

antes:

\[
11.5<12
\]

server executaria primeiro.

Depois:

\[
12<15.5
\]

a outra task executa primeiro.

Portanto:

\[
\boxed{\text{postpone deadline} \Rightarrow \text{lower priority}}
\]

---

## ③ Porque CBS resolve overrun?

Porque não acredita apenas numa estimativa inicial.

Ele mede consumo real:

\[
Q_s\rightarrow0
\]

Quando acaba o budget, altera a deadline antes de continuar.

Portanto a tarefa não consegue monopolizar CPU mantendo artificialmente uma deadline urgente.

---

## ④ \(t_k+T_s\) vs \(d_s+T_s\)

Este é provavelmente o ponto mais fácil de errar no exercício.

Quando chega um job e o teste CBS falha:

\[
\boxed{d_s=t_k+T_s}
\]

Quando **budget chega a zero**:

\[
\boxed{d_s=d_s+T_s}
\]

São eventos diferentes.

---

# 7. Essential Exam Questions — 5

### Q1 — Conceptual

**Porque é que TBS precisa conhecer \(c_k\) antes da execução?**

**Resposta:** porque \(c_k\) entra diretamente em:

\[
d_k=\max(t_k,d_{k-1})+\frac{c_k}{U_s}
\]

Sem \(c_k\), não consegue calcular a deadline.

---

### Q2 — Conceptual

**Qual é o problema do TBS que motiva CBS?**

**Resposta:** TBS não controla overruns. Se o job executar mais que o \(c_k\) declarado, pode consumir CPU adicional mantendo a deadline/prioridade calculada originalmente.

---

### Q3 — Prática

TBS com:

\[
U_s=0.25,\quad t_k=5,\quad d_{k-1}=4,\quad c_k=2
\]

Calcula \(d_k\).

**Resposta:**

\[
d_k=\max(5,4)+\frac2{0.25}
\]

\[
=5+8
\]

\[
\boxed{13}
\]

---

### Q4 — Prática

CBS:

\[
Q_s=2,\quad T_s=8,\quad d_s=10
\]

O budget esgota.

Qual a nova deadline e budget?

**Resposta:**

\[
d_s=10+8=\boxed{18}
\]

\[
c_s=Q_s=\boxed2
\]

Budget exhaustion ⇒ replenish budget + postpone deadline.

---

### Q5 — Multiple choice

No CBS, quando o budget chega a zero, qual operação corresponde ao algoritmo estudado?

**A)** manter deadline e aumentar prioridade
**B)** \(d_s=t_k\)
**C)** \(d_s=d_s+T_s,\ c_s=Q_s\)
**D)** terminar permanentemente a task

**Resposta: C.**

É o mecanismo usado para repor budget sem permitir que o servidor exceda continuamente a bandwidth reservada.

---

# 8. Common Pitfalls

1. **Confundir deadline relativa com absoluta.** EDF compara deadlines absolutas; a deadline do servidor é gerida dinamicamente.
2. **Esquecer o `max` no TBS.**

\[
d_k=\max(t_k,d_{k-1})+\frac{c_k}{U_s}
\]

e não simplesmente \(t_k+c_k/U_s\).

3. **Confundir as duas atualizações CBS:**

\[
\boxed{d_s=t_k+T_s}
\]

quando o teste de chegada falha, versus

\[
\boxed{d_s=d_s+T_s}
\]

quando o budget esgota.

4. **Pensar que CBS dá mais CPU gratuitamente quando replenishes.** Recebe novo budget, mas a deadline é empurrada para a frente; logo, a prioridade EDF é reduzida.
5. **Decorar o cronograma do quadro em vez das regras.** O exercício torna-se muito mais simples se, em cada evento, perguntares apenas: **chegou job? budget chegou a zero? qual é a deadline absoluta de cada entidade?**

## 📓 Guardar no caderno

A distinção mais importante desta aula é:

\[
\boxed{\text{TBS controla bandwidth através da deadline calculada com }c_k}
\]

\[
\boxed{\text{CBS controla bandwidth através de deadline + budget real}}
\]

É essa mudança que permite ao CBS lidar com **execution-time uncertainty e overruns**.
