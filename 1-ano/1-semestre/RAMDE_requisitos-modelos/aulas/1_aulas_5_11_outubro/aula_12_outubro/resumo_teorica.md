
# RAMDE — Aula de 12/10/2026

## Requirements Engineering → Modeling Standards / SysML

**Hierarquia usada:** `RAMDE.srt` → `ramde06.pdf / ramde07.pdf` → `notas_12_10.md`.

A aula teve essencialmente **dois grandes blocos**:

> **Parte A — Requirements:** perceber **o que o sistema deve fazer, com que qualidades e sob que restrições**, e documentar isso sem ambiguidades.
> **Parte B — Models:** representar o sistema através de **modelos formais/semiformais**, introduzindo UML, SysML, MDA, metamodelos e Papyrus.

Isto coincide com os tópicos que aparecem nas tuas notas — requisitos, validação, rastreabilidade, UML/SysML, Papyrus, metamodelos e OMG — mas algumas formulações das notas precisam de correção. notas_12_10 notas_12_10

---

# 1. Reconstruct the Lecture

## 1.1 Requirements Engineering — para que serve?

O professor começa pela ideia de que desenvolver um sistema não começa imediatamente em código.

Existe inicialmente uma **necessidade/problema no mundo real**. Essa necessidade é percebida por pessoas, comunicada e progressivamente transformada numa especificação suficientemente clara para permitir construir uma solução.

A cadeia mental da aula pode ser vista assim:

```text
Realidade
   ↓
perceção humana
   ↓
modelo mental
   ↓
comunicação
   ↓
requisitos
   ↓
modelos/especificação
   ↓
solução de engenharia
```

O problema fundamental é que cada transformação pode **perder informação ou introduzir interpretações diferentes**.

O professor dá bastante importância à relação:

```text
realidade ≠ perceção da realidade ≠ descrição da realidade
```

É precisamente aqui que entra o **Requirements Engineer**.

### Requirements Engineer

O seu trabalho não é simplesmente escrever aquilo que alguém disse.

Tem de:

- compreender aquilo que os stakeholders realmente necessitam;
- eliminar ambiguidades;
- tornar requisitos suficientemente precisos;
- estruturar a informação;
- validar os requisitos;
- gerir alterações ao longo do projeto.

A comunicação é, portanto, um problema central da Engenharia de Requisitos.

---

# 1.2 Tipos de requisitos

O professor distingue essencialmente três categorias.

### Functional requirements

Dizem **o que o sistema faz**.

Exemplo simples:

> O sistema deve permitir reiniciar uma sessão.

Representam funcionalidades ou comportamentos observáveis.

---

### Quality requirements

Dizem **quão bem o sistema deve realizar algo**.

Exemplos mencionados/discutidos:

- performance;
- availability;
- dependability;
- segurança;
- outras propriedades de qualidade.

Uma distinção importante:

```text
Functional
→ WHAT does it do?

Quality
→ HOW WELL must it do it?
```

Um sistema pode implementar corretamente uma funcionalidade e, mesmo assim, falhar um requisito de qualidade.

Por exemplo:

```text
Sistema responde ao pedido.
```

Funcionalmente pode estar correto.

Mas:

```text
Sistema deve responder em ≤ 100 ms.
```

introduz uma propriedade mensurável de performance.

O professor também usa a designação comum **non-functional requirement**, embora os slides prefiram estruturar esta categoria como *quality requirements*.

---

### Constraints

São **restrições impostas à solução ou ao desenvolvimento**.

Por exemplo:

> O sistema tem de utilizar determinado protocolo.

Aqui não estamos a especificar propriamente uma funcionalidade.

Estamos a reduzir o **solution space**:

```text
Todas as soluções possíveis
        ↓ constraint
Menos soluções possíveis
```

📓 **Guardar no caderno**

> Functional = o que faz.
> Quality = quão bem faz.
> Constraint = limita como pode ser construído/desenvolvido.

---

# 1.3 System Context

