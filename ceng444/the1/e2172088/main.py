import sys
import io
from antlr4 import *
from antlr4.tree.Trees import Trees
import antlr4.error.ErrorStrategy as ES
import antlr4.error.Errors as er
from mygramLexer import mygramLexer
from mygramParser import mygramParser
from mygramListener import mygramListener
from mygramVisitor import mygramVisitor
import gui





#classes for function management during execution
class Function():
	def __init__(self, name, node , ids = [], defaults=[]):
		self.name = name
		self.node = node
		self.ids = ids
		self.defaults = defaults

class FunctionDict():

	def __init__(self):
		self.dict = {}
	def addFunc(self,name , node ,ids=[],defaults=[]):
		self.dict[name] = Function(name,node, ids,defaults)
	def addIds(self,name,ids,defaults=None):
		self.dict[name].ids += ids
		if defaults==None:
			self.dict[name].defaults += [False]*len(ids)
		else:
			assert len(ids) == len(defaults), "Should have same length"
			self.dict[name].defaults += defaults
	def getNode(self,name):
		return self.dict[name].node
	def getIds(self,name):
		return self.dict[name].ids
	def getDefaults(self,name):
		return self.dict[name].defaults
	def getZipped(self,name):
		return list(zip( self.getIds(name), self.getDefaults(name)  ))
	def funcExists(self,name):
		return name in self.dict
	def posArgCount(self,name):
		return len(  [ x for x in self.dict[name].defaults if x==False ]  )
	def printFuncs(self):
		print(self.dict)
funcManage = FunctionDict()
###

#data structure to hold variables and scopes
class VariableStack():
	def __init__(self):
		self.scope = [ ]
	def pushScope(self):
		self.scope.append({})
	def popScope(self):
		self.scope.pop()
	def varExists(self, var):
		return var in self.scope[-1]		
	def updateVar(self,var, val):
		self.scope[-1][var] = val
	def getVar(self,var):
		if not self.varExists(var):
			raise uninitializedVarException(var)
		return self.scope[-1][var]
	def printStack(self):
		print("printing stack")
		for s in self.scope:
			print(s)
		print("printing stack done")
stack = VariableStack()
###

#exception classes to be used during execution
class uninitializedVarException(Exception):
    def __init__(self,idd):
        message = "(Runtime) line %d:%d Variable '%s' used without initialization" \
                % ( idd.symbol.line , idd.symbol.column, idd.getText() )
        print(message)
        super().__init__(message)

class uninitializedFuncException(Exception):
    def __init__(self,idd):
        message = "(Runtime) line %d:%d Function '%s' called without definition" \
                % ( idd.symbol.line , idd.symbol.column, idd.getText() )
        print(message)
        super().__init__(message)

class generalException(Exception):
	def __init__(self, message):
		self.msg = message
		if message!= None:
			print(message)
#####

#a little modification to default error reporting behaviour:
def reportInputMismatch(self, recognizer:Parser, e:er.InputMismatchException):
    ctx = recognizer._ctx
    tokens = recognizer.getTokenStream()    
    t = e.offendingToken
    prog = tokens.getText()
    ti = t.tokenIndex
    
    if ti>0 and tokens.tokens[ti-1].type in [ 16,17,18,19,20 ]:
        msg = "binary operator '%s' has no right operand" % tokens.tokens[ti-1].text
    elif self.getTokenErrorDisplay(e.offendingToken) == "')'":
    	msg = "unmatching parenthesis, need '('"
    else:
        msg = "mismatched input " + self.getTokenErrorDisplay(e.offendingToken) \
          + " expecting " + e.getExpectedTokens().toString(recognizer.literalNames, recognizer.symbolicNames)
    recognizer.notifyErrorListeners(msg, e.offendingToken, e)

def reportMissingToken(self, recognizer:Parser):
    if self.inErrorRecoveryMode(recognizer):
        return
    self.beginErrorCondition(recognizer)
    t = recognizer.getCurrentToken()

    expecting = self.getExpectedTokens(recognizer)
    if expecting.toString(recognizer.literalNames, recognizer.symbolicNames) == "';'":
        msg = "missing ';' after statement (instead %s was found)" % self.getTokenErrorDisplay(t)
    elif expecting.toString(recognizer.literalNames, recognizer.symbolicNames) == "')'":
	    msg = "unmatching parenthesis, need ')' (instead %s was found)" % self.getTokenErrorDisplay(t)
    else:
    	msg = "missing " + expecting.toString(recognizer.literalNames, recognizer.symbolicNames) \
          + " at " + self.getTokenErrorDisplay(t)
    recognizer.notifyErrorListeners(msg, t, None)

def reportUnwantedToken(self, recognizer:Parser):
    if self.inErrorRecoveryMode(recognizer):
        return

    tokens = recognizer.getTokenStream()
    prog = tokens.getText()    
    t = recognizer.getCurrentToken()
    ti = t.tokenIndex
    typ = t.type
    
    
    self.beginErrorCondition(recognizer)
    tokenName = self.getTokenErrorDisplay(t)
    expecting = self.getExpectedTokens(recognizer)
    

    if  tokens.tokens[ti-1].type in [ 16,17,18,19,20 ]:
        msg = "binary operator '%s' has no left operand" % tokens.tokens[ti].text
    elif  tokens.tokens[ti].type in [ 16,17,18,19,20 ]:
        msg = "binary operator '%s' has no left operand" % tokens.tokens[ti].text
    elif tokens.tokens[ti].type == 5:
    	msg = "unmatching parenthesis, need '(' " 
    else:
        msg = "extraneous input " + tokenName + " expecting " \
        + expecting.toString(recognizer.literalNames, recognizer.symbolicNames)
    recognizer.notifyErrorListeners(msg, t, None)


ES.DefaultErrorStrategy.reportInputMismatch = reportInputMismatch
ES.DefaultErrorStrategy.reportMissingToken = reportMissingToken
ES.DefaultErrorStrategy.reportUnwantedToken = reportUnwantedToken

######


#checks for return statements(called first)
class returnVisitor(mygramVisitor):

	def aggregateResult(self, aggregate, nextResult):
		return aggregate or nextResult

	def defaultResult(self):
		return False

	# Visit a parse tree produced by mygramParser#prog.
	def visitProg(self, ctx:mygramParser.ProgContext):
		statements = ctx.stmt()

		for s in statements:
			res = s.accept(self)
			if res==True:
				return self.visitChildren(ctx)
		#else
		print("(warning) line 0:0 main body needs a return statement")
		return self.visitChildren(ctx)
	# Visit a parse tree produced by mygramParser#defin.
	def visitDefin(self, ctx:mygramParser.DefinContext):
		###check for return statement
		statements = ctx.stmts().stmt()

		for s in statements:
			res = s.accept(self)
			if res==True:
				return		
		#else
		print("(warning) line %d:%d function '%s' needs a return statement" % \
		 ( ctx.ID().symbol.line, ctx.ID().symbol.column , ctx.ID().getText() ) )

	# Visit a parse tree produced by mygramParser#ret.
	def visitRet(self, ctx:mygramParser.RetContext):
		return True

#discovers functions and push them in to function manager (called second)
class functionListener(mygramListener):     
	def exitDefin(self,ctx):
		#check for argument - default argument order 
		defaults_started = False
		temp = ctx.plist().idargs()
		params = temp.getChildren()
		for p in params: #this is very hacky, fix later
			if defaults_started and p in temp.ID():
				raise generalException("line %d:%d default parameters should follow positional parameters (in function '%s')" % \
			 ( p.symbol.line, p.symbol.column , ctx.ID().getText() ) )
				#raise Exception
			elif p in temp.ass():
				defaults_started = True

	def enterDefin(self,ctx):
		#put functions (names, nodes and arguments) to function manager
		name = ctx.ID().getText()
		node = ctx
		ids = []
		defaults = []    	
		for i in ctx.plist().idargs().ID():
			ids.append(i.getText())
			defaults.append(False)
		for i in ctx.plist().idargs().ass():
			ids.append( i.ID().getText() )
			defaults.append(True)
		
		funcManage.addFunc(name,node,ids,defaults)


