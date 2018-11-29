

class Node:
    def __init__(self, name, parent=None):
        self.name = name
        self.parent = parent
        self.children = []

        if parent:
            self.parent.children.append(self)


def print_tree(current_node, childattr='children', nameattr='name', indent='', last='updown'):

    if hasattr(current_node, nameattr):
        name = lambda node: getattr(node, nameattr)
    else:
        name = lambda node: str(node)

    children = lambda node: getattr(node, childattr)
    nb_children = lambda node: sum(nb_children(child) for child in children(node)) + 1
    size_branch = {child: nb_children(child) for child in children(current_node)}

    """ Creation of balanced lists for "up" branch and "down" branch. """
    up = sorted(children(current_node) , key=lambda node: nb_children(node))
    up = children(current_node) 
    l = len(up)
    down = up[l//2-1:]
    up = up[:l//2-1]
    #while up and sum(size_branch[node] for node in down) < sum(size_branch[node] for node in up):
    #    down.append(up.pop())

    """ Printing of "up" branch. """
    for child in up:     
        next_last = 'up' if up.index(child) is 0 else ''
        next_indent = '{0}{1}{2}'.format(indent, ' ' if 'up' in last else '│', ' ' * len(name(current_node)))
        print_tree(child, childattr, nameattr, next_indent, next_last)

    """ Printing of current node. """
    if last == 'up': start_shape = '┌'
    elif last == 'down': start_shape = '└'
    elif last == 'updown': start_shape = ' '
    else: start_shape = '├'

    if up: end_shape = '┤'
    elif down: end_shape = '┐'
    else: end_shape = ''

    print('{0}{1}{2}{3}'.format(indent, start_shape, name(current_node), end_shape))

    """ Printing of "down" branch. """
    for child in down:
        next_last = 'down' if down.index(child) is len(down) - 1 else ''
        next_indent = '{0}{1}{2}'.format(indent, ' ' if 'down' in last else '│', ' ' * len(name(current_node)))
        print_tree(child, childattr, nameattr, next_indent, next_last)


def tree(var, level=1, outstr=''):
	#Takes a var, prints it out as nested aligned list
	if var is None:
		#Just return a new line:
		outstr+=' \n'
	elif isinstance(var, (int, float, str, bool)):
		#Single value, simply add the fucker
		outstr+=' '+str(var)
		outstr+=' \n'
	elif isinstance(var, (list, tuple)):
		#List with some specified order, print in order
		outstr+='\n'
		k=0	#Manually index this
		for valchild in var:
			for tab in range(level-1):	# Print key
				outstr+='\t'
			outstr+='['+str(k)+'] => '
			k+=1	#Increment index
			newlevel = level + 1
			outstr = tree(valchild,newlevel,outstr)
	elif isinstance(var,(dict)):
		#List with keys and values, no order
		outstr+='\n'
		for k,valchild in sorted(var.iteritems()):
			for tab in range(level-1):	# Print key
				outstr+='\t'
			outstr+='['+str(k)+'] => '
			newlevel = level + 1
			outstr = tree(valchild,newlevel,outstr)
	else:
		#It doesn't qualify as any of the above cases
		outstr+=' '+str(var)
		outstr+=' \n'
	return outstr

def treeprint(var):
	#Wrapper for tree
	outstr = tree(var)
	print(outstr)
	return outstr	#Available to caller for wider use

def print_lisp(inp):

	inp = inp.replace("( (","( '('")
	inp = inp.replace(") )","')' )")
	inp = inp.replace(" "," , ")
	inp = inp.replace("(","( ")
	inp = inp.replace(")"," )")

	inp = inp.split()

	for index,e in enumerate(inp):
		if e!='(' and e!=')' and e!=',':
			inp[index] = '"' + e + '"'


	inp = " ".join(inp)

	inp = eval(inp)

	def lt(t,pn):
		for i in t[1:]:
			if type(i) == str:
				r = Node(i,pn)
			if type(i) == tuple:
				r = Node(i[0],pn)
				lt(i,r)

	root = Node(inp[0], None)
	lt(inp,root)


	print_tree(root)





if __name__ == '__main__':
	inp = "(prog (stmt (ass nana = (e (e (t (f 5))) + (t (f 7)))) ;))"
	print_lisp(inp)