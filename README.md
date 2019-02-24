# Turing Machine Simulator

### This is a Simulator for a Turing Machine with 2 Tapes written in C

Turing Machine Description:
``` 
3
S0 S1 S2
1
S2
S0
9
S0 a a S0 a H a R
S0 a b S0 a H b R
S0 b a S0 b H a R
S0 b b S0 b H b R
S0 a # S1 a H # H
S0 b # S1 b H # H
S1 a # S1 # R a R
S1 b # S1 # R b R
S1 # # S2 # H # H
#abab#
#bbba#
```
Result:
```
##bbbaabab##
```
*Note: There will be more "#" characters in the output file.* 

### How to run:

Type the Turing Machine description in a file named "input"(there is one already in the repository) and run the script "run.sh".
The result will be written in a file named "output".
