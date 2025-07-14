element_at(List, N, Result) :-
    integer(N), N > 0,
    helper(0, N, List, _, Result).



helper(N, N, _, Head, Head) :-
    !.

helper(I, N, [Head|Tail], _, Result) :-
    I1 is (I + 1),
    helper(I1, N, Tail, Head, Result).
