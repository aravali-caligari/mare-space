---
applyTo: "*.md"
---
# Language Parsing guideline for the markdown code blocks

- The language blocks labeled as "mud" contain legacy softcode code snippets.
- This softcode is used for a server-side game engine that has a Space Simultation embedded within it.
- The softcode syntax includes commands, attributes, and object definitions specific to the game engine.
- When parsing or analyzing these code blocks, treat them as legacy softcode and apply relevant parsing rules for MARE/MUSE/MUSH softcode.
- The markdown section named 'Attribute Definitions' contains the definitions of attributes used in the softcode.
  - Each attribute in the 'definitions' section is defined with its name followed by a colon a list of attribute types.
- The markdown section named 'Attribute list' contains the actual attribute values for the object.
  - Each attribute in the 'list' section is defined with its name followed by a colon and its corresponding value.
  - Values may include commands, text, or references to other objects or attributes.
  - Any value starting with a dollar sign ($) indicates a command or program to be executed by its name that a player can invoke.
  - The $ values can contain wildcards and patterned matched until the next : character.
  - Anything named '@pemit %#=<some text>' can be abbreviated to 'print <some text>' in the converted MARE2 code style.
  - Anything that looks like ':/[get(me/Eng)]/ is referring to a 'locking' test to see if a player can activate that command. Any locking that that fails will prevent the command from being executed.
  - The @ symbol is used to denote specific commands or actions within the softcode.
  - Anything inside brackets [] is a substituition section that will be replaced by the results of the inside function.
  - Anything that looks like 'v(0)' is referring to a variable that is being passed into the command or function. Anything that looks like '%1' is also referring to a variable that is being passed into the command or function.
  - Anything that looks like 'get(me/Eng_Man)' is referring to getting the attribute of an object, in this case the object that is running the command (me), and its attribute name.
  - Semicolons (;) are used to separate multiple commands or actions within a single attribute value.
  - Many '@commands' are native commands of the MARE/MUSE/MUSH softcode language, such as @pemit, @wait, @swi, and @force.
  - Braces '{}' are used to group commands or actions together and typically used as part of a conditional statement like '@swi' (i.e. switch).
  - Some function names and command '@' names are referring to custom functions or attributes definted elsewhere in the softcode.
  - The 'get(me/us)' is referring to getting the attribute 'us' of the object running the command (me). 'us' is an attribute that refers to the Space Ship object that the console is part of.
  - An example like '@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1))' means this: Get the absolute value of the first variable passed into the command (%1), then subtract that from the current power generation value of the Space ship object related to the console running the command (me/us), and set that as the new power generation value of the space ship object part of the console running the command (me/us).
  - A switch statement (@swi) is similar to an if-else statement, where it checks a condition and executes different commands based on whether the condition is true or false. This example: @swi get(me/PwrBatt)=*Damaged*,{@pemit %0=Batteries are damaged.},*Destroyed*,{@pemit %0=Batteries are destroyed.},{@swi %[comp(sub(get(me/MaxBatt),1),add(get(me/PwrBatt),abs(%1)))%]=-1,{@pemit %0=Batteries cannot be charged to that potential.},{@pwrbatt me=add(get(me/pwrbatt),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Batteries.} means this: Check the power battery status of the console (me). If it has the wildcarded keyword of 'Damaged', emit a message to the player saying "Batteries are damaged.". Otherwise, check if adding the absolute value of the first variable passed into the command (%1) to the current power battery value would exceed the maximum battery capacity minus 1. If it would exceed, emit a message saying "Batteries cannot be charged to that potential." Otherwise, increase the power battery value by the absolute value of %1, decrease the power generation of the related space ship object (me/us) by the same amount, and emit a message saying "Power Allocated to Batteries." 
  - Any function may be a native function or a custom function defined on an attribute with the attribute flag: 'function' and will have an attribute list name like: evalfuel()
  - The 'program' attribute flag indicates that the attribute is a program that can be invoked by players or other objects.
  - The 'inherit program' flag indicates that the attribute is inheriting a program from a parent object or prototype.
  - Any command that starts with '!' sign is a space sim specific command and not a native MARE/MUSE/MUSH command.
  - The 'me' keyword refers to the object that is executing the command.
  - The 'us' keyword refers to the space ship object that the console is part of.
  - The @wait command is used to introduce a delay before executing the next command.
  - Any function or command that references #-1 is a return value indicating an error or invalid state.
  - Any function or command that returns a positive value # is a valid object reference.
  - Any space-related softcode attribute named 'eng_man' or something similar is referring to the engineering console manning attribute that contains the object reference of the person or object manning that console.
  - Anything named %R is a carriage return character.
  - The 'spc(1)' function returns a single space character.
  - The 'first()', 'rest()', and 'mid()' functions are used for string manipulation, extracting specific parts of a string based on position.
  - Anything function that looks like a color name (Red, Green, Blue, Yellow, Cyan, Magenta, White, Black) is returning the corresponding ANSI color code for that color.
  - The '@tr' command is used to trigger another attribute or program on the object referrenced (example: @tr me/doneturn means to trigger the 'doneturn' attribute on the current object (me)).
  - The '@foreach' command is used to iterate over a list of objects or values, executing a block of code for each item in the list.
  - The space-sim function that looks like 'dg2rd()' is converting degrees to radians.
  - Any string of text that is not bracketed and not '$' and not '!' and not starting with '@' is treated as literal text to be emitted or displayed to the player.
  - Any command named '@fo' or '@force' is a force command that forces the execution of the following commands on another object regardless of locking or conditions.
  - The file named 'legacy_MARE_helptext.html' contains additional help text and documentation about the legacy MARE softcode commands and functions.
- The goal of the above guidelines is to ensure accurate parsing and understanding of the legacy softcode within the markdown files, enabling effective analysis, modification, or execution of the code in the context of the MARE/MUSE/MUSH game engine. 
- Another goal is to convert the legacy softcode into a more modern MARE2 code style with improved readability while preserving the original functionality and logic of the code.
- The chat questions about these code blocks should focus on understanding, analyzing, or modifying the legacy softcode within the context of the MARE/MUSE/MUSH game engine and space simulation functionalities.
- The syntax described in the file 'TinyMARE II help documentation.md' refers to new MARE2 softcode syntax and is the desired syntax of the converted legacy softcode.
- When converting the legacy softcode to the new MARE2 code style, ensure that the indentation and line breaks are applied consistently to enhance readability while maintaining the original logic and functionality of the code.
- The converted softcode also refers to legacy space-sim functions and commands that should be converted to equivilant MARE2 space-sim functions and commands where applicable. The new Space-sim is commonly referred to as 'SpaceMARE'. The conversion instructions and hints for space-sim to the new MARE2 Space Sim is detailed in the file 'README.legacy.conversions.md'.
- A chatprompt will be given that says 'analyze the attribute list code and provide an english description of what the code does' and the response should be a detailed english description of what the code is doing. Place the description in a markdown code block and reference the original attribute name.
- I will be modifying the english description to the actual logic description as I understand it. A chatprompt will be given that says 'convert the attribute list code using the english description as hints on how to convert to new MARE2 code style with improved readability' and the response should be the converted code with proper indentation and line breaks for readability while preserving the original functionality and logic of the code. Place the converted code in a markdown code block and reference the original attribute name.
- When converting, if statements do not use braces {} for the code blocks, instead use indentation to denote code blocks, and the keywords 'else' and 'endif' to denote the end of the if-else statement.
- The @emit and "@pemit %#=" commands are converted to @emit and "print" in the new MARE2 code style.
- Any syntax that looks looks like get(s([v/us)]/vismult)) is converted to get(v(us),vismult) in the new MARE2 code style.
- In the converted MARE2 code syntax, any command with an '=' sign does not have spaces around the '=' sign.
- In the converted MARE2 Code syntax, any command with a comma ',' used to separate multiple commands does not have spaces after the commas.
- In the converted MARE2 code syntax, comments are denoted by the '@@' string at the beginning of the line.
- In the converted MARE2 code, the @pemit and @echo commands do not use quotation marks around the text to be emitted.
- Any mention of @tr in the legacy code is converted to 'call' in the new MARE2 code style. - Example: @tr me/autohelp2=abc becomes: call me/autohelp2=abc@
- Any mention of @swi or @switch in the legacy code is converted to 'switch' statements in the new MARE2 code style - Example: @swi condition,{code block1},{code block2} becomes:
switch expression_to_evaluate
  case expression1
    code block1
  case expression2
    code block2
  default
    code block3
endswitch
A specific example then is:
```mud
@swi get(me/PwrBatt)=*Damaged*,{@pemit %0=Batteries are damaged.},*Destroyed*,{@pemit %0=Batteries are destroyed.},{@pemit %0=Batteries cannot be charged to that potential.}
```becomes:
```mud
@@ Check battery status
switch get(v(me),PwrBatt)
  case *Damaged*
    print Batteries are damaged.
  case *Destroyed*
    print Batteries are destroyed.
  default
    @@ Check if charging exceeds maximum capacity
    print Batteries cannot be charged to that potential.
endswitch
```

- Any mention of @wait in the legacy code is converted to 'wait' in the new MARE2 code style - Example: @wait 10=code block becomes: 
  wait 10
  codeblock
- Any mentions of @foreach in the legacy code is converted to 'foreach' in the new MARE2 code style - Example: @foreach v(0)=code block becomes:
  foreach v(0)
    code block
  endforeach
- In the converted MARE2 code, a comparision of two values (e.g., v(us) and 5) is spelled as v(us)=5 and not v(us)==5. Spaces are ommited around the '=' symbol.
- In the converted MARE2 code, the $command at the beginning of the attribute value is re-arranged to be after the locking test and the number of star wildcards in the original parameter match pattern. Example:
    $cloak *=*:/[v(us)]/@echo Cloak activated. , becomes: :/[v(us)]/2$cloak:@echo Cloak activated.    Because there are 2 star wildcards in the original parameter match pattern.
- In the new MARE2 code style, the $command definition was changed to now have a number before the '$'. This number before the $ controls the pattern of parameters allowed and the meaning of the v(0) through v(9) functions. The number has these allowed values and their meaning: 0=no parameters, 1=exactly one parameter, 2=one parameter with an equal sign followed by exactly one more parameter, 3=One parameter with an equal sign following by 2 or more parameters (upto 9) sperated by commas. Examples of $ patterns then is: 1$command_name:@echo First parameter [v(0)]. 2$command_name:@echo Param1 is [v(0)] and Param2 is [v(1)]; 3$command_name:@echo Param1 is [v(0)], Param2 is [v(1)], Param3 is [v(2)], and optionally more params allowed up to v(9). The user would be allowed to type commands like: 1=command_name *, 2=command_name *=*, 3=command_name *=*,*,etc. A more detailed example then is: 1 could mean: cloakon status, 2 could mean: cloakon passkey=1234, 3 could mean: cloakon setpasskey=oldpass,newpass.
- The new MARE2 code style uses the 'exit' keyword to exit a command early.
- The new code style must include the locking test at the beginning of the command after the $command definition and before the carriage return and rest of the code.
- In the converted code, when a parameter is a literal (e.g., passkey), make sure new code is inserted to validate the first parameter after the command is the expected word, else emit an error message and return.

- Example: Conversion of the 'cloak_on' attribute on the 'Cloak Parent' object that is similar to $cloak_on passkey=*:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}} becomes:
```mud
&cloak_on cloak parent=:/[v(eng_man)]/2$cloak_on:
@@ Validate the first parameter to be 'passkey'
if v(0)=!passkey,
    print Invalid syntax. Use: 'cloak_help'
    exit
endif
@@ Check if cloaking device is already on
if get(v(us),vismult)=-1
    print Cloaking device already on.
    exit
endif

@@ Validate the provided passkey
if v(passkey)=00[v(1)]
    @vismult v(us)=-1
    @emit Cloaking device engaged.
else
    print Invalid cloak passkey.
endif
```

- Edit the beginning of each line in the attribute list section to re-arrange it, example:
"get_obj_size(): ", to become like: "&get_obj_size() <Name of Object>=", in this example the name of the object is missing and should be filled in with the actual object name.
- Put one blank line between each converted attribute for redability.

