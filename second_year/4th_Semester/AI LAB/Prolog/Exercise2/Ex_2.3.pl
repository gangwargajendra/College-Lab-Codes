remove_duplicates(InputList, ResultList) :-
    helper(InputList, [], RevList),
    reverse(RevList, ResultList).

/* Base Case */
helper([] , Acc, Acc).

/* if Head is already in Accumulator */
helper([Head|Tail], Acc, ResultList) :-
    member(Head, Acc),
    helper(Tail, Acc, ResultList).

/* if Head is not in Accumulator */
helper([Head|Tail], Acc, ResultList) :-
    \+member(Head, Acc),
    helper(Tail, [Head|Acc], ResultList).




/* This code gives correct output but in the last |_ is added.*/
/*
remove_duplicates(InputList, ResultList) :-
    helper(InputList, ResultList).

helper([], _).

helper([Head|Tail], ResultList) :-
   (   member(Head, ResultList) ->
            helper(Tail, ResultList)
       ;    helper(Tail, [ResultList|Head])
   ).
*/
