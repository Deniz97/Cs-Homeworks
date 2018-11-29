toCheck a b l h  = [(x,y) | (x,y) <-  [(a,b+1),(a+1,b+1),(a+1,b),(a+1,b-1),(a,b-1),(a-1,b-1),(a-1,b),(a-1,b+1)], x>=0 && y>= 0 && x<l && y<h]

--countW xs a b =  (filter(=="B") [xs!!x!!y | (x,y) <- toCheck a b] ) 

countB  xs a b =  (filter(=="B") [xs!!x!!y | x<-[0..100], y<-[0..100], (x,y) `elem` toCheck a b (length xs) (length (xs!!0)) ] ) 


infect xs (a,b) = length (countB xs a b) +1 

lala = [["W","W","W"],["W","B","W"],["B","B","W"]]