Este foi outro conceito bastante enfatizado.

Antes de especificarmos detalhadamente o sistema, precisamos saber:

> **Onde termina o meu sistema e o que existe à volta dele?**

Temos:

```text
              External system
                    |
                    |
User -------- [ SYSTEM ] -------- Other system
                    |
                    |
              Environment
```

O contexto inclui entidades externas que **interagem ou influenciam o sistema**.

Podem ser:

- pessoas;
- outros sistemas;
- organizações;
- dispositivos;
- regulamentos;
- restrições externas.

O professor refere explicitamente que coisas externas podem influenciar o sistema **mesmo sem existir uma interação computacional direta**.

Por exemplo, legislação pode condicionar o sistema.

---

## System boundary vs context boundary

Mentalmente:

```text
+---------------- Context ----------------+
|                                         |
| Actor         +-------------+           |
| ------------> |   SYSTEM    |           |
|               +-------------+           |
|                                         |
| Regulation       External System        |
+-----------------------------------------+
```

A **system boundary** separa:

```text
system | environment
```

A **context boundary** determina aquilo que ainda consideramos relevante para analisar o sistema.

Isto é importante porque não podemos modelar literalmente o mundo inteiro.

---

# 1.4 Use cases como forma de perceber o contexto

O professor relaciona contexto com **use case diagrams**.

Num use case diagram podemos ter:

```text
Actor
  |
  v
+---------------------+
|       SYSTEM        |
|                     |
|   (Use Case A)      |
|   (Use Case B)      |
|                     |
+---------------------+
```

Os **atores estão fora da fronteira do sistema**.

Os **use cases representam funcionalidades relevantes disponibilizadas pelo sistema**.

Isto permite perceber rapidamente:

- quem interage com o sistema;
- quais são as grandes funcionalidades;
- onde está a fronteira do sistema.

⚠️ Um ator não tem obrigatoriamente de ser uma pessoa.

Pode ser outro sistema.

---

# 1.5 Documentação de requisitos

Depois de percebermos o contexto e recolhermos requisitos, temos de os documentar.

O professor contrasta duas possibilidades principais:

```text
Natural language
vs.
Models / diagrams
```

A linguagem natural é fácil de utilizar e acessível aos stakeholders, mas tem um problema sério:

> **ambiguidade.**

---

# 1.6 O problema da ambiguidade

Esta é uma das mensagens mais importantes desta parte da aula.

Duas pessoas podem ler a mesma frase e produzir **interpretações diferentes**.

O professor utiliza exemplos para mostrar que uma frase aparentemente óbvia pode deixar perguntas sem resposta.

Exemplo conceptual:

> O sistema deve oferecer bebidas alcoólicas a pessoas com mais de 20 anos.

Imediatamente surgem questões:

```text
20 anos conta?
> 20 ?
>= 20 ?
```

O problema não é programação.

O problema existe **antes de programarmos**.

Se o requisito permitir duas interpretações:

```text
Stakeholder → interpretação A
Developer   → interpretação B
```

podemos implementar perfeitamente a interpretação B e mesmo assim construir **o sistema errado**.

---

# 1.7 Técnicas/templates para escrever requisitos

O professor refere a existência de técnicas estruturadas/templates para escrever requisitos de maneira mais clara.

A ideia não é transformar linguagem natural numa linguagem matemática, mas **reduzir liberdade linguística**.

Em vez de:

> O sistema deverá normalmente fazer X quando necessário.

pretende-se uma estrutura que force a esclarecer:

```text
Quando?
Em que condições?
Quem?
O que deve acontecer?
Qual o resultado?
```

A transcrição nesta zona está particularmente degradada nos nomes das técnicas/autores.

**Not clearly covered in the lecture/transcription:** não é seguro reconstruir os nomes exatos de todos os templates apenas a partir do SRT.

A mensagem conceptual, contudo, é clara:

> **Structured natural language → menor ambiguidade.**

---

# 1.8 Model-based requirements

Outra alternativa é representar parte da especificação através de **modelos**.

O professor introduz UML como uma linguagem muito utilizada para modelação de software.

Os modelos permitem representar diferentes perspetivas.

Por exemplo:

```text
Structural perspective
→ estrutura do sistema

Functional perspective
→ funcionalidades

Behavioural perspective
→ comportamento
```

São referidos diagramas como:

- use case;
- class;
- activity;
- state machine.

Não é necessário nesta fase decorar todos.

O ponto fundamental é:

> **Um único diagrama não representa necessariamente tudo o que interessa sobre o sistema.**

Cada modelo oferece uma determinada **view/perspective**.

---

# 1.9 UML

O professor apresenta UML como uma linguagem de modelação bastante extensa.

É importante não pensar:

> UML = desenhar umas caixas.

UML possui um **metamodelo** que define formalmente os conceitos existentes na linguagem e as relações entre eles.

O professor enfatiza mesmo a dimensão/complexidade desse metamodelo.

Portanto:

```text
UML diagram
     ↓ conforms to
UML metamodel
```

Um *Class*, *Association*, *UseCase*, etc. não são simplesmente símbolos inventados pela ferramenta.

São conceitos definidos pela linguagem.

---

# 1.10 Validation of requirements

Outro ponto explícito da aula:

> **Os requisitos têm de ser validados.**

A pergunta essencial é:

> Estamos a especificar aquilo que realmente é necessário?

Não basta o requisito estar bem escrito.

Podemos ter:

```text
precise requirement
+
wrong stakeholder need
=
wrong system
```

A validação procura detetar problemas antes de estes chegarem à implementação.

Isto é especialmente importante porque corrigir um problema tarde no desenvolvimento tende a ser muito mais caro.

---

# 1.11 Requirements Management e traceability

O professor termina esta parte abordando gestão dos requisitos e **rastreabilidade**.

As tuas notas captaram precisamente esta palavra como ponto importante. notas_12_10

Um requisito não deve ficar isolado.

Idealmente conseguimos relacioná-lo com outros artefactos:

```text
Stakeholder need
      ↓
Requirement
      ↓
System element / model
      ↓
Implementation
      ↓
Test
```

Isto permite responder, por exemplo:

> Porque existe este componente?

ou:

> Que testes verificam este requisito?

ou ainda:

> Se alterar este requisito, que partes do sistema podem ser afetadas?

Essa capacidade é **traceability**.

📓 **Guardar no caderno**

> Traceability = conseguir seguir as relações entre requisitos e os restantes artefactos do ciclo de desenvolvimento.

---

# 1.12 Mudança de tema — Modeling Standards

Neste ponto o professor muda de apresentação — algo que também registaste nas notas. notas_12_10

Começa então:

## Model-Driven Engineering / Model-Driven Architecture

A ideia passa a ser:

> E se os **modelos forem artefactos centrais do desenvolvimento**, em vez de simples desenhos auxiliares?

Mentalmente:

```text
Traditional-ish
Requirements → Code

Model-driven
Requirements → Models → Models → Implementation
```

O professor salienta, contudo, que na prática muita coisa continua a exigir intervenção manual.

A tua nota:

> “baseio-me nos modelos mas muita coisa é feita manualmente”

está coerente com a explicação da aula. notas_12_10

---

# 1.13 OMG

Surge então a **Object Management Group (OMG)**.

É apresentada como organização responsável/promotora de vários standards de modelação utilizados neste ecossistema.

Entre os standards mencionados aparecem:

- UML;
- MOF;
- XMI;
- QVT;
- SysML.

---

# 1.14 MDA — níveis de abstração

A apresentação introduz **Model-Driven Architecture (MDA)**.

O princípio importante é separar aquilo que o sistema faz das tecnologias concretas utilizadas.

Existem três níveis apresentados nos slides:

### CIM — Computation Independent Model

Muito abstrato.

Foca:

- necessidades;
- requisitos;
- negócio;

sem decidir detalhes computacionais.

