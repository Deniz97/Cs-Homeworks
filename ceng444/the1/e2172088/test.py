import main

def doTest(inp):
    print("---------")
    print()
    print("Input: ")
    print(inp)
    print()
    print("Output:")
    main.main(inp)
    print()

print("COMPILER ERRORS: ")
#right operand errors
doTest("foo = 5 + ; \nreturn 0;")
doTest("foo = 5 - bar + (7 * baz / );\nreturn 0;")
#left operand errors
doTest("foo = + 5;\nreturn 0;")
doTest("foo = 5 + ( * baz );\nreturn 0;")
#right parenthesis errors
doTest("foo = ( 5 ;\nreturn 0;")
doTest("foo = ( 5 + ( baz );\nreturn 0;")
#left parenthesis errors
doTest("foo =  5 );\nreturn 0;")
doTest("foo =  5 ) + ( baz );\nreturn 0;")
#missin ';' errors
doTest("foo =  5 \nreturn 0;")
doTest("if 0 < 1 \n\tfoo=5; \nendi \nreturn 0;")

print("WARNINGS:")
doTest("foo =  5;")
doTest("fun f(a,b,c=1)\n\tfoo=5;\nendf\nreturn 1;")
doTest("fun f(a,b,c=1)\n\tfoo=5;\nendf")


print("RUNTIME ERRORS:")
doTest("foo =  5;\nfoo = bar + 5;\nreturn 1;")
doTest("foo =  5;\nfoo = func(1,2,3) + 5;\nreturn 1;")
doTest("fun func(a,b,c=1,d=2)\n\treturn a+b+c+d;\nendf\nreturn func(1);")
doTest("fun func(a,b,c=1,d=2)\n\treturn a+b+c+d;\nendf\nreturn func(1,2,3,4,5);")
doTest("fun func(a,b,c=1,d=2,e)\n\treturn a+b+c+d;\nendf\nreturn func(1,2,3,4,5,6);")

print("LEXICAL ERRORS: ")
doTest("_foo = 5;")
doTest("foo = 5.;")
doTest("foo = .5;")
doTest("fun _func(a,b,c=1,d=2)\n\treturn a+b+c+d;\nendf\nreturn func(1,2);")
doTest("if 5 != 5\n\treturn 5;\nelse if 5~=3\n\treturn 5;\nendi;")

print("COMMENTING: ")
doTest("foo = 5; #Parser wont see this\n#Nor This\nbar = 6; #Nor this\n#Not even this")

