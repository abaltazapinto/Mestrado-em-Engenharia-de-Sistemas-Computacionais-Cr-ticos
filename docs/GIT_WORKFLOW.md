# Git Workflow — Mestrado em Engenharia de Sistemas Computacionais Críticos

Este documento define o procedimento normal para fazer alterações neste repositório.

O objetivo é praticar um workflow próximo de desenvolvimento profissional e evitar commits diretamente na `main`.

---

## Regra principal

Nunca desenvolver diretamente na `main`.

A `main` representa o estado estável do repositório.

O fluxo normal é:

```text
main atualizada
    ↓
criar branch
    ↓
fazer alterações
    ↓
verificar alterações
    ↓
git add
    ↓
git commit
    ↓
git push
    ↓
Pull Request
    ↓
merge
    ↓
voltar à main
    ↓
git pull --ff-only
    ↓
apagar branch
```

---

# 1. Começar sempre pela `main`

Confirmar a branch atual:

```bash
git branch --show-current
```

Mudar para `main`:

```bash
git switch main
```

Atualizar a `main` local:

```bash
git pull --ff-only
```

### Porquê `--ff-only`?

Impede o Git de criar um merge inesperado durante um simples `pull`.

Se a história local e remota divergirem, o Git para e obriga-me a perceber primeiro o problema.

---

# 2. Confirmar que o repositório está limpo

Antes de criar uma branch:

```bash
git status
```

Idealmente:

```text
nothing to commit, working tree clean
```

Se existirem alterações, perceber primeiro de onde vêm.

---

# 3. Criar uma branch

Nunca trabalhar diretamente na `main`.

Exemplo:

```bash
git switch -c docs/rtesy-notes
```

Convenções úteis:

```text
docs/...      documentação e apontamentos
study/...     estudo de conceitos
feat/...      nova funcionalidade
fix/...       correção
chore/...     organização/manutenção
lab/...       experiências ou laboratórios
```

Exemplos:

```text
docs/rtesy-scheduling
study/rtesy-rate-monotonic
lab/comcs-can-timing
chore/semester-readmes
feat/cslab-monitoring
```

---

# 4. Fazer as alterações

Editar código, documentação, exercícios ou outros ficheiros.

Durante o trabalho posso verificar:

```bash
git status
```

E analisar exatamente o que alterei:

```bash
git diff
```

Esta etapa é importante.

Nunca fazer `git add .` mecanicamente sem primeiro perceber o que vai entrar no commit.

---

# 5. Preparar o commit

Depois de confirmar as alterações:

```bash
git add .
```

Confirmar o que ficou staged:

```bash
git status
```

Ver exatamente o conteúdo que será commitado:

```bash
git diff --cached
```

## Regra

Antes de qualquer commit devo conseguir responder:

> O que estou a guardar e porquê?

---

# 6. Criar o commit

Formato preferido:

```text
tipo(área): descrição curta
```

Exemplos:

```bash
git commit -m "docs(rt): add scheduling study notes"
```

```bash
git commit -m "docs(com): document CAN timing experiment"
```

```bash
git commit -m "chore(meta): add semester course READMEs"
```

```bash
git commit -m "lab(rt): add schedulability experiment"
```

Tipos úteis:

| Tipo | Utilização |
|---|---|
| `docs` | documentação |
| `feat` | nova funcionalidade |
| `fix` | correção |
| `lab` | experiências/laboratórios |
| `study` | estudo |
| `test` | testes |
| `chore` | organização/manutenção |
| `refactor` | reorganização sem alterar comportamento |

---

# 7. Confirmar o commit

Ver os últimos commits:

```bash
git log --oneline -5
```

Confirmar o estado:

```bash
git status
```

---

# 8. Fazer push da branch

Na primeira vez que a branch é enviada:

```bash
git push --set-upstream origin "$(git branch --show-current)"
```

Depois de o upstream existir:

```bash
git push
```

## Conceito importante

