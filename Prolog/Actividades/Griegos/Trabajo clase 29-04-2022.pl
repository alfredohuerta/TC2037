%RECURSIVE VERSION
factorial(1, 1).
factorial(X, Result):-
    X > 1,
    NewX is X - 1,
    factorial(NewX, NewResult),
    Result is NewResult * X.

%TAIL VERSION
%RESULT IS FACTORIAL (1, Result)
factorialT(1, Result, Result).
factorialT(X, Acc, Result):-
    X > 1,
    NewX is X - 1,
    NewAcc is Acc * x,
    factorialT(NewX, NewAcc, Result).

%RECURSIVE VERSION FIBONACCI
fibo(1, 1).
fibo(2, 1).
fibo(N, Result):-
    N > 2,
    N1 is N - 1,
    fibo(N1, R1),
    N2 is N - 2,
    fibo(N2, R2),
    Result is R1 + R2.

%TAIL VERSION
%fiboT(N, T1, T2, Acc)
fiboT(1, _, Acc, Acc).
fiboT(N, T1, T2, Result):-
    N > 1,
    N1 is N - 1,
    NewTerm is T1 + T2,
    fiboT(N1, T2, NewTerm, Result).

%RECURSIVE VERSION SUMATORIA GAUSS
%sum(Start, End, Result).
sum(End, End, End).
sum(Start, End, Result):-
    Start < End,
    S1 is Start + 1,
    sum(S1, End, Aux),
    Result is Start + Aux.

%Tail version
%sumT(Star, End, Acc, Result).
sumT(End, End, Acc, Result):-
    Result is Acc + End.

sumT(Start, End, Acc, Result):-
    Start < End,
    S1 is Start + 1,
    NewAcc is Acc + Start,
    sumT(S1, End, NewAcc, Result).

%removeFromList(Element, List, NewList).
removeFromList(_, [], []).

removeFromList(Element, [Element | Tail], Result):-
    removeFromList(Element, Tail, Result).

removeFromList(Element, [Head | Tail], [Head | NewList]):-
    Element \= Head,
    removeFromList(Element, Tail, NewList).
