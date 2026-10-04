# Mestrado em Engenharia de Sistemas Computacionais Críticos — Project Context


                    CHATGPT PROJECT
          "Mestrado Sistemas Computacionais Críticos"
                         │
          ┌──────────────┴──────────────┐
          │                             │
   contexto global                 chats especializados
          │                             │
          │                ┌────────────┼─────────────┐
          │                │            │             │
       MASTER           CCSAR         RTESY         COMCS ...
          │
          └──────────────────┬────────────────────────┘
                             │
                             ▼
                         GIT REPO
                             │
                  1-ano/1-semestre/
                             │
       ┌──────────────┬──────┼──────┬───────────────┐
     CCSAR          RAMDE   CSLAB  RTESY           COMCS


## 1. Objetivo deste projeto

Este projeto acompanha o Mestrado em Engenharia de Sistemas Computacionais Críticos no ISEP.

Objetivos principais:

- acompanhar as unidades curriculares;
- organizar aulas, laboratórios, exercícios e projetos;
- recuperar rapidamente matéria dada antes do início efetivo das aulas;
- relacionar os conteúdos do mestrado com conhecimentos anteriores de Embedded Engineering;
- transformar aprendizagem académica em conhecimento técnico reutilizável;
- manter documentação, decisões, experiências e debugging de forma versionada em Git;
- usar GitHub Issues para trabalho acionável e acompanhamento de progresso.

---

## 2. Estrutura académica — 1.º Ano / 1.º Semestre

### Arquiteturas de Computadores para Sistemas Críticos
Diretório:

`1-ano/1-semestre/arquiteturas-computadores/`

Foco esperado:

- arquitetura de computadores;
- pipeline;
- memória e cache;
- paralelismo;
- multicore;
- previsibilidade temporal.

### Engenharia Orientada a Requisitos e Modelos
Diretório:

`1-ano/1-semestre/requisitos-modelos/`

Foco esperado:

- requisitos;
- modelação;
- UML / SysML;
- rastreabilidade;
- especificação e verificação.

### Laboratório de Sistemas Críticos
Diretório:

`1-ano/1-semestre/laboratorio-sistemas-criticos/`

Foco esperado:

- integração;
- implementação;
- testes;
- debugging;
- documentação;
- decisões de engenharia.

### Sistemas Embebidos e de Tempo-Real
Diretório:

`1-ano/1-semestre/sistemas-embebidos-tempo-real/`

Conhecimento anterior relevante:

- FreeRTOS;
- pthreads;
- mutexes;
- semáforos;
- concorrência;
- sincronização;
- ESP32;
- C / C++;
- sistemas embebidos.

Foco esperado:

- scheduling;
- deadlines;
- WCET;
- schedulability analysis;
- priority inversion;
- recursos partilhados;
- multiprocessor scheduling;
- mixed-criticality systems.

### Tecnologias de Comunicação para Sistemas Críticos
Diretório:

`1-ano/1-semestre/tecnologias-comunicacao/`

Conhecimento anterior relevante:

- Ethernet;
- IPv4 / IPv6;
- TCP / UDP;
- MQTT;
- CAN / CAN-FD;
- routing;
- VLAN;
- tcpdump;
- nmap;
- Linux networking.

Foco esperado:

- comunicação determinística;
- latência e jitter;
- fiabilidade;
- fault tolerance;
- redes industriais;
- protocolos para sistemas críticos.

---

## 3. Estratégia de Catch-up

O início efetivo das aulas pode ocorrer depois do início formal do semestre.

Não recuperar cronologicamente tudo.

Ordem de prioridade:

1. trabalhos e projetos já iniciados;
2. deadlines próximos;
3. conceitos necessários para acompanhar a aula atual;
4. laboratórios;
5. teoria anterior não bloqueante.

Documento de controlo:

`docs/catch-up.md`

Pergunta principal:

> O que preciso de saber agora para conseguir acompanhar e executar o trabalho atual?

---

## 4. Convenção para GitHub Issues

Cada Issue deve representar uma tarefa concreta e verificável.

### Prefixos sugeridos

- `[ARCH]` — Arquiteturas de Computadores
- `[REQ]` — Requisitos e Modelos
- `[LAB]` — Laboratório de Sistemas Críticos
- `[RT]` — Sistemas Embebidos e Tempo-Real
- `[COM]` — Tecnologias de Comunicação
- `[META]` — organização geral do mestrado

### Exemplos

- `[RT] Rever Rate Monotonic Scheduling`
- `[COM] Reproduzir captura CAN e documentar timing`
- `[ARCH] Entender cache miss e impacto temporal`
- `[LAB] Preparar ambiente de desenvolvimento`
- `[META] Atualizar catch-up após primeira semana`

### Estrutura de uma Issue

```md
## Objetivo

O que deve ficar compreendido ou concluído.

## Evidência de conclusão

- [ ] exercício resolvido
- [ ] teste executado
- [ ] notas atualizadas
- [ ] código/documentação commitados

## Material

Links para slides, documentação, datasheets, standards ou papers.

## Notas

Resultados, dúvidas e decisões.
```

---

## 5. Fluxo de trabalho

Fluxo recomendado:

```text
Aula / problema
      ↓
GitHub Issue
      ↓
branch
      ↓
experiência / exercício / código
      ↓
notas técnicas
      ↓
commit
      ↓
issue fechada
```

Exemplo:

```bash
git switch -c study/rt-rate-monotonic
```

Depois:

```bash
git add .
git commit -m "docs(rt): add notes on rate-monotonic scheduling"
```

---

## 6. Regras de documentação

Guardar no Git:

- código próprio;
- notas próprias;
- exercícios;
- experiências;
- diagramas produzidos pelo aluno;
- decisões de engenharia;
- resultados de debugging;
- links para documentação oficial.

Evitar versionar por defeito:

- PDFs dos professores;
- PowerPoints;
- ficheiros binários grandes;
- builds;
- ambientes virtuais;
- material protegido que não seja necessário distribuir.

---

## 7. Método de estudo técnico

Para cada conceito:

1. formular uma hipótese;
2. prever o comportamento esperado;
3. testar;
4. observar output;
5. explicar o resultado;
6. consultar documentação oficial;
7. guardar apenas a conclusão reutilizável.

Preferir:

- datasheets;
- reference manuals;
- application notes;
- documentação oficial;
- standards;
- livros técnicos;
- papers;
- experimentação prática.

---

## 8. Relação com Embedded Engineering

O mestrado deve aprofundar conhecimentos já adquiridos em Embedded Engineering.

Mapa mental:

```text
Embedded Engineering
        ↓
construir e programar o sistema
        ↓
Critical Systems
        ↓
analisar previsibilidade
verificar comportamento
justificar requisitos
avaliar falhas
demonstrar propriedades
```

Princípio central para sistemas de tempo-real:

> Correctness = logical correctness + temporal correctness.

---

## 9. Estado inicial

- [x] Repositório criado
- [x] Estrutura do 1.º semestre criada
- [x] Diretórios preservados com `.gitkeep`
- [x] `.gitignore` preparado
- [ ] READMEs das UCs preenchidos
- [ ] `docs/catch-up.md` preenchido
- [ ] primeiro commit estrutural
- [ ] primeiras GitHub Issues criadas
- [ ] primeira semana de aulas mapeada
