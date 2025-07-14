minimum(List, Result) :-
    helper(List, inf, Result).

helper([], MinEle, MinEle) :-
    !.

helper([Head|Tail], MinEle, Result) :-
    (   Head < MinEle ->
                  helper(Tail, Head, Result)
        ;         helper(Tail, MinEle, Result)
    ).
