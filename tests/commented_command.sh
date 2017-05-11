echo "testing commented commands "
zeo="ls # list all files "
fir="#"
sec="ls && echo END OF LIST #it really the end"
thi="echo a comment # how do you do?"
fou="#fourth time the charm"
fif="######################## nothing but pound"
six="#comment between co##ments"
sev="echo hi || #i forgot; the right side" 
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
    