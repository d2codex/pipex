# pipex

## MANDATORY PART

My Pipex program aims to emulate the basic behavior of shell piping, within
defined boundaries.  Specifically, it mimics the following shell command:

`< infile cmd1 | cmd2 > outfile`

The program must take exactly 5 arguments

`./pipex infile cmd1 cmd2 outfile`

## What does it do?
* Reads from the infile
* Depending on the command, it executes cmd1
	* For commands such as `cat` or `grep`, it will read the contents of the
	 infile and use them as input to the command.
	* For commands like `ls -l` or `echo` it will ignore the infile and run
	 the command as it normally would.
* Pipes out the output of cmd1 as input to cmd2
* Writes the final output of cmd2 to outfile 

## So, what do I mean by defined boundaries?

In order to implement Pipex, one must understand the relationship between
Shell and the user input string (argv/argc).

Here is a little allegory to illustrate what is happening before the program is
even run.

The program to be run as per user input from the command line interface (CLI)
is as follows:

`./pipex infile "grep hello" wc\ -l outfile`

    Here is how the story starts ... 

It was a dark and stormy night at the house located at `./pipex`.
The Parent, a clever but lazy soul, was busy preparing for a big project that
needed finishing - and she knew she couldn't do it alone.  So she hired
contractors, and one by one they started arriving at her doorstep.

First came `"grep hello"`, clutching a file labeled `infile` tightly in his hands.
The butler, Bash opened the door, despite the rain pouring down.

"Welcome Mr. Grep," Bash said with a nod. "Before you come in, please remove
your quotes - it's quite warm inside and we wouldn't want you to overheat."

Grep peeled off his protective quotes and handed them to Bash. `grep hello`
then stepped through the door.

The next vistor, `wc\ -l` arrived with his outfile in hand.  He had left his
house in a hurry and so had forgotten his overquotes and was soaking wet.  

"Good evening Mr. wc," Bash greeted.  But just as wc was about to step through
the door, Bash spotted the weapon `\`, an 8mm pistol.  With no quotes to conceal
his `\`, Bash politely demanded the weapon.

"I'm sorry sir," Bash said firmly, "but there are children in the house.  For
their safetly, you must leave your `\` behind." He lowered his voice to a mere
whisper and added, "Unless there's been a `kill` order from the Parent."

There was none, so wc reluctantly handed over his `\`. If the child he's working
with must be disciplined, he will just have to order a `timeout` instead. So
`wc -l` stepped through the door.

	To be continued ...

So what can we tell from this story?  Well, before your program is even run,
the shell (in this case my Bash) parses the input, stripping the double quotes
and escapes.  Once bash handles the "visitors" and before letting them go into
the house (running the program) this is what `./pipex` sees:

	infile grep hello wc -l outfile

In your argv table, you now have:

 argv[0] | argv[1] | argv[2] | argv[3] | argv[4] |
|:--------:|:--------:|:--------:|:--------:|:--------:|
|./pipex  | infile  |grep hello | wc -l   |outfile  |

## Do I need to handle quotes?

Consider: 
`"grep 'hello world'" ` or `'grep "hello world'"`

A simple test using `echo` will show you what bash removes.

`echo "grep 'hello world'"`
gives
`grep 'hello world'`

and

`echo 'grep "hello world"'`
gives
 `grep "hello world"`

But what happens if we have something crazy like

`echo "gr"ep" 'hello wor"ld"'"`?

we get `grep 'hello world'`

This has something to do with the way bash concatenates adjecent strings.
But I won't get into that.

In a nutshell, what you need to know is that bash is parsing your string 
before your pipex program executes and whatever is handed to your pipex
is what you need to parse. 

## What about escapes?
We also see that bash handles the escapes, removing `\` when they are not
wrapped around quotes.

`wc\ -l` becomes `wc -l`

But if we have something like `"grep 'hello\ world'"` we get
`grep 'hello\ world'`
Here, backslashes are not interpreted inside single quotes.
The same goes for backslashes in double quotes.
This is outside the scope of pipex and thus is not required by the subject.
But it's not a bad idea to keep that in mind, as you will see this later in 
minishell.

## You only need to handle 1 pipe, so what's the deal with the loop?
To prepare for the bonus part, which handles multiple pipes, I decided to
process the commands in a single function in a loop, instead of hard-coding it.
There is a bit more complexity to this method, but overall, it is scalable.

## To open or not to open?... in the parent
Opening in the child process was much simpler for me.  When an fd is opened
in the parent all children will inherit it and that means there's more tracking
to be done in order to close them.

## Do I need to handle absolute or relative paths?
Consider `./pipex infile /bin/ls cmd2 outfile`

The equivalent shell command is `< infile /bin/ls | cmd2 > outfile`
Bash will pass `/bin/ls` to pipex as the command. All we need to do is treat
it as a direct path.

## BONUS
*documentation in progress*

*Disclaimer*
*This project and it's documentation reflect my perosnal understanding and
interpretation of the pipex project.  Although I have tried to ensure accuracy,
there may be errors or gaps in my understanding. Constructive feedback and
corrections are appreciated.*

*In addition, if you are working on this project, what you decide to handle or
not handle is entirely up to your discretion, but be ready for explanations and
evidence for your evaluator if they don't agree with you.*
