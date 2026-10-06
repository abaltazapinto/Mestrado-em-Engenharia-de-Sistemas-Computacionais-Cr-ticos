
# AULA TEÓRICA — RTESY

## Earliest Deadline First, Dynamic Scheduling, Jitter/Offsets e Hierarchical Scheduling

**Fonte principal:** SRT da aula de 06/10/2026 (~47 min).
**Slides:** `RTESY 3` usados apenas para confirmar terminologia, fórmulas, tabelas e figuras quando a transcrição automática ficou corrompida.
**Notas pessoais:** usadas apenas na secção de correção.

A transcrição tem vários erros de ASR — por exemplo, `"ADF"` → **EDF**, `"First Care Ferser"` → **First Come First Serve**, `"List of Slide First"` → **Least Slack/Laxity First**, e várias ocorrências de `"scheduler"` foram transcritas como palavras sem sentido. Corrigi estes termos quando os slides tornam a intenção inequívoca.

---

# 1. Reconstrução da aula

## 1.1 Transição: preempção vs. não-preempção

Nos primeiros minutos, o professor ainda está a concluir o tópico anterior.

A ideia claramente percetível é:

- **preempção aumenta a complexidade**;
- sistemas não-preemptivos são conceptualmente mais simples;
- essa simplicidade pode ser obtida à custa de uma utilização mais limitada do processador;
- depois disto, a aula muda para **scheduling com prioridades dinâmicas**.

Os valores percentuais concretos ditos no início ficaram muito corrompidos na SRT.

**Not clearly covered in the lecture:** o valor exato referido nesses primeiros segundos.

---

## 1.2 Prioridades dinâmicas

≈ `02:00–05:20`

Até aqui tinham sido consideradas sobretudo **prioridades fixas**.

Numa abordagem dinâmica:

> a prioridade de uma tarefa/job é determinada ou atualizada **durante a execução**.

Portanto, uma tarefa não possui necessariamente a mesma prioridade durante toda a vida do sistema.

### Vantagem principal

O professor salienta que isto torna o sistema mais **adaptável** e permite obter uma utilização do processador superior à que se consegue garantir através do teste simples de prioridades fixas.

### Desvantagens

É necessário:

- calcular/atualizar prioridades em runtime;
- reorganizar a ready queue;
- suportar maior overhead do scheduler.

Há ainda uma diferença fundamental perante uma **sobrecarga**.

Com prioridades fixas, é possível prever qual a classe de tarefas que tende a sofrer primeiro: as de prioridade inferior.

Com prioridades dinâmicas isso é menos previsível, porque:

> a prioridade no instante da sobrecarga depende do estado corrente do sistema.

O professor enfatiza bastante este problema para sistemas críticos.

⚠️ A afirmação oral de que praticamente "ninguém usa EDF em sistemas críticos" é mais absoluta do que os próprios slides. O ponto técnico suportado pela aula é: **o comportamento de EDF durante overload é menos previsível quanto a qual tarefa falhará o deadline.**

---

## 1.3 Exemplos de algoritmos com prioridade dinâmica

≈ `05:20–07:10`

Foram apresentados três exemplos.

### EDF — Earliest Deadline First

Escolhe o job com o **deadline absoluto mais próximo**.

É o algoritmo em que a aula se concentra.

### LLF / LSF — Least Laxity First / Least Slack First

Não considera apenas quando termina o deadline.

Considera também quanto trabalho falta fazer.

Intuição dada na aula:

> uma tarefa pode ter um deadline mais distante, mas precisar de muito mais CPU; nesse caso pode ter menos "folga".

De forma intuitiva:

\[
Slack \approx tempo\ até\ deadline - execução\ restante
\]

Não foi desenvolvido matematicamente em profundidade.

### FCFS — First Come First Serve

Executa primeiro quem está há mais tempo à espera.

O professor interpreta isto também como prioridade dinâmica porque o "peso" de uma tarefa aumenta à medida que esta avança na fila.

---

# 1.4 EDF — regra fundamental

≈ `07:10–13:00`

Esta é provavelmente **a parte mais importante da aula**.

Em EDF:

