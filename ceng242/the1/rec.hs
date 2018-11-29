-- Use GHCi for testing and debuging your programs

-- GHCi commands
-- :load 
-- :reload
-- :? (see list of available commands)
-- :t (examine types of functions and variables)

-- Resources you may refer while learning Haskelll
-- http://learnyouahaskell.com/chapters
-- haskell.org
-- Check Haskell tutorials pointed in http://www.ceng.metu.edu.tr/course/ceng242/documents


-- Variable declarations
a = 5
b = [1, 2, 3]


-- Functions
add::Integer->Integer->Integer
add x y = x + y

len :: [Integer] -> Integer
len [] = 0
len (x:xs) = len(xs) + 1

--Pattern Matching Examples
lucky 7 = "lucky"
lucky _ = "unlucky"

f::String->String
f "" = "0"
f all@(x:xs) = "First of " ++ all ++ " is " ++ [x] 

-- If Else Example

bmiTell weight height = if (weight / (height  ^ 2))  <= 18.5 then "underweight"
                                else if (weight / (height ^ 2 )) <= 25.0 then "normal"
                                     else if (weight / (height ^ 2 )) <= 30.0 then "overweight" 
                                          else "obese"


-- Case Example
head' :: [a] -> a  
head' xs = case xs of [] -> error "No head for empty lists!"  
                      (x:_) -> x  
					  
-- Where Example
bmiTellWhere weight height = if bmi  <= 18.5 then "underweight"
                                else if bmi <= 25.0 then "normal"
                                     else if bmi <= 30.0 then "overweight" 
                                          else "obese"
				where bmi = weight / height ^ 2

-- Let Example
cylinder :: (RealFloat a) => a -> a -> a  
cylinder r h = 
    let sideArea = 2 * pi * r * h  
        topArea = pi * r ^2  
    in  sideArea + 2 * topArea 

-- Guard Example
bmiTellGuard weight height | bmi <= 18.5 = "underweight"
			   | bmi <= 25.5 = "normal"
			   | bmi <= 30.0 = "over"
			   | otherwise = "obese"
			    where bmi = weight / (height ^ 2) 	


-- Defining our Own Data Types
-- Make sure that you understand what value constructors are
-- Examine result of the command ":info Shape" in the interpreter. 
data Shape = Circle Float | Rectangle Float Float


-- A function that works on our data type
-- Lack of paranthesis may generate errors.  ex: (Circle 3)

perimeter::Shape->Float
perimeter (Circle r) = 2*3*r
perimeter (Rectangle a b) = 2*(a+b) 

-- Type Constructors:  takes a type and constructs a new type
-- built-in example
-- data Maybe a = Nothing | Just a

safeSqrt::Float -> Maybe Float
safeSqrt n | n < 0 = Nothing
	   | otherwise = Just (sqrt n)


-- Define a recursive data type
data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show)

-- A function that works on our recursive data type
-- Find an element in the tree.
treeElem x EmptyTree = False
treeElem x (Node a left right)
		| x == a = True
		| otherwise = treeElem x right || treeElem x left 


-- Take Home Exercises
-- 1. Implement reverse function which reverses a list of floats. Your function should work for only floats.
-- 2. Implement len function with case expressions.
-- 3. Implement bmiTell function using let-in construct.
-- 4. Update Tree class so that the Tree type is in the Eq typeclass. As a result, you will be able to compare the trees with == operator. Example : EmptyTree == ( Node 2 EmptyTree EmptyTree)
-- 5. Examine result of the command ":info Shape" in the interpreter. 
-- 6. Examine result of the command ":info Tree" in the interpreter. 




