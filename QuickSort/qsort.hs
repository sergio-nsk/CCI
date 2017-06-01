qsort [] = []
qsort (x:tail) = qsort [y | y <- tail, y < x] ++ [x] ++ qsort [y | y <- tail, y >= x]

main = do
    print(qsort([3, 7, 2, 8, 1, 9, 0, 10, 5, 5, 4]))

// Run it: runhugs qsort.hs
// Or: runhaskell qsort.hs
