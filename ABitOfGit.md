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
programming terminology – it will get more familiar to you as you use it!

![The Github Logo](http://romain.therrat.fr/wp-content/plugins/better-github-widget/octocat.png)

One of the major benefits of Git is its ubiquity. Git comes preinstalled on all
Mac and Linux computers, and a simple installation file is available on
Windows. Additionally, Git will store the code history of your project as it
progresses, making the process of reverting recent, and sometimes harmful,
changes a breeze.

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

Advanced Git Commands
---------------------

If Git only tracked the changes you make to your code, it would be a pretty
boring piece of software. However, Git can do so much more than that! Let's
have a look at some of Git's more advanced functionality:
