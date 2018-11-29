# Generated from mygram.g4 by ANTLR 4.7.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .mygramParser import mygramParser
else:
    from mygramParser import mygramParser

# This class defines a complete generic visitor for a parse tree produced by mygramParser.

class mygramVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by mygramParser#prog.
    def visitProg(self, ctx:mygramParser.ProgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#stmt.
    def visitStmt(self, ctx:mygramParser.StmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#defin.
    def visitDefin(self, ctx:mygramParser.DefinContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#plist.
    def visitPlist(self, ctx:mygramParser.PlistContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#idargs.
    def visitIdargs(self, ctx:mygramParser.IdargsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#clist.
    def visitClist(self, ctx:mygramParser.ClistContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#args.
    def visitArgs(self, ctx:mygramParser.ArgsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#stmts.
    def visitStmts(self, ctx:mygramParser.StmtsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#ret.
    def visitRet(self, ctx:mygramParser.RetContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#iff.
    def visitIff(self, ctx:mygramParser.IffContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#elsee.
    def visitElsee(self, ctx:mygramParser.ElseeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#wh.
    def visitWh(self, ctx:mygramParser.WhContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#io.
    def visitIo(self, ctx:mygramParser.IoContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#cond.
    def visitCond(self, ctx:mygramParser.CondContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#ass.
    def visitAss(self, ctx:mygramParser.AssContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#e.
    def visitE(self, ctx:mygramParser.EContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#t.
    def visitT(self, ctx:mygramParser.TContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by mygramParser#f.
    def visitF(self, ctx:mygramParser.FContext):
        return self.visitChildren(ctx)



del mygramParser