> entre todos os jobs ready, executa aquele cujo **deadline absoluto é mais próximo**.

Não basta olhar para o `D` da tabela.

É obrigatório considerar também **quando o job chegou**.

---

## Relative deadline vs. absolute deadline

O professor insiste várias vezes nesta diferença.

Se:

- `r` = instante de release/arrival;
- `D` = relative deadline;

então:

\[
d_{abs}=r+D
\]

### Exemplo simples

Job A:

\[
r_A=0,\qquad D_A=10
\]

Logo:

\[
d_A=10
\]

Job B:

\[
r_B=6,\qquad D_B=5
\]

Logo:

\[
d_B=11
\]

Apesar de B ter:

\[
D_B < D_A
\]

A continua a ser mais urgente porque:

\[
10 < 11
\]

### Regra mental

**EDF não compara `D`.**

EDF compara:

\[
\boxed{r+D}
\]

Isto explica porque o professor diz:

> **"o instante de chegada é fundamental."**

---

# 1.5 O scheduler em EDF

≈ `12:00–20:40`

Quando um job chega, o scheduler tem de:

1. obter o instante atual/release;
2. acrescentar o relative deadline;
3. guardar o **absolute deadline**;
4. ordenar/escolher os ready jobs com base nesse valor.

Em EDF preemptivo, sempre que acontece um evento relevante, o scheduler pode ter de tomar uma nova decisão.

Na aula foram particularmente considerados:

- chegada/release de um job;
- conclusão de um job.

Se chega uma nova tarefa cujo deadline absoluto é anterior ao da tarefa que está a executar:

> **há preempção.**

Caso contrário, a tarefa corrente continua.

---

# 1.6 Exemplo Control / Alarm / Logger

≈ `13:10–22:50`

O professor trabalha um exemplo com três tarefas.

Uma das tabelas contém aproximadamente:

| Task    |  C |   T |   D | Arrival |
| ------- | -: | --: | --: | ------: |
| Control | 20 |  60 |  40 |       0 |
| Alarm   |  5 |  70 |  20 |      25 |
| Logger  | 50 | 100 | 100 |       5 |

O segundo slide altera ligeiramente o período do **Alarm para 65 ms**.

Isto é deliberado: serve para mostrar que uma pequena alteração temporal pode mudar quem preempta quem.

### Início do exemplo

Em `t=0`:

- Control chega;
- absolute deadline = `0 + 40 = 40`.

Logo Control começa.

Em `t=5`:

- Logger chega;
- absolute deadline = `5 + 100 = 105`.

Control continua porque:

\[
40 < 105
\]

Em `t=20`:

- Control termina;
- Logger pode executar.

Em `t=25`:

- Alarm chega;
- absolute deadline:

\[
25+20=45
\]

Logger tinha:

\[
105
\]

Portanto:

\[
45<105
\]

e **Alarm preempta Logger**.

Isto demonstra exatamente o mecanismo do EDF.

---

## Prioridade realmente muda

Mais tarde, o mesmo par de tarefas pode ter a relação oposta.

Uma tarefa que anteriormente preemptou outra pode, numa release futura, deixar de o fazer.

Não existe portanto:

> "Alarm tem sempre prioridade superior a Logger."

Existe:

> "neste instante, este job de Alarm tem um absolute deadline anterior ao job de Logger."

Esta é a mudança mental essencial entre **Fixed Priority Scheduling** e **EDF**.

---

# 1.7 EDF preemptivo vs. não-preemptivo

≈ `22:45–27:00`

O professor refere também EDF **não-preemptivo**.

A regra de escolha continua relacionada com deadlines.

A diferença é:

> depois de uma tarefa começar, outra tarefa que chegue não pode interrompê-la.

Isto introduz **blocking**.

A análise de escalonabilidade e de response time torna-se significativamente mais complicada.

O professor diz explicitamente que a análise mais avançada de response time em EDF:

> **fica fora do âmbito da disciplina.**

Portanto:

**Not clearly covered in the lecture:** análise matemática completa de response time em EDF.

---

# 1.8 Testes de escalonabilidade

≈ `23:00–26:00`

Esta é outra parte central.

## Fixed Priority, preemptivo, `D = T`

