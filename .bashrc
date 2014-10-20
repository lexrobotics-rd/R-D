# Sets up a convenient git Bash environment. Copy into ~. (that is, C:/Users/You/)

cd ~/Documents/Programming

alias gps="git push origin master"
alias gpl="git pull origin master"
alias gs="git status"
alias gc="git add -A && git commit"
alias cd..="cd .."
alias dir="ls"
alias main="cd ~/Documents/Programming/2015-4029 && git status"
alias rd="cd ~/Documents/Programming/r-d && git status"

clear
echo HELLO!
echo Try using commands "main" or "rd". "notepad ~/.bashrc" for details on these aliases.
