# Mestrado em Engenharia de Sistemas Computacionais Críticos - ISEP

Repositório de estudo, laboratórios, exercícios, projetos e documentação técnica do
**Mestrado em Engenharia de Sistemas Computacionais Críticos — ISEP**.

O objetivo não é usar este repositório apenas como arquivo de materiais, mas como um
**engineering notebook versionado**, acompanhando a evolução técnica ao longo do mestrado.

---

## 1.º Ano — 1.º Semestre

| Unidade Curricular | Diretório | Estado |
|---|---|---|
| Arquiteturas de Computadores para Sistemas Críticos | [`arquiteturas-computadores`](./1-ano/1-semestre/CCSAR_arquiteturas-computadores/) | 🟡 A iniciar |
| Engenharia Orientada a Requisitos e Modelos | [`requisitos-modelos`](./1-ano/1-semestre/RAMDE_requisitos-modelos/) | 🟡 A iniciar |
| Laboratório de Sistemas Críticos | [`laboratorio-sistemas-criticos`](./1-ano/1-semestre/CSLAB_laboratorio-sistemas-criticos/) | 🟡 A iniciar |
| Sistemas Embebidos e de Tempo-Real | [`sistemas-embebidos-tempo-real`](./1-ano/1-semestre/RTESY_sistemas-embebidos-e-de-tempo-real/) | 🟡 A iniciar |
| Tecnologias de Comunicação para Sistemas Críticos | [`tecnologias-comunicacao`](./1-ano/1-semestre/COMCS_tecnologias-comunicacao/) | 🟡 A iniciar |

---

## Background técnico

O mestrado dá continuidade a conhecimentos adquiridos anteriormente em
**Embedded Engineering**, incluindo:

- C / C++
- ESP32
- FreeRTOS
- pthreads
- mutexes e semáforos
- concorrência e sincronização
- Linux
- Git
- GDB
- Raspberry Pi
- Ethernet
- IPv4 / IPv6
- TCP / UDP
- MQTT
- CAN / CAN-FD
- debugging hardware/software

O objetivo agora é evoluir de:

~~~text
construir e programar sistemas
              ↓
analisar previsibilidade
              ↓
verificar comportamento
              ↓
avaliar falhas
              ↓
demonstrar propriedades
              ↓
engenharia de sistemas críticos
~~~

---

## Estrutura do repositório

~~~text
.
├── 1-ano/
│   └── 1-semestre/
│       ├── arquiteturas-computadores/
│       ├── requisitos-modelos/
│       ├── laboratorio-sistemas-criticos/
│       ├── sistemas-embebidos-tempo-real/
│       └── tecnologias-comunicacao/
│
├── docs/
│   ├── catch-up.md
│   ├── plano-curricular.md
│   └── PROJECT_CONTEXT_Mestrado_Sistemas_Computacionais_Criticos.md
│
└── README.md
~~~

Cada UC pode conter:

~~~text
aulas/
labs/
exercicios/
projeto/
README.md
~~~

dependendo da natureza da disciplina.

---

## Workflow

O trabalho será organizado através de Git e GitHub Issues.

~~~text
Aula / problema
      ↓
GitHub Issue
      ↓
branch
      ↓
estudo / experiência / exercício / código
      ↓
notas técnicas
      ↓
commit
      ↓
Issue concluída
~~~

### Convenções

~~~text
[ARCH]  Arquiteturas de Computadores
[REQ]   Requisitos e Modelos
[LAB]   Laboratório de Sistemas Críticos
[RT]    Sistemas Embebidos e Tempo-Real
[COM]   Tecnologias de Comunicação
[META]  Organização geral
~~~

---

## Estratégia de catch-up

Como o início efetivo no mestrado poderá ocorrer depois das primeiras aulas,
a recuperação será feita por prioridade:

1. trabalhos e projetos já iniciados;
2. deadlines próximos;
3. conceitos necessários para acompanhar as aulas atuais;
4. laboratórios;
5. teoria anterior não bloqueante.

Estado de recuperação:

[`docs/catch-up.md`](./docs/catch-up.md)

---

## Método de estudo

~~~text
Hipótese
   ↓
Output esperado
   ↓
Experiência / exercício
   ↓
Observação
   ↓
Explicação
   ↓
Documentação oficial
   ↓
Conclusão reutilizável
~~~

### Fontes preferenciais

- datasheets
- reference manuals
- application notes
- documentação oficial
- standards técnicos
- livros técnicos
- papers científicos
- experimentação prática

---

## Real-Time Systems

> **Correctness = logical correctness + temporal correctness.**

Num sistema de tempo-real não basta produzir a resposta correta.
O instante em que essa resposta é produzida também faz parte da correção do sistema.

---

## Estado atual

- [x] Repositório criado
- [x] Estrutura do 1.º semestre criada
- [x] `.gitignore` configurado
- [x] GitHub Issues iniciais criadas
- [x] Project Context criado
- [ ] READMEs individuais das UCs preenchidos
- [ ] Catch-up preenchido com dados reais
- [ ] Primeiras aulas mapeadas
- [ ] Primeiros labs/projetos documentados

---

## Objetivo final

No final do mestrado, este repositório deverá documentar não apenas
**o que foi estudado**, mas principalmente:

- o que foi implementado;
- o que foi testado;
- o que falhou;
- como foi diagnosticado;
- quais decisões de engenharia foram tomadas;
- como essas decisões podem ser justificadas.