Utilização:

\[
U=\sum_i \frac{C_i}{T_i}
\]

Se:

\[
U>1
\]

é impossível escalonar num único CPU.

O teste suficiente de Liu & Layland apresentado é:

\[
U\leq n(2^{1/n}-1)
\]

→ **schedulable garantido**.

Se estiver entre esse limite e `1`:

> o teste de utilização é **inconclusivo**.

Não significa automaticamente que o sistema seja impossível.

---

# EDF preemptivo com `D = T`

O teste apresentado na aula é muito mais simples:

\[
\boxed{U=\sum_i\frac{C_i}{T_i}}
\]

Se:

\[
U>1
\]

→ não schedulable.

Se:

\[
U\leq1
\]

→ schedulable.

Isto significa que EDF pode garantir utilização até:

\[
100\%
\]

nas condições apresentadas.

---

# EDF com `D < T`

A aula introduz **density**:

\[
U^*=\sum_i\frac{C_i}{D_i}
\]

Segundo o teste apresentado:

\[
U^*\leq1
\]

→ schedulable.

\[
U^*>1
\]

→ não schedulable.

⚠️ A SRT troca momentaneamente `>` e `<` porque a transcrição ficou confusa. O professor corrige-se logo a seguir e o slide confirma a versão acima.

---

# 1.9 Exemplo dos 84%

O professor recupera:

| Task | C | T=D |  C/T |
| ---- | -: | --: | ---: |
| τ1  | 2 |  10 | 0.20 |
| τ2  | 9 |  15 | 0.60 |
| τ3  | 1 |  25 | 0.04 |

Logo:

\[
U=0.20+0.60+0.04=0.84
\]

Para três tarefas, o bound de Fixed Priority é aproximadamente:

\[
3(2^{1/3}-1)\approx0.78
\]

Então:

\[
0.84>0.78
\]

O teste FPS **não consegue concluir**.

Mas:

\[
0.84<1
\]

Logo, nas condições EDF ensinadas:

> **EDF garante que o task set é schedulable.**

Isto foi usado pelo professor para demonstrar a vantagem de utilização do EDF.

---

# 1.10 Exercício de tracing

≈ `27:00–41:00`

Foi pedido traçar a execução durante 100 ms de:

| Task |  C | T=D | Arrival |
| ---- | -: | --: | ------: |
| τ1  | 10 |  30 |       0 |
| τ2  | 10 |  40 |       0 |
| τ3  | 21 |  60 |       0 |

comparando **FPS e EDF**.

O professor também discute empates de deadlines.

Quando dois jobs têm o mesmo deadline, a aula indica como critério típico:

- manter a tarefa já em execução, ou
- entre tarefas novas, usar ordem de chegada/posição na fila.

O professor recomenda evitar ambiguidades deste tipo nos testes sempre que possível.

Grande parte deste período corresponde ao tempo dado aos alunos para resolverem o exercício, e a SRT contém grandes lacunas.

**Not clearly covered in the lecture:** uma solução oral completa e inequivocamente transcrita do diagrama dos 100 ms.

---

# 1.11 SimSo

≈ `41:20`

O professor mostra **SimSo** como ferramenta para verificar os diagramas de scheduling.

As tuas notas registaram também esse link. notas_6_10_26

O slide refere configurações para:

- FPS;
- EDF;
- FPS com offset.

A ideia pedagógica é importante:

> primeiro raciocinar manualmente; depois usar o simulador para verificar.

---

# 1.12 Offset e jitter

≈ `41:40–44:05`

Uma tarefa pode ser **periodicamente ativada**, mas a sua execução efetiva não começar sempre com o mesmo atraso.

Por exemplo:

```text
release       release       release
  |             |             |
  |---2 ms---> execução
                |------5 ms------> execução
                              |-> execução
```

Embora os releases sejam periódicos, a execução observada pode não o ser perfeitamente.

Essa variação é associada ao **jitter**.

As tuas notas registam a ideia geral de jitter como variação entre instantes esperados e reais. notas_6_10_26

O professor salienta:

> mais jitter → comportamento temporal menos regular.

---

## Para que servem offsets?

