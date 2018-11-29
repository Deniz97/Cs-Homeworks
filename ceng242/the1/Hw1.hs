module Hw1 (next) where -- DO NOT CHANGE THIS

next :: [[String]] -> [[String]]
-- IMPLEMENT NEXT FUNCTION HERE --

toCheck a b w h = [(x,y) | (x,y) <-  [(a,b+1),(a+1,b+1),(a+1,b),(a+1,b-1),(a,b-1),(a-1,b-1),(a-1,b),(a-1,b+1)], x>=0 && y>= 0 && x<h && y<w ]

countW xs a b w h = length (filter(=="B") [xs!!x!!y | (x,y) <- toCheck a b w h ] ) 

cases c  "B" |c==2 || c==3 = "B" | otherwise = "W"
cases c "W" | c==3 = "B" | otherwise = "W"

helper xs ys x = [(cases c isAlive) | y<-[0..(length ys)-1], let c = countW xs x y (length ys) (length xs), let isAlive =ys!!y]

next xs = [helper xs ys x | (ys,x) <-zip xs [0..(length xs)-1]]

lala = [["B","W","B"],["W","B","B"],["W","B","B"],["B","B","W"],["W","W","B"],["W","W","B"],["W","W","B"],["B","B","B"],["W","B","W"],["B","B","W"],["B","B","W"],["W","B","W"],["B","W","B"]]

-- DO NOT CHANGE CODE BELOW THIS LINE! --
createFile fileName = writeFile fileName ""

writeSteps filename grid n = do
                    createFile filename
                    writeStepsHelper filename grid n n
    where writeStepsHelper filename grid n all = if n == 0 then putStrLn ((show all) ++ " steps are succesfully written to \'" ++ filename ++ "\'") else do
                                    appendFile filename ((show (next grid)) ++ "\n")
                                    writeStepsHelper filename (next grid) (n-1) all