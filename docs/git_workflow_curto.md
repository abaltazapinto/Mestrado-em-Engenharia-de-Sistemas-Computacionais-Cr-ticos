git switch main
git pull --ff-only
git switch -c <nome-da-branch></nome>
git status
git add .
git commit -m "tipo(area): mensagem curta"
git push --set-upstream origin <nome-da-branch></nome>
gh pr create --base main --head <nome-da-branch></nome>
gh pr checks <numero-do-pr></numero>
gh pr merge <numero-do-pr></numero> --merge --delete-branch
git switch main
git pull --ff-only
git branch -d <nome-da-branch></nome>
git fetch --prune

git stash list
git stash show --stat 'stash@{1}'

git stash = alterações guardadas fora da working tree/commit
git stash apply = recupera alterações e mantém o stash
git stash pop = recupera alterações e apaga o stash se correr bem
git add = adiciona alterações atuais ao staging; não inclui stashes automaticamente

git stash apply stash@{0}

# Ver threads abertas:

> gh api graphql -F owner=abaltazapinto -F name=Mestrado-em-Engenharia-de-Sistemas-Computacionais-Cr-ticos -F number=<numero-do-pr></numero> -f query='query($owner:String!,$name:String!,$number:Int!){repository(owner:$owner,name:$name){pullRequest(number:$number){reviewThreads(first:100){nodes{id isResolved path}}}}}' --jq '.data.repository.pullRequest.reviewThreads.nodes[] | select(.isResolved == false) | {id,path}'

# Resolver uma thread:

> gh api graphql -F threadId=<ID_DA_THREAD> -f query='mutation($threadId:ID!){resolveReviewThread(input:{threadId:$threadId}){thread{isResolved}}}'

# Regra mental:

    main → branch → alterar → add → commit → push → PR → merge → main → pull → apagar branch