Pode ser introduzido deliberadamente um atraso:

\[
Offset
\]

antes da ativação/execução de uma tarefa.

Por exemplo, em vez de:

```text
τ1  ↑
τ2  ↑
τ3  ↑
```

todas tentarem trabalhar simultaneamente, pode-se fazer:

```text
τ1  ↑
τ2       ↑
τ3            ↑
```

Isto permite distribuir a carga no tempo.

Na aula, os offsets são apresentados também como uma forma de tornar o comportamento temporal mais regular e reduzir jitter em certas situações.

---

# 1.13 Hierarchical Scheduling

≈ `44:05–46:55`

Último tópico da aula.

Um sistema não tem necessariamente de utilizar **um único algoritmo de scheduling**.

Pode combinar vários.

O professor chama a isto **hierarchical scheduling**.

### Primeiro nível

Por exemplo:

```text
priority 10
priority 9
priority 8
...
```

O scheduler escolhe primeiro a maior prioridade fixa disponível.

### Segundo nível

Se houver várias tarefas **no mesmo nível**, pode existir outro algoritmo.

Por exemplo:

```text
Priority 10 → EDF entre as tarefas deste nível
Priority 9  → Fixed Priority
Priority 8  → Round Robin
```

Assim temos múltiplas decisões de scheduling.

Foram mencionados:

- Linux;
- Zephyr;
- Ada.

### Zephyr

A aula salienta que Zephyr permite combinar políticas e usar EDF como critério dentro de níveis de prioridade.

### Linux

Segundo a explicação dada na aula, existe uma classe baseada em deadlines acima das classes real-time de prioridades fixas.

O ponto a memorizar agora não é a implementação completa do kernel.

É:

\[
\boxed{\text{um sistema pode combinar políticas de scheduling}}
\]

A tua nota `"escalamento hierárquico ou prioridades dinâmicas"` mistura dois conceitos diferentes. notas_6_10_26

---

# 2. Explicação simples das partes difíceis

## A. Porque é que EDF é "dynamic priority"?

Imagina três entregas:

```text
Pacote A → entregar às 15:00
Pacote B → entregar às 14:00
Pacote C → entregar às 17:00
```

Agora B é o mais urgente.

Depois de B sair, A passa a ser o mais urgente.

Não existe:

```text
A = prioridade 1 para sempre
B = prioridade 2 para sempre
```

A prioridade surge do **deadline atual**.

---

## B. Relative deadline vs. absolute deadline

Isto é o conceito que mais facilmente dá erro.

`D=20 ms` não significa:

> termina no instante 20.

Significa:

> termina no máximo 20 ms **depois de chegar**.

Se chega em:

\[
r=50
\]

então:

\[
d_{abs}=50+20=70
\]

EDF compara **70**, não compara simplesmente **20**.

---

## C. Porque EDF pode chegar aos 100%?

Fixed Priority tem uma ordem escolhida antecipadamente.

Essa ordem pode não ser ideal em todos os instantes.

EDF pergunta continuamente:

> **qual é realmente o job mais urgente agora?**

Isso permite aproveitar melhor o CPU nas condições estudadas.

---

## D. Jitter

Uma tarefa periódica deveria idealmente parecer:

```text
|----10----|----10----|----10----|
X          X          X          X
```

Com interferência pode parecer:

```text
X            X       X             X
```

O período nominal continua igual, mas o comportamento observado varia.

Essa variação temporal é o que interessa aqui quando se fala de **jitter**.

---

## E. Hierarchical scheduling

É simplesmente:

> **scheduler dentro de scheduler.**

Primeiro:

```text
qual o nível de prioridade?
```

Depois:

```text
entre as tarefas desse nível, qual executa?
```

Essa segunda decisão pode ser EDF, Round Robin, etc.

---

# 3. Problemas / correções nas notas e materiais

As tuas definições:

> `T = período`
> `D = deadline`
> `C = tempo de execução`

estão corretas para a notação usada na aula. notas_6_10_26

Mas faltou a variável/conceito que provavelmente é **mais importante nesta aula**:

\[
\boxed{d_{abs}=r+D}
\]

onde `r` é o release/arrival.

### Correções importantes

