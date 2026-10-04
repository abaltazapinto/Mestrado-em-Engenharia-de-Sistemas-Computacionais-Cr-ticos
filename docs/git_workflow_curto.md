git switch main
git pull --ff-only
git switch -c <nome-da-branch>
git status
git add .
git commit -m "tipo(area): mensagem curta"
git push --set-upstream origin <nome-da-branch>
gh pr create --base main --head <nome-da-branch>
gh pr checks <numero-do-pr>
gh pr merge <numero-do-pr> --merge --delete-branch
git switch main
git pull --ff-only
git branch -d <nome-da-branch>
git fetch --prune

# Ver threads abertas:

> gh api graphql -F owner=abaltazapinto -F name=Mestrado-em-Engenharia-de-Sistemas-Computacionais-Cr-ticos -F number=<numero-do-pr> -f query='query($owner:String!,$name:String!,$number:Int!){repository(owner:$owner,name:$name){pullRequest(number:$number){reviewThreads(first:100){nodes{id isResolved path}}}}}' --jq '.data.repository.pullRequest.reviewThreads.nodes[] | select(.isResolved == false) | {id,path}'

# Resolver uma thread:

> gh api graphql -F threadId=<ID_DA_THREAD> -f query='mutation($threadId:ID!){resolveReviewThread(input:{threadId:$threadId}){thread{isResolved}}}'

# Regra mental:

    main → branch → alterar → add → commit → push → PR → merge → main → pull → apagar branch

