# EnderKnight-Programming-Language
Repository for the EnderKnight programming language 

## Instalation
Currently, the only pre-compiled binary is a exe for 64 bit Windows. For all versions, you just need to download the zip file called "C++ Compiler" and unzip it. If you're on Mac and Linux, you'll have to install a separate compiler(XMake for Mac, GCC for Linux), open the terminal, go to the main programming language folder(with a file called Makefile, and use the command make

## Syntax 

```
var world = "Hello World" 
var number = 5
echo world
echo 1+35(9/2+(9+8))
jmp second_goto
jmp other_echo

echo "we be back c:"
echo 5+1
edef second_goto:
    echo "second goto"
    if number = 5:
        echo "yay, if statements work c:"

    echo "NO IF STATEMENT"
    
edef other_echo:
    echo "other_echo"
    
```
* All functions are placed at the bottom of the program and require a end_edef statement.
* Variables use the var keyword.
* to execute, use in the terminal `EnderKnightShell "any ek file"`

## Currently WIP
* fixing bugs
