{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE EmptyDataDecls, MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances,
             InstanceSigs #-}
module RollTheBall where
import Pipes
import ProblemState
import qualified Data.Array as A

{-
    Direcțiile în care se poate mișca o piesa pe tablă
-}

data Directions = North | South | West | East
    deriving (Show, Eq, Ord)

{-
    Sinonim tip de date pentru reprezetarea unei perechi (Int, Int)
    care va reține coordonatele celulelor de pe tabla de joc
-}

type Position = (Int, Int)

{-
    Tip de date pentru reprezentarea celulelor tablei de joc
-}

data Cell = HorPipe | VerPipe | TopLeft | BotLeft | BotRight | TopRight | EmptySpace | EmptyCell | StartUp | StartDown
            | StartLeft | StartRight | WinUp | WinDown | WinLeft | WinRight | Endl | StartCells | WinningCells
            deriving (Eq, Ord)

{-
    Tip de date pentru reprezentarea nivelului curent
-}
data Level = Level { array :: A.Array (Position) Cell
                    , sPos :: Position
                    , fPos :: Position
                    , solution :: [Position]
                    , poswon :: Position
                    } deriving (Eq, Ord)

{-
    *** Optional *** 
  
    Dacă aveți nevoie de o funcționalitate particulară,
    instantiați explicit clasele Eq și Ord pentru Level.
    În cazul acesta, eliminați deriving (Eq, Ord) din Level.
-}

{-
    *** TODO ***

    Instanțiati Level pe Show. 
    Atenție! Fiecare linie este urmată de \n (endl in Pipes).
-}

instance Show Cell where
    show HorPipe = [horPipe]
    show VerPipe = [verPipe]
    show BotLeft = [botLeft]
    show BotRight = [botRight]
    show TopRight = [topRight]
    show TopLeft = [topLeft]
    show EmptySpace = [emptySpace]
    show EmptyCell = [emptyCell]
    show StartUp = [startUp]
    show StartDown = [startDown]
    show StartLeft = [startLeft]
    show StartRight = [startRight]
    show WinUp = [winUp]
    show WinDown = [winDown]
    show WinLeft = [winLeft]
    show WinRight = [winRight]
    show Endl = [endl]

instance Show Level where
    show (Level arr sPos fPos solution poswon) = (show Endl) ++ foldl (++) "" ([foldl (++) "" [(show (arr A.! (x ,y))) | y <- [0..(snd(snd(A.bounds arr)))]] ++ (show Endl) | x <- [0..(fst(snd(A.bounds arr)))]])


        
{-
    *** TODO ***
    Primește coordonatele colțului din dreapta jos a hărții.
    Intoarce un obiect de tip Level în care tabla este populată
    cu EmptySpace. Implicit, colțul din stânga sus este (0,0)
-}

emptyLevel :: Position -> Level
emptyLevel end = Level (A.array ((0, 0), end) [((x, y), EmptySpace) | x <- [0..fst end], y <- [0..snd end]]) (-1, -1) (-1, -1) [] (-1, -1)


{-
    *** TODO ***

    Adaugă o celulă de tip Pipe în nivelul curent.
    Parametrul char descrie tipul de tile adăugat: 
        verPipe -> pipe vertical
        horPipe -> pipe orizontal
        topLeft, botLeft, topRight, botRight -> pipe de tip colt
        startUp, startDown, startLeft, startRight -> pipe de tip initial
        winUp, winDown, winLeft, winRight -> pipe de tip final
    Parametrul Position reprezintă poziția de pe hartă la care va fi adaugată
    celula, dacă aceasta este liberă (emptySpace).
-}

addCell :: (Char, Position) -> Level -> Level
addCell (cell, pos) (Level arr sPos fPos x poswon)
    | (snd pos) < 0 || (fst pos) < 0 || (fst pos) > (fst (snd (A.bounds arr))) || (snd pos) > (snd (snd (A.bounds arr))) = Level arr sPos fPos x poswon
    | (arr A.! pos) /= EmptySpace = Level arr sPos fPos x poswon
    | (cell, pos) == ('║', pos) = Level (arr A.// [(pos, VerPipe)]) sPos fPos x poswon
    | (cell, pos) == ('═', pos) = Level (arr A.// [(pos, HorPipe)]) sPos fPos x poswon
    | (cell, pos) == ('╔', pos) = Level (arr A.// [(pos, TopLeft)]) sPos fPos x poswon
    | (cell, pos) == ('╗', pos) = Level (arr A.// [(pos, TopRight)]) sPos fPos x poswon
    | (cell, pos) == ('╚', pos) = Level (arr A.// [(pos, BotLeft)]) sPos fPos x poswon
    | (cell, pos) == ('╝', pos) = Level (arr A.// [(pos, BotRight)]) sPos fPos x poswon
    | (cell, pos) == ('┴', pos) = Level (arr A.// [(pos, StartUp)]) pos fPos x pos
    | (cell, pos) == ('┬', pos) = Level (arr A.// [(pos, StartDown)]) pos fPos x pos
    | (cell, pos) == ('┤', pos) = Level (arr A.// [(pos, StartLeft)]) pos fPos x pos
    | (cell, pos) == ('├', pos) = Level (arr A.// [(pos, StartRight)]) pos fPos x pos
    | (cell, pos) == ('╨', pos) = Level (arr A.// [(pos, WinUp)]) sPos pos x poswon
    | (cell, pos) == ('╥', pos) = Level (arr A.// [(pos, WinDown)]) sPos pos x poswon
    | (cell, pos) == ('╡', pos) = Level (arr A.// [(pos, WinLeft)]) sPos pos x poswon
    | (cell, pos) == ('╞', pos) = Level (arr A.// [(pos, WinRight)]) sPos pos x poswon
    | (cell, pos) == ('▓', pos) = Level (arr A.// [(pos, EmptyCell)]) sPos fPos x poswon


{-
    *** TODO *** 

    Primește coordonatele colțului din dreapta jos al hărții și o listă de 
    perechi de tipul (caracter_celulă, poziția_celulei).
    Întoarce un obiect de tip Level cu toate celeule din listă agăugate pe
    hartă.
    Observatie: Lista primită ca parametru trebuie parcursă de la dreapta 
    la stanga.
-}
addCellHelper ::  Level -> (Char, Position) -> Level
addCellHelper (Level arr sPos fPos x poswon) (cell, pos) = addCell (cell, pos) (Level arr sPos fPos x poswon)
 
createLevel :: Position -> [(Char, Position)] -> Level
createLevel position xs = foldl addCellHelper (emptyLevel position) xs


{-
    *** TODO ***

    Mișcarea unei celule în una din cele 4 direcții 
    Schimbul se poate face doar dacă celula vecină e goală (emptySpace).
    Celulele de tip start și win sunt imutabile.

    Hint: Dacă nu se poate face mutarea puteți lăsa nivelul neschimbat.
-}

moveCell :: Position -> Directions -> Level -> Level
moveCell pos d (Level arr sPos fPos x poswon)
    | pos == sPos = Level arr sPos fPos x poswon
    | pos == fPos = Level arr sPos fPos x poswon
    | d == North = if ((fst posn) >= 0 && (snd posn) <= limy && (fst posn) <= limx && (snd posn) >=0 && (arr A.! posn) == EmptySpace)
                    then Level (arr A.// [(pos, EmptySpace), (posn, (arr A.! pos))]) sPos fPos x poswon
                    else Level arr sPos fPos x poswon
    | d == South = if ((fst poss) <= limx && (snd poss) <= limy && (fst poss) <= limx && (snd poss) >=0 && (arr A.! poss) == EmptySpace)
                    then Level (arr A.// [(pos, EmptySpace), (poss, (arr A.! pos))]) sPos fPos x poswon
                    else Level arr sPos fPos x poswon
    | d == West = if ((snd posw) >= 0 && (snd posw) <= limy && (fst posw) <= limx && (snd posw) >=0 && (arr A.! posw) == EmptySpace)
                    then Level (arr A.// [(pos, EmptySpace), (posw, (arr A.! pos))]) sPos fPos x poswon
                    else Level arr sPos fPos x poswon
    | d == East = if ((snd pose) <= limy && (snd pose) <= limy && (fst pose) <= limx && (snd pose) >=0 && (arr A.! pose) == EmptySpace)
                    then Level (arr A.// [(pos, EmptySpace), (pose, (arr A.! pos))]) sPos fPos x poswon
                    else Level arr sPos fPos x poswon   
    where posn = ((fst pos) - 1, (snd pos))
          poss = ((fst pos) + 1, (snd pos))
          posw = ((fst pos), (snd pos) - 1)
          pose = ((fst pos), (snd pos) + 1)
          limx = (fst (snd (A.bounds arr)))
          limy = (snd (snd (A.bounds arr)))

{-
    *** HELPER ***

    Verifică dacă două celule se pot conecta.
    Atenție: Direcția indică ce vecin este a
    doua celulă pentru prima.

    ex: connection botLeft horPipe East = True (╚═)
        connection horPipe botLeft East = False (═╚)
-}
connection :: Cell -> Cell -> Directions -> Bool
connection cella cellb d
    | d == North && cella `elem` [StartUp, WinUp, VerPipe, BotRight, BotLeft] && cellb `elem` [StartDown, WinDown, VerPipe, TopRight, TopLeft] = True
    | d == South && cella `elem` [StartDown, WinDown, VerPipe, TopRight, TopLeft] && cellb `elem` [StartUp, WinUp, VerPipe, BotRight, BotLeft] = True
    | d == West && cella `elem` [StartLeft, WinLeft, HorPipe, BotRight, TopRight] && cellb `elem` [StartRight, WinRight, HorPipe, BotLeft, TopLeft] = True
    | d == East && cella `elem` [StartRight, WinRight, HorPipe, BotLeft, TopLeft] && cellb `elem` [StartLeft, WinLeft, HorPipe, BotRight, TopRight] = True
    | otherwise = False
{-   
    *** TODO ***

    Va returna True dacă jocul este câștigat, False dacă nu.
    Va verifica dacă celulele cu Pipe formează o cale continuă de la celula
    de tip inițial la cea de tip final.
    Este folosită în cadrul Interactive.
-}
wonLevel :: Level -> Bool
wonLevel (Level arr sPos fPos x poswon)
    | (fst poswon) == (fst fPos) && (snd poswon) == (snd fPos) = True
    | (posn `notElem` x) && (connection (arr A.! poswon) (arr A.! posn) North) = wonLevel (Level arr sPos fPos (poswon:x) posn)
    | (poss `notElem` x) && (connection (arr A.! poswon) (arr A.! poss) South) = wonLevel (Level arr sPos fPos (poswon:x) poss)
    | (posw `notElem` x) && (connection (arr A.! poswon) (arr A.! posw) West) = wonLevel (Level arr sPos fPos (poswon:x) posw)
    | (pose `notElem` x) && (connection (arr A.! poswon) (arr A.! pose) East) = wonLevel (Level arr sPos fPos (poswon:x) pose)
    | otherwise = False
    where 
        posn = ((fst poswon) - 1, (snd poswon))
        poss = ((fst poswon) + 1, (snd poswon))
        posw = ((fst poswon), (snd poswon) - 1)
        pose = ((fst poswon), (snd poswon) + 1)

successorsHelper :: Position -> Directions -> Level -> Bool
successorsHelper pos d (Level arr sPos fPos x poswon)
    | pos == sPos = False
    | pos == fPos = False
    | d == North = if ((fst posn) >= 0 && (snd posn) <= limy && (fst posn) <= limx && (snd posn) >=0 && (arr A.! posn) == EmptySpace && (arr A.! pos) /= EmptySpace)
                    then True
                    else False
    | d == South = if ((fst poss) <= limx && (snd poss) <= limy && (fst poss) <= limx && (snd poss) >=0 && (arr A.! poss) == EmptySpace && (arr A.! pos) /= EmptySpace)
                    then True
                    else False
    | d == West = if ((snd posw) >= 0 && (snd posw) <= limy && (fst posw) <= limx && (snd posw) >=0 && (arr A.! posw) == EmptySpace && (arr A.! pos) /= EmptySpace)
                    then True
                    else False
    | d == East = if ((snd pose) <= limy && (snd pose) <= limy && (fst pose) <= limx && (snd pose) >=0 && (arr A.! pose) == EmptySpace && (arr A.! pos) /= EmptySpace)
                    then True
                    else False
    where posn = ((fst pos) - 1, (snd pos))
          poss = ((fst pos) + 1, (snd pos))
          posw = ((fst pos), (snd pos) - 1)
          pose = ((fst pos), (snd pos) + 1)
          limx = (fst (snd (A.bounds arr)))
          limy = (snd (snd (A.bounds arr)))


instance ProblemState Level (Position, Directions) where
    successors lvl@(Level arr sPos fpos x poswon) = [(((x, y), d), z) | d <- [North, South, West, East], x <- [0..(fst(snd(A.bounds arr)))], y <- [0..(snd(snd(A.bounds arr)))], successorsHelper (x,y) d lvl == True, z <- [moveCell (x,y) d lvl]]
    isGoal lvl@(Level arr sPos fpos x poswon) = wonLevel lvl
    reverseAction (a, s) = undefined 