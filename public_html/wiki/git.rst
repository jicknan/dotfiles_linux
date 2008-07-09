======================
Git 分散式版本控制系统
======================

:Copyright: Copyright 2008 Jick Nan.
:Author: Jick Nan <jick.nan 在 gmail.com>
:Create Date: Sat 10 May 2008 03:37:38 PM CST

.. contents::

Git 快速上手
------------

- 设置个人信息::

  $ git config ­global user.name "Jick Nan"
  $ git config ­global user.email "jick.nan@gmail.com"

- 建立 Respository::

  $ git init

- clone::

  $ git clone git://git.kernel.org/scm/git/git.git # using git protocol
  $ git clone ssh://[user@]host:~/project/jicknan jicknan.git # ssh way

- 建立 branch::

  $ git branch <name>
  $ git branch <name> <commit-id>

- 移除 branch::

  $ git branch -d <name>

- 显示 branch 列表::

  $ git branch
  $ git branch -a # 显示所有的 branch

- 显示各个 branch 的发展状态::

  $ git-show-branch

- 产看各 branch 的最新 commit::

  $ git-show-ref

- 查看 branch 的版本差异::

  $ git diff master work

- 查看当前 branch 的变化状况::

  $ git-whatchanged

- 采用 /Jump 到某个 commit::

  $ git checkout <commit-id>
  $ git checkout -b <name> <commit-id>

- 给远端 Repository 清除的标示（如 min)::

  $ git remote add min ssh://<username>@git.kernel.org/scm/git/git.git

- 用指定的标示抓取修改::

  $ git fetch min
  $ git pull min # 另一种方法

- 整合 min repository 到 master branch::

  $ git merge min/master

- 显示 commit 的 SHA1::

  $ git rev-list HEAD^..HEAD

- 显示记录::

  $ git log
  $ git log HEAD~4..HEAD
  $ git log ­pretty=oneline v1.0..v2.0 | wc-l
  $ git log --raw -r --abbrev=40 ­pretty=oneline origin..HEAD
  $ git archive --format=tar --prefix=project/ HEAD | gzip >latest.tar.gz
  $ git blame <filename>

- 产生 commit (于 local)::

  $ git diff -cached
  $ git add .
  $ git diff HEAD
  $ git commit

- Reset the conflicted merge: use git-reset::

  $ git reset ­-mixed <commit-id> # Reset the index database to the moment before merging
  $ git reset ­-hard <commit-id> # Reset the index database and the working data
  $ git reset ­-soft <commit-id> # 在不触及工作区资料与 index 资料库的前提下，进行错误修正。

git-svn
-------

- Clone a repo (like git clone)::

  $ git-svn clone http://svn.foo.org/porject/trunk foo-svn-git

- Enter the newly cloned directory::

  $ cd foo-svn-git

- You should be on master branch, double-check with git-branch::

  $ git branch

- Do some work and commit locally to git::

  $ git commit ...

- Something si committed to SVN, rebase your local changes against the
  latest changes in SVN::

  $ git-svn rebase

- Now commit your changes (that were committed previously using git) to SVN,
  as well as automatically updating your working HEAD::

  $ git-svn dcommit

- Append svn:ignore settings to the default git exclude file::

  $ git-svn show-ignore >> .git/info/exclude

Git 相关工具
------------

- 低阶、内建::

   $ git-write-tree
   $ git-commit-tree

- 高阶、外部

  * StGit ­ quilt for git

  * qgit, git gui, gitk ­ graphical tools

  * Gitweb

  * Cogito ­ cvs command like syntax (depricated)

  * Trac - git plugin available

Git repository
--------------

- git@github::

  $ cd existing_git_repo
  $ git remote add origin git@github.com:jicknan/jicknan.git
  $ git push origin master

- git@or.cz::

  $ git remote add orcz git+ssh://repo.or.cz/srv/git/jicknan.git


Resources
--------
- `Everyday GIT With 20 Commands Or So`__
- `Git 中文教程`__
- `如何在svn系统中使用 git`__
- `git for CVS users`__
- `rst2html + git == personal wiki`__

__ http://www.kernel.org/pub/software/scm/git/docs/everyday.html
__ http://www.bitsun.com/documents/gittutorcn.htm
__ http://www.robinlu.com/blog/archives/194
__ http://www.kernel.org/pub/software/scm/git/docs/cvs-migration.html
__ http://lucumr.pocoo.org/cogitations/2008/05/02/rst2html-git-personal-wiki/
