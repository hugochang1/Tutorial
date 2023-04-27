# Git
# Download Git
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

### Start Using Git
- `$ git init`
````
Initialized empty Git repository in C:/Users/mtk04140/git_demo/.git/
````

