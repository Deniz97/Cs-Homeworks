--answer 1me
answer1 = sum [a | a<- [1..1000-1], mod a 3 == 0 || mod a 5 == 0 ]

--answer2
answer2 a b  | a>4000000= []
                | otherwise =  [a] ++ answer2 b (a+b)
bom =sum [x | x <- answer2 1 2, even x]

--answer3

sieve x xs 
        |  x*x>600851475143  = []
        | (not (0 `elem` map (mod x) xs) && (mod 600851475143 x) == 0  )=  [x]++ (sieve (x+2)  ([x]++xs))
        |otherwise = sieve (x+1) (xs)


--answer4

revers 0 x = x  
revers a b =  let (pa, pb) = a `quotRem` 10 in revers pa (10*b+pb)

answer4 =  maximum ( [x | y<-[100..999] , z<-[100..999],  let x=y*z, x==revers x 0 ]  )

--ODEV

toCheck a b w h = [(x,y) | (x,y) <-  [(a,b+1),(a+1,b+1),(a+1,b),(a+1,b-1),(a,b-1),(a-1,b-1),(a-1,b),(a-1,b+1)], x>=0 && y>= 0 && x<h && y<w ]

countW xs a b w h = length (filter(=="B") [xs!!x!!y | (x,y) <- toCheck a b w h ] ) 

cases c  "B" |c==2 || c==3 = "B" | otherwise = "W"
cases c "W" | c==3 = "B" | otherwise = "W"

helper xs ys x = [(cases c isAlive) | y<-[0..(length ys)-1], let c = countW xs x y (length ys) (length xs), let isAlive =ys!!y]

next xs = [helper xs ys x | (ys,x) <-zip xs [0..(length xs)-1]]

lala = [["B","W","B"],["W","B","B"],["W","B","B"],["B","B","W"],["W","W","B"],["W","W","B"],["W","W","B"],["B","B","B"],["W","B","W"],["B","B","W"],["B","B","W"],["W","B","W"],["B","W","B"]]