#executes the actual program (called last)
class executionVisitor(mygramVisitor):
    def visitProg(self, ctx):
        stack.pushScope()
        for s in ctx.stmt():
        		res = s.accept(self)
        		if  res != None:
        			return res
        return None

    def visitStmts(self,ctx):
    	stmts = ctx.stmt()

    	for s in stmts:
    		res = s.accept(self)
    		if res!=None:
    			return res


    def visitRet(self,ctx):
    	return ctx.e().accept(self)

    def visitAss(self,ctx):
        var = ctx.ID().getText()
        
        res = ctx.e().accept(self)
        if res!=None:
            stack.updateVar(var,res)
        return None
        

    def visitE(self,ctx):
        if ctx.getChildCount() == 1:
            return self.visitChildren(ctx)
        if ctx.getChildCount() == 3:
            c = ctx.getChild(0)
            lhs = c.accept(self)
            c = ctx.getChild(2)
            rhs = c.accept(self)

            if ctx.getChild(1).getText() == "+":
                return lhs + rhs
            else:
                return lhs - rhs
        

    def visitT(self,ctx):
        if ctx.getChildCount() == 1:
            return self.visitChildren(ctx)
        elif ctx.getChildCount() == 3:
            c = ctx.getChild(0)
            lhs = c.accept(self)
            c = ctx.getChild(2)
            rhs = c.accept(self)

            if ctx.getChild(1).getText() == "*":
                return lhs * rhs
            elif ctx.getChild(1).getText() == "/":
                return lhs / rhs
            else:
                return lhs % rhs

    def visitF(self,ctx):
        if ctx.getChildCount() == 3: # f -> (e)
            return ctx.getChild(1).accept(self)
        elif ctx.getChildCount() == 2: #function call
            name = ctx.ID().getText()
            #recover ids, defaul values and args and push to scope
            
            if not funcManage.funcExists(name):
            	raise uninitializedFuncException(ctx.ID())
            
            ids = funcManage.getIds(name)
            defaults = funcManage.getDefaults(name)
            args = ctx.clist().accept(self)
            if len(args) > len(ids):
            	err_msg = "line %d:%d Function '%s' takes only %d arguments but %d were given" \
            		%(ctx.ID().symbol.line,ctx.ID().symbol.column, name ,len(ids),len(args))
            	raise generalException(err_msg)
            elif len(args) < funcManage.posArgCount(name):
            	err_msg = "line %d:%d Function '%s' takes %d positional argument but only %d were given" \
            		%(ctx.ID().symbol.line,ctx.ID().symbol.column, name ,funcManage.posArgCount(name),len(args))
            	raise generalException(err_msg)

            stack.pushScope()
            for i in range(len(args)):
            	stack.updateVar(ids[i],args[i])
            
        
            return funcManage.getNode(name).accept(self)
        elif ctx.getChildCount() == 1: #ID or Num
            if ctx.NUM() != None:
            	return eval(ctx.NUM().getText()) #security problem? Fix later (seperate lex rules for int and float?)
            if ctx.ID() != None:
            	var = ctx.ID().getText()
            	if not stack.varExists(var):
            		raise uninitializedVarException(ctx.ID())
            	else:
            		return stack.getVar(var)

    def visitDefin(self,ctx):    	
    	#push ids and default values in scope
    	name = ctx.ID().getText()
    	ids = []
    	defaults = []
    	for i in ctx.plist().idargs().ass():
    		if not stack.varExists( i.ID().getText() ):
    			stack.updateVar( i.ID().getText(),  i.e().accept(self) )
    	####
    	
    	##call the actual function
    	for s in ctx.stmts().stmt():
    		res = s.accept(self)
    		if res != None:
    			stack.popScope()
    			return res
    			
    	###

    def visitClist(self,ctx):
    	retval = []
    	for expr in ctx.args().e():
    		retval.append(expr.accept(self))
    	return retval

    def visitIff(self,ctx):
    	conds = ctx.cond()
    	stmts = ctx.stmts()
    	for i in range(len(conds)):
    		if conds[i].accept(self):
    			res = stmts[i].accept(self)
    			if res!=None:
    				return res

    	if "else" in ctx.getText(): ##very hacky, but for some reason ctx.elsee() does not return None
    		return ctx.elsee().accept(self)
    		

    def visitElsee(self,ctx):
    	stmts = ctx.stmts().stmt()
    	for s in stmts:
    		res = s.accept(self)
    		if res!= None:
    			return res

    def visitWh(self,ctx):

    	while ctx.cond().accept(self):

    		for s in ctx.stmts().stmt():
    			res = s.accept(self)
    			if res!=None:
    				return res

    def visitCond(self,ctx):
    	if ctx.getChildCount() == 2:
    		return not ctx.cond().accept(self)
    	elif ctx.getChildCount() == 3:
    		if ctx.Bop() != None:
    			lhs = ctx.getChild(0).accept(self)
    			rhs = ctx.getChild(2).accept(self)
    			bop = ctx.Bop().getText()
    			if bop=="<=":
    				return lhs <= rhs
    			elif bop=="<":
    				return lhs < rhs
    			elif bop==">=":
    				return lhs >= rhs
    			elif bop==">":
    				return lhs > rhs
    			elif bop=="==":
    				return lhs == rhs
    		elif ctx.Lop() != None:
    			lhs = ctx.getChild(0).accept(self)
    			rhs = ctx.getChild(2).accept(self)
    			lop = ctx.Bop().getText()
    			if lop=="and":
    				return lhs and rhs
    			elif lop=="or":
    				return lhs or rhs

    def visitIo(self,ctx):
    	if ctx.getChild(0).getText() == "input":
    		id_name = ctx.ID().getText()
    		inp = float(input("in: "))
    		if True: #check for bad input shape
    			stack.updateVar(id_name,inp)
    	elif ctx.getChild(0).getText() == "output":
    		print("out: ", ctx.e().accept(self) )



    def visitTerminal(self, node):
        return node.getText()

    def defaultResult(self):
    	return None


