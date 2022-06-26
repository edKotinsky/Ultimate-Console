<h1>Ultimate Console</h1>
<p>CLI with commands, options, arguments and variables, working on callback functions and references</p>

<h3>What is it for?</h3>

<p>This library provides simple command interface to program. This interface
consists of commands, options, arguments and variables.</p> 

<h3>Details, please?</h3>

<p>The commands are the lists of options and arguments, they also have names 
and the callback functions. Options in fact are the wrapper for references to 
variables, which provide interface for its changing. They have long string 
names and short one character names - keys. Arguments are also wrapper for 
references, but they have not names. Instead this they are stored in a command 
in certain order.</p>

<p>As commands are lists of options and arguments, they must be passed before them. 
So it seems like this: command option argument. Here "command" is a command name, 
"option" is an option name, and argument is a word, which may be a character string 
or a number or something else.</p>

<p>In this moment I'll explain, what are the variables. If a command contains options 
and arguments and has a name and a callback, variable contains only one argument, which 
only acts as a wrapper for reference. Variable syntax seems like: 
    variable = value</p>

<p>As said below, option has two names: long string and short one character key. 
Short name is not necessary. Option long name always starts with two dashes: 
    --option 
Option short name starts with one dash: 
    -o</p>

<p>Option can require the value to pass to stored variable or can not. 
If option does, this value passes to it like this: 
    --option = value 
Or with option short name: 
    -o value</p>

<p>Argument, as said below, does not have any name. But it located in certain order. 
This means, if in the list an argument with int type of reference are located before 
an argument with string type of reference, this notation are valid: 123 abc, and this 
are not: abc 123.</p>

<p>So the command syntax is: 
    command [--option[=value]] [-key [value]] [argument]; 
In square brackets are located optional parts. Arguments can be located in any place 
after command name.</p>

<p>Semicolon in the end of the notation is not necessary, if you are sure, that there 
will be any EOL or EOF symbol. Otherwise semicolon separates command. When disassembler 
gets symbol, which is a end-of-a-line symbol, it calls command callback, completes execution 
and returns a result. So this is important. Valid end-of-a-line symbols are: \0, \n, ; </p>

<p>In the end about valid characters. Command names can consists of a-z, A-Z and a dash -. 
Option and variables are the same. Key is always one letter character. String values can 
contain space, if they are enclosed in quotation marks.</p>

<h3>What for is you done it?</h3>
<p>This is my hobby project, I did it just because I want. I don't suppose that somebody 
will use this.</p>

<h3>Your English is bad</h3>
<p>Yes, I know.</p>