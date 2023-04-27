# ----------------- Download -----------------
https://git-scm.com/downloads

# ----------------- Config -----------------
$ git config --list

$ git config --global user.name "Hugo Chang"
$ git config --global user.email "Hugo.Chang@gmail.com"

$ git config --local user.name "Hugo Chang"
$ git config --local user.email "Hugo.Chang@gmail.com"

$ git config --global alias.co checkout
$ git config --global alias.l "log --oneline --graph"

$ vi ~/.gitconfig

# ----------------- Basic Operation -----------------
$ git init
$ rm -rf .git

$ git status
$ git diff
$ git log -p

$ git add file
$ git add .

withdraw git add
$ git rm --cached file
$ git rm --cached -r .

$ git commit -m "commit message"

$ gitk
$ git log
$ git log -3
$ git log fileName
$ git log -p fileName
$ git log --oneline
$ git log --autho="Hugo"
$ git log --autho="Hugo\|Leo"
$ git log --grep="search something in commit message"
$ git log -p -S "search something in the content"

# ----------------- Modify Last Commit -----------------
$ git commit --amend -m "modify the last commit message"

add one file to the last commit without changing it
$ git add newFile
$ git commit --amend --no-edit

# ----------------- .gitignore -----------------
$ vi .gitignore

# this is comment
# ignore myself
.gitignore

# ignore file1.txt
file1.txt
*.txt
!file2.txt

# ----------------- Check File Content -----------------
$ git blame fileName

to check a range of specific lines
$ git blame -L 3,10 fileName

# ----------------- Rollback the file for working directory -----------------
$ git checkout fileName
$ git checkout .

rollback whole codebase to previous two version
$ git checkout HEAD~2 .

# ----------------- Rollback the file for working directory and staging area -----------------
$ git reset --hard HEAD

rollback all to previous two commit
$ git reset --hard HEAD~2

$ git reflog
$ git reset -hard 7bbaeeb

# ----------------- Branch -----------------
$ git branch

create a branch
$ git branch cat
$ git branch cat commit_id

change a branch name
$ git branch -m cat tiger

delete a branch
$ git branch -d dog

switch branch
$ git checkout cat

# ----------------- Merge -----------------
merge branch
$ git merge cat
$ git merge commit_id

it will create a new commit and its parents are cat and dog
cat will be moved to this new commit

merge conflict handling
step 1. check which file conflict
  $ git status
step 2. correct it
step 3. commit it
  $ git add file
  $ git commit -m "conflict fixed"

# ----------------- Rebase -----------------
merge branch
$ git rebase cat

all commits in dog branch will generate new commits to cat branch
dog will be moved to the last new commit

merge conflict handling
step 1. check which file conflict
  $ git status
step 2. correct it
step 3. commit it
  $ git add file
  $ git rebase --continue

# ----------------- Merge Conflict for Binary File -----------------
merge conflict for binary file
in step 2
$ git checkout --ours file
$ git checkout --theirs file

# ----------------- Give up the last rebase, merge, or reset -----------------
git reset --hard ORIG_HEAD

# ----------------- Change historical commit messages -----------------
check log list first
$ git log --oneline
$ git rebase -i commit_id

# ----------------- Generate a new commit message for rollback -----------------
git revert HEAD

# ----------------- Tag -----------------
1. lightweight tag
$ git tag tag_name
$ git tag tag_name commit_id

2. annotated tag (recommended)
$ git tag tag_name commit_id -a -m "tag message"

check tag
$ git show tag_name

delete tag
$ git tag -d tag_name

# ----------------- Cherry-pick -----------------
$ git cherry-pick commit_id
$ git cherry-pick commit_id1 commit_id2 commit_id3
$ git cherry-pick commit_id --no-commit

# ----------------- Clear reflog -----------------
$ git reflog expire --all --expire=now

# ----------------- Clone the whole repo -----------------
$ git clone git@github.com:hugochang/project.git
$ git clone git@github.com:hugochang/project.git folder

$ git remote add origin git@github.com:hugochang/project.git

$ git push -u origin master

$ git fetch
$ git merge origin/master

git pull = git fetch + git merge (please be noted that git merge will create a new commit)
$ git pull

if you don't want to generate the additional commit message
$ git pull --rebase

# ----------------- Patches -----------------
$ git format-patch 8ec2e78..70b517c
$ git format-patch -2
$ git format-patch -2 -o ../patches/
$ git am patches/*
