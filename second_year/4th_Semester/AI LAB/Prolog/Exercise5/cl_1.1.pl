permutation([], []).

permutation(List, [Element|Permutation]) :-
    select(Element, List, Rest),
    permutation(Rest, Permutation).