def main(argv):
    if type(argv) == str:
        lexer = mygramLexer(InputStream(argv)) 
    else:
        input = FileStream(argv[1])
        lexer = mygramLexer(input)
    stream = CommonTokenStream(lexer)
    parser = mygramParser(stream)
    tree = parser.prog()
    
    
    function_listener = functionListener()
    execute_visitor = executionVisitor()
    return_visitor = returnVisitor()
    
    #check for return statements
    return_visitor.visit(tree)


    try:
        if parser.getNumberOfSyntaxErrors() > 0:
        	raise generalException(None)
        #detect functions
        walker = ParseTreeWalker()
        walker.walk(function_listener, tree)
        #execute the program
        result = execute_visitor.visit( tree )
        print("Execution Result: ",result)
    except TypeError as e:
        print()
       	print("Could not finish execution. (Bad expression)")
    except (generalException,uninitializedFuncException,uninitializedVarException) as e:
        print()
       	print("Could not finish execution.")
    
    lisp_like = Trees.toStringTree(tree, None, parser)
    print()
    print(lisp_like)
    #if the given input does not contain function definition or function call
    #you can use the line below to pretty-print the output in a tree-like format
    # (i could not handle pretty print when the input includes a '(' or ')' )
    #print(gui.print_lisp(lisp_like))
    
 
if __name__ == '__main__':
    main(sys.argv)