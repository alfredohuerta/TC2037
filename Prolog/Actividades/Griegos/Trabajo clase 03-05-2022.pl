%substitute(X, Y, List, Result).
substitute(_, _, [], []).

substitute(X, Y, [X | Tail], [Y | R1]):-
    substitute(X, Y, Tail, R1).

substitute(X, Y, [Head | Tail], [Head | R1]):-
    X \= Head,
    substitute(X, Y, Tail, R1).

%anyPositives(List, Result)
anyPositives([]):- fail.

%El ! es para que se detenga en cuanto complete la operación.
anyPositives([X | _]):- X > 0, !.

anyPositives([_ | Tail]):-
    anyPositives(Tail).

%pushaBack(X, List, Result)
pushBack(X, [], [X]).

pushBack(X, [Head | Tail], [Head | R1]):-
    pushBack(X, Tail, R1).

%len(List, Size).
len([], 0).

len([_ | Tail], Result):-
    len(Tail, R1),
    Result is R1 + 1.

%reverse(List, List).
reveser([], []).

reverse([Head | Tail], Result):-
    reverse(Tail, R1),
    pushBack(Head, R1, Result). %También puede usarse el append.
