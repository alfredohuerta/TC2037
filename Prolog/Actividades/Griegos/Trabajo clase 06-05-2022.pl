arc(1, 2).
arc(1, 3).
arc(1, 4).
arc(2, 5).
arc(2, 6).
arc(2, 7).
arc(3, 8).
arc(3, 9).
arc(3, 10).
arc(4, 5).
arc(4, 7).
arc(4, 11).
arc(4, 9).
arc(7, 8).
arc(7, 10).
arc(8, 9).

connect(A, B):-
    arc(A, B).

connect(A, B):-
    arc(B, A).

%next(current, next, visitedList).
next(current, next, visitedList):-
    connect(current, next),
    not(memeber(next, visitedList)).

%dfsAux(current, goal, visitedList, path).
dfsAux(goal, goal, _, [goal]).

dfsAux(current, goal, visitedList, [current | path]):-
    next(current, next, visitedList),
    dfsAux(next, goal, [next | visitedList], path).

dfs(start, end, path):-
    dfsAux(start, end, [], path).

%pushaBack(X, List, Result)
pushBack(X, [], [X]).

pushBack(X, [Head | Tail], [Head | R1]):-
    pushBack(X, Tail, R1).

%bfsAux(goal pending, visited, path).
bfsAux(goal, [goal | _], visited, visited).

bfsAux(goal, [current | tail], visited, path):-
    goal \= current,
    next(current, next, visited),
    pushBack(tail, next, newPending),
    pushBack(current, visitded, newVisited),
    bfsAux(goal, newPending, [current | visited], path).

bfs(start, end, path):-
    bfsAux(goal, [start], [], tempPath),
    pushBack(goal, tempPath, path).
