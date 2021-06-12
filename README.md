# EnderKnight-Programming-Language
Repository for the EnderKnight programming language 


## Syntax 

```
var world = "Hello World"
var number = 5
echo world
goto second_goto
echo "we be back c:"
math (1+2)*5


edef other_echo:
    echo "edef is awesome"
    math 25-50*3
    
    end_edef other_echo

edef second_goto:
    echo "this works c:"

    end_edef second_goto
    
```
* All functions are placed at the bottom of the program and require a end_edef statement.
* Variables use the var keyword.
* to execute, use in the terminal `python3 EnderKnight.py Whatever_Your_Ek_File_is.ek --run-with-errors(optional)`
* --run-with-errors forces the program to run even if it has errors

## Currently WIP
* if statements
* Porting to C++ or Rust(requires help from others)
