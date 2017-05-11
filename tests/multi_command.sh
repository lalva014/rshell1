#!/bin/bash

echo "testing multi-commands "
zeo="ls || ls || ls "
fir="ls && ls || ls "
sec="ls; ls; ls"
thi="ls || ls || echo LA; clear"
fou="ls || echo hi && echo 45 && pie || echo LA"
fif="mkdir hello && mkdir hello || mkdir hello; rmdir hello "
six="ls -a; echo hello; echo bye && echo when: echo later"
sev="&& echo hello || echo bye && ls" 
eig="|| ls -a || echo 8 && echo when"
nin="ls -a; echo 9 && echo 9.9"
ten="ls; ls; ls; ls; ls"
ele="echo marco; echo hello && ls; echo end; clear" 
twl="echo hello || echo fail"
thr="s || echo true && ls; echo hello"
a="git status || echo hand; ls; ls; echo being && echo end"
b="ls && echo hello; echo end && ls -a; echo bye"
c="ls || ls || ls || ls || ls || ls && echo end"
d="ls && ls && ls && ls && echon end"
e="echo being; ls && ls && ls || ls && echo end; ls || ls || echo end"
f= "ls; ls; echo hello && echo bye; echo be || echo end"
t= "echo got phone ? || echo no ; echo yes ; echo ls; echo or;"
q= "echo and ; echo or; echo ;"
u= "echo and || echo no" 


    echo $zeo
    eval $zeo 
    
    echo $fir
    eval $fir
    
    echo $sec
    eval $sec
    
    echo $thi
    eval $thi
    
    echo $fou
    eval $fou
    
    echo $fif
    eval $fif
    
    echo $fif
    eval $fif
    
    echo $six
    eval $six
    
    echo $sev
    eval $sev
    
    echo $eig
    eval $eig
    
    echo $nin
    eval $nin
    
    echo $ten
    eval $ten

    echo $ele
    eval $ele
    
    echo $twl
    eval $twl
    
    echo $thr
    eval $thr
    
    echo $a
    eval $a
    
    echo $b
    eval $b
    
    echo $c
    eval $c
    
    echo $e
    eval $e 
    
    echo $f
    eval $f
    
    echo $t
    eval $t
    
    echo $q
    eval $q
    
    echo $u
    eval $u