# Git
### Download
- https://git-scm.com/download/win
- after installing the git, launch `Git Bash`

### Config
- `$ git config --global user.name "Hugo Chang"`
- `$ git config --global user.email "hugo@gmail.com"`
- `$ git config --list`
```
user.name=Hugo Chang
user.email=hugo@gmail.com
````
- `vi ~/.gitconfig`
````
[user]
        name = Hugo Chang
        email = hugo@gmail.com
````
- `$ git config --local user.name "Hugo Chang"`
- `$ git config --local user.email "hugo@gmail.com"`
- `$ git config --global alias.co checkout`
- `$ git config --global alias.l "log --oneline --graph`

### Start
- `$ git init`
````
Initialized empty Git repository in C:/Users/mtk04140/git_demo/.git/
````
- `$ git status`
````
On branch master

No commits yet

nothing to commit (create/copy files and use "git add" to track)
````
- `$ echo "hello" > test.txt`
- `$ git status`
````
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        test.txt

nothing added to commit but untracked files present (use "git add" to track)
````
- `$ git add test.txt`
- `$ git add *.txt`
- `$ git add .`
  - equal to `$ git add --all`
- `$ git status`
````
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   test.txt
````
- `$ git commit -m "init commit"`
````
[master (root-commit) 7097d33] init commit
 1 file changed, 1 insertion(+)
 create mode 100644 test.txt
````
- `$ git log`
````
commit 7097d33cffe9d838ece10f5c988e1d3ca0ea89fc (HEAD -> master)
Author: Hugo Chang <hugo@gmail.com>
Date:   Thu Apr 27 09:16:31 2023 +0800

    init commit
````
- `$ git log --oneline --graph`
````
* 07a459a (HEAD -> master) add new file
* 7097d33 init commit
````
- `$ git log --author="hugo"`
- `$ git log --author="hugo\|bean"`
- `$ git log --grep="keyword"`

