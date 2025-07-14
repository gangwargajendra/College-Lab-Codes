successor(List, Result) :-
    append([x], List, Result).


plus(List1, List2, Result) :-
    append(List1, List2, Result).

times(List1, List2, Result) :-
    helperTimes(List1, List2, [], Result).

helperTimes([], _, Acc, Acc).

helperTimes([_|Tail], List2, Acc, Result) :-
    append(Acc, List2, Acc1),
    helperTimes(Tail, List2, Acc1, Result).
