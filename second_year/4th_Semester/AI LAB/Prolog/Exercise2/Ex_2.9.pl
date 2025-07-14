longer([], [_|_]).

longer([_|Tail1], [_|Tail2]) :-
    longer(Tail1, Tail2).

