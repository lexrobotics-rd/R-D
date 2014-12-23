A Bit of Git: LexRobotics R&D Git Guide 2014-2015
=================================================

Welcome to the LexRobotics (eventually) comprehensive guide to Git! This guide 
serves as a reference for aspiring and advanced Git users alike. If you are new 
to programming or have never even heard of Git, this document will take you 
through all the steps needed to become a master Gitter.

What is Git?
------------

Git is a distributed revision control system: it is a program that allows many 
software developers to work on a given project without having to share a common 
network. Git automatically tracks changes to code files and other documents, 
and it allows developers to compare, restore, and in some cases merge the 
various revisions of a file. Git is most frequently accessed via a Command Line 
Interface (CLI), which involves entering text into a terminal emulator (for 
Macs, this is Terminal.app). Don't worry if you don't understand all the 
programming terminology – it'll get more familiar to you as you use it!

![The Github Logo](http://romain.therrat.fr/wp-content/plugins/better-github-widget/octocat.png)

One of the major benefits of Git is its ubiquity. Git comes preinstalled on 
just about all Mac and Linux computers, and a simple installation file is 
available for Windows. Additionally, Git will store the code history of your 
project as it progresses, making the process of reverting recent, unwanted, or 
harmful changes a breeze.

Windows Installation Guide
--------------------------

Download the latest version of Git for Windows from 
<http://git-scm.com/download/win>. The download should start automatically.

CLI Basics
----------

There are several must-know commands to be able to navigate around any file 
system in a CLI:

- To list the files and folders in your current directory: `ls`
- To change the current folder (working directory): `cd targetfolder`
- To go back to the parent folder: `cd ..`
- `cd`s can be strung together in a single command: `cd
  targetfolder/subfolder`
- A more complicated example: `cd ../../otherfolder/subfolder`

Practice these two basic commands until you have a feel for moving around a Git 
repository, or a group of related files being stored as a single project. They 
will be incredibly useful to you as your Git knowledge progresses! I can't 
stress this enough.

Github
------

[Github](https://github.com/) is an online service that hosts free, public Git 
repositories (or paid private ones). To make a Github account, follow these 
steps:

Introducing Git Commands
------------------------

- `git add -A`: prepares, or "stages," the changes to all the files in the Git 
  repository, including added or removed files.
- `git commit -m "[descriptive message of changes]"`: makes Git record a 
  snapshot of the current state of the repository in its version history.
- `git pull origin master`: downloads, or "pulls," changes to the repository 
  that are available online.
- `git push origin master`: uploads, or "pushes," local changes to the 
  repository so that they are public.

When you first learn these commands, it may feel like you are just banging your 
hands on the keyboard. Don't worry about it, _it will get easier_.

![What Programming Feels Like](http://www.cs.cmu.edu/~cangiuli/img/angry.gif)

Git Workflow
------------

- A programming session will always start with a `git pull origin master` and 
  end with a `git push origin master`.
- After changing a file, run `git add -A` and `git commit -m "[message]"`. It 
  is best __not__ to change multiple files, or to even change multiple parts of 
  one file, between commits. Having small, specific commits with _insightful_ 
  messages (not just `update`...) makes it easier to identify problems when 
  they arise in the codebase.

Really Cool Advanced Git Commands
---------------------------------

If Git only tracked the changes you make to your code, it would be a pretty 
boring piece of software. However, Git can do so much more than that! Let's 
have a look at some of Git's more advanced functionality:

- `git rm [file]`: deletes a file from the directory and stages the deletion.
```
git rm log.txt
```  
If I catch anyone deleting log files, I will not be amused.
- `git rm --cached [file]`: deletes a file from the staging area but leaves the 
  working copy alone.
- `git mv [file] [newname]`: renames a file and stages the rename. It is best 
  to restrict the use of `git mv`s to keep confusion to a minimum.
- `git status`: lists all files whose changes have been staged but not yet 
  committed. You should do a `git status` before each `git commit`, and if 
  you've changed more than a couple files, you should be committing more 
  frequently!
- `git diff`: shows file changes not yet staged.
- `git diff --staged`: shows file changes between the staged files and git's 
  previous version of each file. This command is like a more specific 
  `git status`.
- `git log`: lists the complete version history of the project, including the 
  date, message, and author of each commit.
- `git log --follow [file]`: lists the history of one specific file, including 
  renames (although it may lose track in extreme cases). A very useful command.

FAQ
---

- _Oops I just changed like 50 files without committing any of them. I guess 
  I'll just commit all the changes..._

  __No.__ Stage the files in groups with `git add [file]` and commit them 
  the right way, with meaningful messages. You will thank yourself later when 
  you can easily find any tiny bug that shows up in the codebase. If you 
  accidentally stage too many changes, you can "unstage" files with `git reset` 
  or `git reset [file]` for just one file.


- _Ughhh all the changes I've made since the last commit were completely wrong 
  and I need to toss them_

  `git reset --hard [file]` will erase everything up to the last commit.

(Good stuff on `git reset`: http://stackoverflow.com/a/5800164/1181387)


- _Ctrl-Z! Ctrl-Z!_
  Git is designed to keep track of everything, so just making a new commit that 
  reverses whatever you did is fine. However, if you really wanted to add 
  something to a previous commit, `git reset --soft HEAD~1` will reset the 
  repository to `HEAD~1` (moving back one commit) and stage the changes, allowing
  you to continue editing and then re-`git add; git commit` later.


- _Ahh the internet's down!_

  Don't worry; if you've committed your changes locally it's all saved. Just 
  remember to push your changes once the internet comes back!


<!--Probably not a good idea to create new repos unnecessarily.
- _Ahhh the internet's down but I want to make a new repo I should just add a 
  new folder to the robotics repository_
  `git init [repository name]` will make a local git repository that can be 
  uploaded to Github later.
-->


- *OMG git keeps uploading these useless .DS_Store files on Macs how do I kill 
  them*

  Create a file named .gitignore in the parent folder of the Git repository and 
  add a line `.DS_Store`.


- *I just realized I committed a password a while ago LOL*

  Try using `git filter-branch` (google that) or BFG. Or better yet, ask someone 
  who's done it before to show you.


- _I messed up something locally with git, and I don't know what happened!_

  Do NOT `git push`.

  If you don't have any local changes, try `git fetch; git reset --hard origin/[remote branch name]`.

  If you do have local changes, uncommit all the things you want to keep: 
  `git reset --soft [last commit hash that's not new]`. Edit stuff in the working 
  directory as desired. Stash all your changes with `git add -A; git stash`. 
  `git fetch; git reset --hard origin/[remote branch name]` to reset everything.
  `git stash apply` to reapply your changes on top of the new `HEAD`. Now you 
  can `git commit` and `git push` your various stashed changes.
  Or better yet, ask someone who's done it before to show you.
  [there probably is a better way to deal with locally-committed stuff than `git stash`.]
