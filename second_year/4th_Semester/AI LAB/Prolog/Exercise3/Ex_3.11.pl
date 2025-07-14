helper([], Poly2, Acc, Result) :-
    append(Acc, Poly2, Result).

helper([(Coeff1, Power)|Rest], Poly2, Acc,  Result) :-
    select((Coeff2, Power), Poly2, Poly2Rest),
    CoeffSum is Coeff1 + Coeff2,
    ( CoeffSum =:= 0 ->
        helper(Rest, Poly2Rest, Acc, Result)
    ;
        helper(Rest, Poly2Rest, [(CoeffSum, Power)|Acc], Result)
    ).

helper([(Coeff, Power)|Rest], Poly2, Acc, Result) :-
    \+ member((_, Power), Poly2),
    helper(Rest, Poly2, [(Coeff, Power)|Acc], Result).


poly_sum(Poly1, Poly2, Result) :-
    helper(Poly1, Poly2, [], Result).