```text
WHAT is needed?
```

---

### PIM — Platform Independent Model

Já descreve estrutura/comportamento computacional, mas permanece independente de uma plataforma concreta.

```text
HOW does the system behave?
without choosing the final technology
```

---

### PSM — Platform Specific Model

Introduz decisões específicas da plataforma.

```text
How will this be realized
ON THIS PLATFORM?
```

Mental model:

```text
CIM
 ↓
PIM
 ↓
PSM
 ↓
Code
```

Quanto mais descemos:

```text
abstraction ↓
implementation detail ↑
```

---

# 1.15 Model transformations

A consequência natural é poder transformar modelos.

Por exemplo:

```text
PIM
 ↓ model-to-model transformation
PSM
 ↓ model-to-code transformation
Code
```

Aqui aparece **QVT** associado às transformações entre modelos.

⚠️ A tua nota diz:

> “QVT é uma linguagem de modelação”

Isso está **incorreto**. notas_12_10

Correção:

> **QVT (Queries/Views/Transformations) é um standard/linguagem para transformações entre modelos**, não uma linguagem de modelação geral como UML/SysML.

---

# 1.16 Metamodel — conceito central

Este é provavelmente o conceito mais abstrato da segunda metade.

Um **modelo** representa algo.

Um **metamodelo** define os conceitos que podem existir nesse modelo.

Exemplo intuitivo:

```text
UML metamodel
defines:
Class
Attribute
Association
UseCase
...

        ↓ conforms to

My UML model
Car
Engine
Driver
...
```

Analogia simples:

```text
Grammar of Portuguese
        ↓
Portuguese sentence
```

é semelhante a:

```text
Metamodel
   ↓
Model
```

O professor mostra inclusivamente a implementação/representação do metamodelo UML no Eclipse.

A tua anotação “relações conceitos metamodelos, eclipse, implementação do modelo” está, portanto, no caminho correto. notas_12_10

---

# 1.17 MOF

Nos slides aparece **MOF — Meta Object Facility**.

A ideia relevante para primeiro contacto é:

```text
MOF
 ↓ defines metamodeling concepts
UML metamodel
 ↓ defines UML concepts
UML model
 ↓ represents
System
```

Não vale a pena aprofundar agora os vários níveis M0/M1/M2/M3 se ainda estás em primeiro contacto.

O professor queria sobretudo que distinguissem:

> **model vs metamodel**

---

# 1.18 UML → SysML

Depois passa para **SysML**.

A diferença intuitiva:

```text
UML
→ principalmente software

SysML
→ systems engineering
```

Um sistema de engenharia pode conter:

```text
software
hardware
mechanics
people
interfaces
requirements
```

Logo, SysML tenta permitir modelar o **sistema como um todo**, não apenas o software.

---

# 1.19 SysML 1.x e UML

O professor explica que **SysML 1.x foi construído a partir/extensão de UML**, usando mecanismos como UML Profiles/stereotypes.

Isto explica porque vários diagramas/conceitos são semelhantes.

Por exemplo, SysML possui conceitos específicos de systems engineering como:

- blocks;
- requirements;
- relações associadas aos requisitos;
- diagramas próprios/adaptados.

O objetivo não é decorar hoje todos os diagramas.

O essencial é:

```text
UML → software modeling

SysML → systems engineering / MBSE
```

---

# 1.20 SysML v2 e KerML

Perto do fim aparece a evolução para **SysML v2**.

Aqui existe uma alteração importante.

A tua nota:

> “kernel model language é tipo superclasses”

é apenas uma aproximação muito grosseira. notas_12_10

O professor apresenta **KerML — Kernel Modeling Language** como uma linguagem/base fundamental sobre a qual SysML v2 é construído.

Mentalmente, para já:

```text
KerML
   ↓ foundation
SysML v2
```

Não precisas ainda de compreender internamente KerML.

**Not clearly covered in the lecture:** detalhes formais da semântica de KerML.

---

