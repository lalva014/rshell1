echo "testing exit command"
zeo="exit"
fir="ls exit"
sec="ls && ls || echo hello exits"
thi="echo bye exit"
fou="echo bye; exit"
fif="######################## nothing exit pound"
six="clear; exit"
sev="" 
eig="s || s || echo la # PRINTS ONLY: la"
nin="ls -a # echo 9 && echo 9.9"



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
    