| Nota/material                                            | Correção                                                                                                                                 |
| -------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| `"vamos falar de EDF"`                                 | Certo, é o tópico central.                                                                                                               |
| `T, D, C`                                              | Certo, mas falta**arrival/release/offset e absolute deadline**.                                                                      |
| `"quanto mais jitter pior a qualidade"`                | Aceitável no contexto da aula, mas melhor escrever**maior jitter = menor regularidade/previsibilidade temporal**.                   |
| `"escalamento hierárquico ou prioridades dinâmicas"` | **Não são sinónimos.** Hierarchical scheduling pode combinar fixed priority + EDF/RR.                                             |
| `"Zephyr..."`                                          | Muito incompleto: Zephyr foi dado como exemplo de combinação hierárquica de políticas.                                                 |
| Slide Alarm`T=70` e depois `T=65`                    | Não parece erro: é uma variante deliberada para alterar o comportamento do exemplo.                                                      |
| SRT diz por momentos`density > 1 schedulable`          | Erro/transcrição/confusão momentânea. A conclusão da aula é**>1 não schedulable; ≤1 schedulable**, segundo o teste mostrado. |

Há ainda uma formulação oral demasiado absoluta sobre EDF não ser usado em sistemas críticos. O conceito que deve ficar para estudo é mais preciso:

> **EDF tem excelente utilização, mas overload torna menos previsível qual tarefa sofrerá deadline miss.**

---

# 4. 📓 Resumo para escrever no caderno — ~30 min

## Dynamic Scheduling

- prioridade pode mudar durante runtime
- decisão baseada no estado atual do sistema
- vantagens:
  - flexível
  - adapta-se a períodos diferentes
  - maior utilização possível
- desvantagens:
  - overhead
  - mais complexidade
  - overload menos previsível

### Exemplos

- **EDF** → menor absolute deadline
- **LLF/LSF** → menor slack/laxity
- **FCFS** → maior waiting time

---

## EDF — Earliest Deadline First

Regra:

\[
\boxed{\text{executar o ready job com menor absolute deadline}}
\]

Relative deadline:

\[
D
\]

Release:

\[
r
\]

Absolute deadline:

\[
\boxed{d=r+D}
\]

**EDF compara `d`, NÃO apenas `D`.**

---

## Scheduler EDF

Nova decisão quando:

- job chega/release
- job termina

Se novo job tiver:

\[
d_{new}<d_{running}
\]

→ preempta em EDF preemptivo.

Prioridades mudam ao longo do tempo.

---

## Parâmetros

\[
C=\text{execution time}
\]

\[
T=\text{period}
\]

\[
D=\text{relative deadline}
\]

\[
r=\text{release/arrival}
\]

\[
d=r+D=\text{absolute deadline}
\]

---

## Utilization

\[
U=\sum_i\frac{C_i}{T_i}
\]

### EDF, `D=T`

\[
U\leq1 \Rightarrow schedulable
\]

\[
U>1 \Rightarrow not\ schedulable
\]

### Fixed Priority

\[
U\leq n(2^{1/n}-1)
\]

→ guaranteed schedulable.

Entre esse bound e `1`:

→ **inconclusive**.

---

## EDF `D<T`

Density:

\[
U^*=\sum_i\frac{C_i}{D_i}
\]

Na regra apresentada na aula:

\[
U^*\leq1 \Rightarrow schedulable
\]

\[
U^*>1 \Rightarrow not\ schedulable
\]

---

## Exemplo

\[
U=0.20+0.60+0.04=0.84
\]

FPS, `n=3`:

\[
U_{bound}\approx0.78
\]

\[
0.84>0.78
\]

→ FPS utilization test **inconclusive**.

EDF:

\[
0.84<1
\]

→ **schedulable guaranteed**.

---

## Jitter

- tarefa pode ter activation periódica
- execução pode sofrer atrasos diferentes
- variação temporal → **jitter**
- maior jitter → menor regularidade temporal

---

## Offset

Offset = atraso deliberado da tarefa.

Usado para:

- distribuir carga;
- evitar todas as tarefas simultâneas;
- tornar comportamento mais regular;
- reduzir jitter em certos casos.