`origin` é o repositório remoto.

A branch local pode passar a acompanhar uma branch remota:

```text
local
chore/semester-readmes

        ↓ tracking

origin/chore/semester-readmes
```

---

# 9. Criar Pull Request

Usando GitHub CLI:

```bash
gh pr create --base main
```

Também posso indicar explicitamente a branch:

```bash
gh pr create --base main --head "$(git branch --show-current)"
```

## Conceito importante

```text
HEAD = branch de onde vêm as alterações
BASE = branch para onde quero enviar as alterações
```

Normalmente:

```text
minha branch
     ↓
    main
```

---

# 10. Verificar o Pull Request

Listar PRs:

```bash
gh pr list
```

Ver um PR:

```bash
gh pr view NUMERO_DO_PR
```

Ver estado do merge:

```bash
gh pr view NUMERO_DO_PR --json state,mergedAt,mergeCommit
```

Estados importantes:

```text
OPEN
MERGED
CLOSED
```

`OPEN` significa que criar o PR não fez ainda o merge.

---

# 11. Merge

Este repositório pode ter proteção da branch `main`.

Por isso, um comando como:

```text
gh pr merge
```

pode ser recusado até que os requisitos definidos no GitHub sejam cumpridos.

Não usar `--admin` como procedimento normal porque isso pode contornar as proteções configuradas no repositório.

Fazer o merge quando os requisitos do PR estiverem cumpridos.

Confirmar depois:

```bash
gh pr view NUMERO_DO_PR --json state,mergedAt,mergeCommit
```

Esperado:

```text
"state": "MERGED"
```

---

# 12. Atualizar a `main` depois do merge

Voltar à `main`:

```bash
git switch main
```

Atualizar:

```bash
git pull --ff-only
```

Agora a `main` local contém o trabalho que foi integrado através do PR.

---

# 13. Apagar a branch antiga

Depois de confirmar que o PR foi merged:

```bash
git branch -d NOME_DA_BRANCH
```

Exemplo:

```bash
git branch -d chore/semester-readmes
```

Se a branch remota ainda existir:

```bash
git push origin --delete NOME_DA_BRANCH
```

Nunca apagar uma branch antes de confirmar que o trabalho importante está integrado.

---

# Checklist rápido

Antes de começar:

```text
[ ] Estou na main
[ ] main está atualizada
[ ] working tree está limpo
[ ] criei uma branch
```

Antes do commit:

```text
[ ] executei git status
[ ] executei git diff
[ ] sei exatamente o que alterei
[ ] fiz git add
[ ] confirmei com git diff --cached
```

Antes do PR:

```text
[ ] commit criado
[ ] mensagem do commit faz sentido
[ ] branch enviada para origin
```

Depois do PR:

```text
[ ] PR foi realmente MERGED
[ ] voltei à main
[ ] executei git pull --ff-only
[ ] apaguei a branch antiga
```

---

# Workflow resumido

```text
git switch main
        ↓
git pull --ff-only
        ↓
git status
        ↓
git switch -c <branch>
        ↓
trabalhar
        ↓
git diff
        ↓
git add .
        ↓
git diff --cached
        ↓
git commit
        ↓
git push
        ↓
gh pr create
        ↓
review/checks
        ↓
merge
        ↓
git switch main
        ↓
git pull --ff-only
        ↓
git branch -d <branch>
```

---

# Regra mental

Antes de usar Git, pensar sempre:

```text
Onde estou?
↓
O que alterei?
↓
O que vou guardar?
↓
Para onde vou enviar?
```

Os quatro comandos que ajudam a responder são:

```bash
git branch --show-current
```

```bash
git status
```

```bash
git diff
```

```bash
git log --oneline -5
```

Git não deve ser uma sequência de comandos decorados.

O objetivo é perceber permanentemente:

```text
working tree
    ↓
staging area
    ↓
local repository
    ↓
remote branch
    ↓
Pull Request
    ↓
main
```
