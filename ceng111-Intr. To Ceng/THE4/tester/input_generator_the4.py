#a messy random imput generator and a random tree generator with apporiate datums, for the4 exam

from os.path import abspath, join, dirname
from random import randint as rnd
import random
from the4 import help_michael as i_love_ozbalci
import time
import copy

#you are encouraged to play with below values to make better,more proper inputs
#first change the value on table below, then find and change the actual variable/place on the code

# maximum_depth = rnd(2,5)                  #maximum depth wanted for the tree
# (2 times)wp = rnd(5,28)*100               #wp vlue for randomly generated datums  (including micheal)
# cp = rnd(1,20)*100                        #cp value for randomly generated datums
# child_count = rnd(0,4)                    #child_count for each node generated #it makes sense to include 0
# mikes_money = rnd(20,150)*100 #micheal's saving money

def make_tree(uniq_check,maximum_depth=  rnd(2,5) ,tree = [["Micheal",0, rnd(5,28)*100 ]],depth=0 ):
    t = [tree[0][:]]
    
    
    #some poorly meshed-together code, just know that this sh*t returns a single human name
    def random_name_generator():

        full_path = lambda filename: abspath(join(dirname(__file__), filename))

        FILES = {
            'first:male': full_path('dist.male.first'),
            'first:female': full_path('dist.female.first'),
        }

        def get_name(filename):
            
            selected = random.random() * 90
            with open(filename) as name_file:
                for line in name_file:
                    name, _, cummulative, _ = line.split()
                    if float(cummulative) > selected:
                        return name

        def get_first_name(gender=None):
               
            if gender not in ('male', 'female'):
                gender = random.choice(('male', 'female'))
            return get_name(FILES['first:%s' % gender]).capitalize()

        return get_first_name()

    #datum generator for a single node
    def create_datum(uniq_check):    
            while True:
                name = random_name_generator()
                if not(name in uniq_check):
                    uniq_check.append(name)
                    return [name, rnd(1,20)*100 , rnd(5,28)*100   ]

    #actual function body
    if depth>maximum_depth:
        return t
    
    for i in range( rnd(0,4)  ):
        t.append([create_datum(uniq_check)])
    
    for i in range(1,len(t)):
        t[i]=make_tree(uniq_check,maximum_depth,t[i],depth+1)
    return t


def print_io():
    inputs=[]
    outputs=[]

    #print "50 input as no"," 50 as yes"," 100 as possible"
    checker_yes = 50
    checker_no = 50
    checker_poss = 100
    while  checker_poss>0 or checker_no>0 or checker_yes>0:
        mikes_money = rnd(20,150)*100
        tree = make_tree([])
        trii = copy.deepcopy(tree)
        ans = i_love_ozbalci(trii,mikes_money)

        if checker_yes > 0 and ans == "Yes":
            inputs.append([tree,mikes_money])
            outputs.append(ans)
            checker_yes -= 1
            #print checker_yes," yes left"
       
        elif checker_no>0 and ans == "No":
            inputs.append([tree,mikes_money])
            outputs.append(ans)
            checker_no -= 1
            #print checker_no," no left"
      
        elif type(ans)==list and ans[0] == "Possible":
            inputs.append([tree,mikes_money])
            outputs.append(ans)
            checker_poss -= 1
            #print checker_poss," possible left"

    print "inputs=",inputs
    print
    print
    print
    print
    print "outputs=",outputs

print_io()