# 1.21 Papyrus

Finalmente aparece a ferramenta prática.

**Eclipse Papyrus** é apresentada como ferramenta open-source para trabalhar com estes modelos.

Importante distinguir:

```text
SysML = modeling language

Papyrus = modeling tool
```

Da mesma maneira:

```text
C = language
VS Code = tool/editor
```

O professor comenta versões/compatibilidade e utilização do executável.

Isto aparece também claramente nas tuas notas. notas_12_10 notas_12_10

---

# 2. Difficult Parts — explicação simples

Há uma ligação que torna praticamente toda a aula mais fácil:

```text
NEED
 ↓
REQUIREMENT
 ↓
MODEL
 ↓
IMPLEMENTATION
 ↓
VALIDATION / TEST
```

### Requirement vs model

**Requirement:** diz o que queremos/necessitamos.

> “O sistema deve manter a temperatura entre X e Y.”

**Model:** cria uma representação estruturada do sistema que satisfará esses requisitos.

> sensores → controller → actuator → environment

---

### Context

Imagina desenhar uma caixa à volta daquilo que vais construir.

```text
        User
          |
          v
     +----------+
     |  SYSTEM  | ← aquilo que construo
     +----------+
          ^
          |
     Other system
```

A pergunta é:

> O que pertence à minha caixa e o que está fora dela?

---

### Model vs metamodel

Usa esta analogia:

```text
C grammar
   ↓
C program
```

equivale aproximadamente a:

```text
Metamodel
   ↓
Model
```

O metamodelo diz **que construções são permitidas**.

O modelo utiliza essas construções para representar um sistema específico.

---

### UML vs SysML

Pensa num carro:

```text
UML
→ modelar sobretudo o software do ECU

SysML
→ ECU + sensores + atuadores + hardware +
   requisitos + interfaces + restante sistema
```

Não significa que UML seja incapaz de representar coisas fora de software; esta é a distinção de foco apresentada na aula.

---

### MDA

Imagina que ainda não decidiste usar ESP32 ou STM32.

```text
PIM
TemperatureController
Sensor
Actuator
```

Depois decides STM32:

```text
PSM
STM32
ADC
GPIO
TIMx
...
```

Primeiro modelas a solução **independentemente da plataforma**; depois especializas para uma tecnologia.

---

# 3. Detect and Correct Issues

As tuas notas são úteis como registo da aula, mas há alguns pontos a corrigir.

| Nota                                           | Avaliação                 | Correção                                                                                                                                |
| ---------------------------------------------- | --------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| “QVT é uma linguagem de modelação”        | ❌                          | QVT está associado a**model-to-model transformations**.                                                                            |
| “SysML foi baseado no...”                    | ⚠️ incompleto             | SysML 1.x foi desenvolvido com base/extensão de**UML**.                                                                            |
| “Kernel Model Language é tipo superclasses” | ⚠️ demasiado simplificado | KerML fornece a**foundation** para SysML v2.                                                                                        |
| “OMG promove standards de modelação”       | ✅                          | Correto no contexto da aula.                                                                                                              |
| “requisitos têm de ser validados”           | ✅                          | Conceito explicitamente enfatizado.                                                                                                       |
| “rastreabilidade”                            | ✅                          | Conceito importante de Requirements Management.                                                                                           |
| “Papyrus open source”                        | ✅                          | Papyrus é uma ferramenta open-source baseada no ecossistema Eclipse.                                                                     |
| “UML tem 300 classes cerca”                  | ⚠️                        | O professor/slides referem a grande dimensão do**metamodelo UML**; não memorizes “300”.                                         |
| “modelo da realidade e perceção cerebral”  | ✅ ideia                    | O ponto é que a nossa representação da realidade passa por**perceção/modelos mentais**, podendo perder/distorcer informação. |

As notas realmente registam validação e rastreabilidade como conceitos separados, o que deve ser mantido. notas_12_10

Também registam corretamente a passagem posterior para Papyrus, metamodelos e SysML. notas_12_10 notas_12_10

