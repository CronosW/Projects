{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Search where

import qualified Data.Maybe as M
import ProblemState
{-
    *** TODO ***

    Tipul unei nod utilizat în procesul de căutare. Recomandăm reținerea unor
    informații legate de:

    * stare;
    * acțiunea care a condus la această stare;
    * nodul părinte, prin explorarea căruia a fost obținut nodul curent;
    * adâncime
    * copiii, ce vor desemna stările învecinate
-}

data Node s a = Node { state :: s
                     , action :: Maybe a
                     , parent :: Maybe (Node s a)
                     , depth :: Int
                     , children :: [Node s a]
                     } deriving (Show, Eq)

{-
    *** TODO ***
    Gettere folosite pentru accesul la câmpurile nodului
-}
nodeState :: Node s a -> s
nodeState node = state node

nodeParent :: Node s a -> Maybe (Node s a)
nodeParent node = parent node

nodeDepth :: Node s a -> Int
nodeDepth node = depth node

nodeAction :: Node s a -> Maybe a
nodeAction node = action node

nodeChildren :: Node s a -> [Node s a]
nodeChildren node = children node

{-
    *** TODO ***

    Generarea întregului spațiu al stărilor
    Primește starea inițială și creează nodul corespunzător acestei stări,
    având drept copii nodurile succesorilor stării curente.
-}
createStateSpaceHelper :: (ProblemState s a, Eq s) => Node s a -> Int -> (a, s) -> Node s a
createStateSpaceHelper parentNode depth (a, s) = node
    where
        node = Node s (Just a) (Just parentNode) (depth + 1) (filter (\child -> (state child) /= (state parentNode)) (map children (successors s)))
        children (a2, s2) = createStateSpaceHelper node (depth + 1) (a2, s2) 

createStateSpace :: (ProblemState s a, Eq s) => s -> Node s a
createStateSpace state = r
    where
        r = Node state Nothing Nothing 0 (map (\(a, s) -> (createStateSpaceHelper r 0 (a, s))) (successors state))



{-
    *** TODO ***
   
    Primește un nod inițial și întoarce un flux de perechi formate din:
    * lista nodurilor adăugate în frontieră la pasul curent
    * frontiera

-}

isVisited :: Eq s => Node s a -> [Node s a] -> Bool
isVisited node [] = False
isVisited node visited = (state node) == (state (head visited)) || isVisited node (tail visited)

bfs :: Ord s => Node s a -> [([Node s a], [Node s a])]
bfs n = (bfsHelper [n] [n])

bfsHelper :: Eq s => [Node s a] -> [Node s a] -> [([Node s a], [Node s a])]
bfsHelper frontier visited
    | null frontier == False = [(children, (tail frontier) ++ children)] ++ bfsHelper ((tail frontier) ++ children) ((head frontier) : visited)
    | otherwise = []
    where
        children = [x | x <- (nodeChildren (head frontier)), ((not(isVisited x visited)))]


{-
    *** TODO ***
  
    Primește starea inițială și finală și întoarce o pereche de noduri, reprezentând
    intersecția dintre cele două frontiere.
-}

bidirBFS :: Ord s => Node s a -> Node s a -> (Node s a, Node s a)
bidirBFS n1 n2 = bidirHelper (bfs n1) (bfs n2)

bidirHelper :: Eq s => [([Node s a], [Node s a])] -> [([Node s a], [Node s a])] -> (Node s a, Node s a)
bidirHelper ((l1, l2):r1) ((l3, l4):r2)
    | null list == True = bidirHelper r1 r2
    | otherwise = head list
    where list = filter (\(v, w) -> (state v) == (state w)) [(x, y) | x <- l1, y <- l4] 

{-
    *** TODO ***

    Pornind de la un nod, reface calea către nodul inițial, urmând legăturile
    către părinți.

    Întoarce o listă de perechi (acțiune, stare), care pornește de la starea inițială
    și se încheie în starea finală.

-}

extractPath :: Node s a -> [(Maybe a, s)]
extractPath n
    | M.isJust (nodeParent n) = (foldl (++) (extractPath (M.fromJust (nodeParent n))) [[((nodeAction n), (nodeState n))]])
    | M.isNothing (nodeParent n) = [((nodeAction n), (nodeState n))]
    


{-
    *** TODO ***

    Pornind de la o stare inițială și una finală, se folosește de bidirBFS pentru a găsi
    intersecția dintre cele două frontiere și de extractPath pentru a genera calea.

    Atenție: Pentru calea gasită în a doua parcurgere, trebuie să aveți grijă la a asocia
    corect fiecare stare cu acțiunea care a generat-o.

    Întoarce o listă de perechi (acțiune, stare), care pornește de la starea inițială
    și se încheie în starea finală.
-}

solve :: (ProblemState s a, Ord s)
      => s          -- Starea inițială de la care se pornește
      -> s          -- Starea finală la care se ajunge
      -> [(Maybe a, s)]   -- Lista perechilor
solve = undefined
