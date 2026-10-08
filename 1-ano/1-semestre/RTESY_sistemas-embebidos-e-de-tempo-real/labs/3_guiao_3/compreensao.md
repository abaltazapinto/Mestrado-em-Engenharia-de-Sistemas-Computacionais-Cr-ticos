# Compreensao do guiao 3.

o guiao pede dois programas

Programa A                         Programa B
──────────                         ──────────
3 pthreads periódicas              3 pthreads periódicas
SCHED_FIFO                         SCHED_RR
prioridades diferentes             prioridades diferentes
períodos diferentes                períodos diferentes
WCET artificial                    WCET artificial
       │                                  │
       └──────────────┬───────────────────┘
                      ↓
               trace-cmd / kernel
                      ↓
                 KernelShark
                      ↓
         observar quem executa e quando

1. O que queremos demonstrar

	tens 3 tarefas periodicas , por exemplo: 

	τ1: prioridade alta     período curto
	τ2: prioridade média    período médio
	τ3: prioridade baixa    período longo

 Cada tarefa executa repetidamente: 

esperar instante de ativação
        ↓
ficar READY
        ↓
obter CPU
        ↓
executar um certo trabalho
        ↓
terminar esse job
        ↓
esperar próxima ativação

a experiencia consuste em prever:

> Quando duas ou mais threads estao READY, qual delas recebe o CPU ? 

E depois confrontar essa previsao com o que realmente aconteceu no kernel. 

 Cada tarefa executa repetidamente: 

esperar instante de ativação
        ↓
ficar READY
        ↓
obter CPU
        ↓
executar um certo trabalho
        ↓
terminar esse job
        ↓
esperar próxima ativação

a experiencia consuste em prever:

> Quando duas ou mais threads estao READY, qual delas recebe o CPU ? 

E depois confrontar essa previsao com o que realmente aconteceu no kernel. 

 Cada tarefa executa repetidamente: 

esperar instante de ativação
        ↓
ficar READY
        ↓
obter CPU
        ↓
executar um certo trabalho
        ↓
terminar esse job
        ↓
esperar próxima ativação

a experiencia consuste em prever:

> Quando duas ou mais threads estao READY, qual delas recebe o CPU ? 

E depois confrontar essa previsao com o que realmente aconteceu no kernel. 

2. O fenomeno que tens de conseguir ver no KernelShark

O kernelShark vai transformar algo abstracto como:

	> pthread_setschedparam(....);

numa linha temporal concreta.

Imagina : 

tempo ───────────────────────────────────────────────>

τ3 LOW       ███████──────████────────────
τ2 MEDIUM    ──────████──────────████─────
τ1 HIGH      ───██──────────██────────██──

nao quero que olhes para isto como apenas 3 threads

> Quero que p[erguntes:

Quem estava READY neste instante?
        ↓
Que prioridade tinha?
        ↓
Qual política estava ativa?
        ↓
Porque foi esta thread escolhida?
        ↓
Porque deixou de executar?

> Se conseguir responder a essas cinco perguntas olhando para um trace, estas a comecar perceber de scheduling real. 

---

Ha particularmente quatro APIs que vao tornar se importantes:

	pthread_create()
	pthread_setschedparam()
	pthread_setaffinity_np()
	clock_nanosleep()

Primeiro precisamos de perceber por que existem

4. Dependency map

PROCESSO
   ↓
THREAD
   ↓
estado da thread
READY / RUNNING / BLOCKED
   ↓
scheduler
   ↓
scheduling policy
SCHED_FIFO / SCHED_RR
   ↓
prioridade
   ↓
preempção
   ↓
tarefas periódicas
   ↓
release → execução → conclusão
   ↓
WCET + período
   ↓
trace real de execução
   ↓
trace-cmd + KernelShark

Mais tarde pensaremos : 

CPU affinity
     ↓
qual CPU pode executar a thread
     ↓
reduzir efeitos multicore na experiência

isto e importante: se as 3 threads puderem correr simultaneamente em tres CPUs diferentes, fica muito mais dificil observar o fenomento de scheduling que queremos estudar. 

---

pergunta -> ficou claro que em SCHED_FIFO , uma thread de prioridade mais alta que fica pronta preempta uma thread de prioridade inferior..

Portanto : 

antes:
CPU → B (prio 60)

A fica READY (prio 80)

depois:
CPU → A (prio 80)
      B volta para READY

---

# Saber
.RM
prioridades FIXAS
determinadas normalmente pelo período

EDF
prioridades DINÂMICAS
determinadas pela deadline absoluta mais próxima

---

RM e um algoritmo de scheduling/analise

	SCHED_FIFO e SCHED_RR sao politicas reais disponibilizadas pelo Linux/POSIX

---