---

# 4. 📓 30-Min Notebook Summary

Esta é a parte que eu escreveria à mão.

## Requirements Engineering

**Requirement**

- condição/capacidade necessária ao stakeholder/sistema
- descreve necessidade, comportamento ou propriedade

**Requirements Engineering**

- obter
- documentar
- validar
- gerir requisitos

### Types

**Functional**

- o que o sistema faz

**Quality / non-functional**

- quão bem faz
- performance
- availability
- dependability
- security etc.

**Constraint**

- limita solution space
- tecnologia, standard, prazo etc.

---

## Communication

Realidade → perceção → modelo mental → descrição.

Problema:

- pessoas interpretam linguagem diferentemente
- linguagem natural pode ser ambígua

Objetivo:

- requisitos claros
- precisos
- compreensíveis
- verificáveis/validáveis

Structured language/templates ajudam a reduzir ambiguidade.

---

## System Context

**System boundary**

- separa sistema do exterior

**Context**

- elementos externos relevantes que influenciam/interagem com sistema

Ex.:

```text
Actors → [SYSTEM] ← External systems
             ↑
         constraints
```

Use cases podem ajudar a representar:

- atores
- funcionalidades
- fronteira do sistema

---

## Requirements Validation

Requisitos devem ser validados.

Pergunta:

> Estamos a especificar aquilo que o stakeholder realmente necessita?

Erro no requisito → possível erro em todo o desenvolvimento.

---

## Requirements Management

Requisitos mudam → precisam de gestão.

**Traceability**

```text
Need → Requirement → Model → Implementation → Test
```

Permite:

- perceber origem
- impacto de alterações
- saber como requisito é implementado/testado

---

# Modeling

Modelo = representação de algo.

Diferentes modelos mostram diferentes **views**:

- structure
- behaviour
- functionality

---

## UML

**Unified Modeling Language**

- linguagem de modelação
- forte foco em software
- vários tipos de diagramas
- definida através de um metamodelo

---

## Model vs Metamodel

```text
Metamodel
defines language
     ↓
Model
represents system
```

Analogia:

```text
grammar → sentence
metamodel → model
```

---

## OMG

Object Management Group.

Standards referidos:

- UML
- SysML
- MOF
- XMI
- QVT

---

## MDA

Model-Driven Architecture.

```text
CIM
↓
PIM
↓
PSM
↓
Code
```

**CIM**

- requirements/business
- independente da computação

**PIM**

- estrutura/comportamento
- independente da plataforma

**PSM**

- tecnologia/plataforma concreta

Transformações:

```text
PIM → PSM = model-to-model
PSM → code = model-to-code
```

**QVT**

- model transformations

---

## SysML

Systems Modeling Language.

Foco:

```text
software
hardware
requirements
interfaces
system behaviour
```

SysML 1.x relacionado/derivado de UML.

**SysML v2**

- nova geração
- foundation: **KerML**

---

## Papyrus

```text
SysML/UML = languages
Papyrus = tool
```

Eclipse Papyrus:

- open source
- criação/edição de modelos.

---

# 5. Core Concepts — apenas os difíceis

## 1. Requirement → Model → System

Não confundas estes níveis:

```text
"I need X"
    ↓
Requirement

"Here is how the system is structured/behaves"
    ↓
Model

Actual hardware/software
    ↓
System
```

O modelo **não é o sistema**. É uma representação dele.

---

## 2. Model vs Metamodel

Esta é provavelmente a pergunta mais provável de te bloquear inicialmente.

```text
Metamodel = rules/vocabulary
Model     = instance using those rules
```

Exemplo:

```text
UML metamodel:
Class, Attribute, Association...

Your model:
Car
 ├── speed
 └── engine
```

---

## 3. Context boundary

Não perguntes apenas:

> “O que faz o sistema?”

Pergunta primeiro:

> **“O que considero parte do sistema?”**

Sem essa fronteira, nem sequer sabes corretamente quais responsabilidades pertencem ao teu sistema.

