mean(List, X) :-
    helper(List, 0, TotalEle, 0, Sum),
    X is (Sum / TotalEle).

/* special case : if we have an empty list. */
helper([], 0, 1, Y, Y) :-
    !.


/* Y = sum of 0 to iteration I */

helper([], I, I, Y, Y) :-
    !.

helper([Head|Tail], I, TotalEle, Y, Sum) :-
    Y1 is (Y + Head),
    I1 is (I + 1),
    helper(Tail, I1, TotalEle, Y1, Sum).