---

## Hierarchical Scheduling

Mais de uma decisão de scheduling.

Exemplo:

```text
Priority 10 → EDF
Priority 9  → EDF
Priority 8  → Round Robin
```

Primeiro:

→ escolhe prioridade.

Depois:

→ scheduler secundário decide dentro desse nível.

Exemplos mencionados:

- Linux
- Zephyr
- Ada

---

# 5. Core Concepts — só os difíceis

### 1. Absolute deadline

Não memorizes EDF como:

> "menor D".

Memoriza:

\[
\boxed{\text{EDF = menor }(release+D)}
\]

---

### 2. Dynamic priority

A tarefa não "é" prioridade alta ou baixa.

O **job atual** torna-se mais ou menos prioritário dependendo do seu absolute deadline.

---

### 3. Utilization test

Para EDF com `D=T`:

\[
U\leq1
\]

é o número-chave desta aula.

Mental model:

> CPU precisa de executar, em média, no máximo 100% da sua capacidade.

---

### 4. Offset vs. jitter

**Offset:** atraso introduzido intencionalmente.

**Jitter:** variação temporal observada.

Um offset bem escolhido pode ser usado para **reduzir variação/jitter**.

---

### 5. Hierarchical scheduling

Não significa "prioridades dinâmicas".

Significa:

\[
\boxed{\text{combinar vários níveis/políticas de scheduling}}
\]

---

# 6. Essential Exam Questions — 5

## Conceptual 1

**Pergunta:** Porque é que EDF é considerado um algoritmo de prioridade dinâmica mesmo que uma tarefa tenha sempre `D=20 ms`?

**Resposta:** Porque cada release tem um novo absolute deadline:

\[
d=r+D
\]

**Raciocínio:** Como `r` muda, `d` muda; consequentemente a posição/prioridade do job na ready queue também pode mudar.

---

## Conceptual 2

**Pergunta:** Qual é a principal desvantagem de EDF durante overload apresentada na aula?

**Resposta:** Não é facilmente previsível qual tarefa irá falhar o deadline.

**Raciocínio:** As prioridades dependem dinamicamente dos deadlines absolutos existentes naquele instante.

---

## Practical 1

Uma tarefa A está ready com:

\[
d_A=50
\]

Em `t=25` chega B com:

\[
D_B=20
\]

**Quem executa em EDF preemptivo?**

**Resposta:**

\[
d_B=25+20=45
\]

Como:

\[
45<50
\]

B preempta A.

---

## Practical 2

Em EDF preemptivo com `D=T`:

\[
\tau_1:C=25,\quad T=?
\]

\[
\tau_2:C=10,\quad T=60
\]

\[
\tau_3:C=20,\quad T=80
\]

Qual é aproximadamente o menor `T1` permitido pelo teste da aula?

**Resposta:**

\[
\frac{25}{T_1}+\frac{10}{60}+\frac{20}{80}\leq1
\]

\[
T_1\geq42.86\ ms
\]

**Raciocínio:** Basta impor `U ≤ 1`, porque `D=T`.

---

## Multiple Choice

Em EDF preemptivo, qual propriedade decide normalmente qual ready job executa?

**A)** menor período
**B)** maior execution time
**C)** menor absolute deadline
**D)** menor relative deadline

**Resposta:** **C — menor absolute deadline.**

**Raciocínio:** EDF considera o deadline real de cada job, que depende também do seu release.

---

# 7. Common Pitfalls

1. **Comparar `D` diretamente em EDF.** O correto é calcular:
   \[
   d=r+D
   \]
2. **Achar que `U > bound FPS` significa "não schedulable".** Entre o bound e `1`, o teste FPS apresentado é apenas **inconclusivo**.
3. **Dar uma prioridade permanente às tarefas em EDF.** EDF atribui a urgência aos **jobs atuais**, dinamicamente.
4. **Confundir offset com jitter.** Offset é uma deslocação intencional; jitter é uma **variação** temporal.
5. **Confundir hierarchical scheduling com dynamic scheduling.** Hierarchical scheduling combina políticas; pode incluir simultaneamente fixed priorities, EDF e Round Robin.