---

## 4. PIM vs PSM

```text
PIM = solution without committing to technology
PSM = solution adapted to specific technology
```

Mental model:

> PIM = arquitetura genérica.
> PSM = arquitetura já comprometida com STM32/Linux/Java/etc.

---

## 5. UML vs SysML

```text
            UML
             ↓
     software-oriented modeling

            SysML
             ↓
       systems engineering
             ↓
hardware + software + requirements + interfaces + behaviour
```

Para **Critical Systems**, esta diferença torna-se especialmente importante porque o sistema raramente é apenas código.

---

# 6. Essential Exam Questions — 5 total

### Q1 — Conceptual

**Qual a diferença entre functional requirement, quality requirement e constraint?**

**Resposta:** Functional define o que o sistema faz; quality define propriedades/qualidade desse comportamento; constraint limita as soluções ou o processo de desenvolvimento.

**Raciocínio:** `what` vs `how well` vs `solution limitation`.

---

### Q2 — Conceptual

**Qual a diferença entre model e metamodel?**

**Resposta:** Um model representa um sistema; um metamodel define os conceitos e regras utilizados para construir esses modelos.

**Raciocínio:** `metamodel → defines language → model`.

---

### Q3 — Practical

Requisito:

> “O sistema deve responder rapidamente ao utilizador.”

**Qual é o problema principal?**

**Resposta:** É ambíguo/não suficientemente preciso: “rapidamente” não estabelece um critério mensurável.

**Raciocínio:** Pessoas diferentes podem interpretar tempos de resposta diferentes.

---

### Q4 — Practical

Tens um modelo de um sistema sem qualquer referência a STM32, ESP32 ou Linux. Depois transformas esse modelo numa versão específica para STM32.

**Que níveis MDA representam aproximadamente estes dois modelos?**

**Resposta:** `PIM → PSM`.

**Raciocínio:** O primeiro é platform-independent; o segundo contém decisões específicas da plataforma.

---

### Q5 — Multiple Choice

Qual afirmação está correta?

A. SysML é uma ferramenta de modelação.
B. Papyrus é uma linguagem semelhante a UML.
C. Um metamodelo define os conceitos utilizados para criar modelos.
D. QVT é uma linguagem para escrever requisitos em linguagem natural.

**Resposta:** **C**

**Raciocínio:** Papyrus é ferramenta; UML/SysML são linguagens; QVT está relacionado com transformações de modelos.

---

# 7. Common Pitfalls

1. **Confundir non-functional com “não importante”.** Quality requirements como performance, availability ou safety podem determinar fortemente a arquitetura.
2. **Confundir requirement com implementação.** “Usar tecnologia X” pode ser um **constraint**, enquanto “o sistema deve fazer X” é funcionalidade.
3. **Pensar que UML/SysML são ferramentas.** São **linguagens de modelação**; Papyrus é uma ferramenta que as suporta.
4. **Confundir model com metamodel.** O teu diagrama é um **modelo**; as regras/conceitos que permitem construir esse diagrama pertencem ao **metamodelo**.
5. **Decorar diagramas sem compreender a cadeia da aula.** A ideia central é muito mais importante:

```text
Stakeholder / Reality
        ↓
Requirements
        ↓
System Context
        ↓
Precise Documentation
        ↓
Models
        ↓
UML / SysML
        ↓
Implementation
        ↓
Validation + Traceability
```

### 📓 Se só guardares uma ideia desta aula

**Requirements Engineering tenta garantir que estamos a construir a coisa certa; modelação tenta criar representações suficientemente estruturadas do sistema para conseguirmos analisar e desenvolver essa coisa.**

No contexto desta UC, isto liga diretamente requisitos, UML/SysML, rastreabilidade, especificação e verificação — precisamente o foco previsto para **Engenharia Orientada a Requisitos e Modelos** no teu projeto do mestrado. PROJECT_CONTEXT_Mestrado_Sistem…
