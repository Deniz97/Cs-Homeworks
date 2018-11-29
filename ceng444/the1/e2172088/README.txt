-Deniz Rasim Uluğ
-2172088

Hello!

My homework consist of three parts:

-Grammer
-Error reporting
-Actual execution of the program

0) Usage:
	$python main.py [path]
	Example:
	$python main.py inputs/inp1.txt

	Use test.py to see my own examples containing errors. test.py only contains errors which I have manually handled to print a semantic error, plus some lexical errors.
	$test.py

	Well formed programs are in directory 'inputs', and their outputs are in the directory 'outputs'. The inputs to the programs, when one requires, is given 10.

1) Grammar

	Changes:
		- Original XPLN has to start with a statement. Our grammar can start with either a statement or a function definition.
		- Output statement can also output an expression.
		- assignment operator is "=", not ":=" (sorry, but i had to)

	Additions:
		- Added the binary modulo operator '%' with the same precedence as '*' and '/' (Cause every language should be able to find primes)
		- While function definitions should only include ID in their parameters, function call's arguments can contain expressions.
		- We also support "default parameters" with the following syntax:
			fun f(a,b,c=2,d=3)
		  But default parameters should follow positional parameters.
		- You can also use the prior parameters in the expression of a default parameter. Example:
			fun f(a,b,c=a*b)
		- Added single line comments with '#' keyword.
		- Added support for "else if" logic



	Unspecified by the cover grammar:
		- Floats should have numbers both left and right of the dot.




2) Error reporting

	Compile time errors (we implemented 5):
		- When an arithmetic binary operator lacks a right operand.
		- When an arithmetic binary operator lacks a left operand.
		- When ')' is found without a prior '('
		- When a statement lacks ')' after a '('
		- When a statement lacks ';'

		Notes: Instead of modifying the parser itself, we simply modified the error reporting behaviour of the antlr library (in main.py). All other errors can be handled this way. Tough it would be much cleaner and easier if the error reporting functions took local context as an argument (you can only access the global context in an error reporting function).

	After compile time and before runtime warnings:
		- When a function or the main body does not have a return statement (wether reachable or not)

		Notes: We implemented this with the visitor class "returnVisitor" in main.py
			   We also dont stop the execution for this.

	Runtime errors:
		- When a variable is used without initialization
		- When a function is used without initialization
		- When a function has more positional arguments than it is called with
		- When a function has less arguments (positional+default) than it is called with
		- When a function definition has a positional parameter after a default parameter.

		Notes: We throw an exception at the first such error and stop the execution.

3) Execution

	- All grammar specifications are fully supported.

	Notes: *To execute the program, we wrote an "executeVisitor" class. For every visit, we simply let python itself execute the statements.
		   * We use the class "VariableStack" to keep track of the variables and scopes
		   * We use the class "FunctionDict" to keep information about functions.
		   * Python handles everything else, again, we do not generate any intermediate code.
		   * Input ID prints "in: " to terminal.
		   * Output e prints "out: " to terminal.
		   * Final return is showed as "Execution Result: [value]"



Finally, there is gui.py. You can uncomment the final lines of main.py to pretty print the lisp tree. But this only works when the code does not have any '(' or ')' (don't ask why).

Take care.

