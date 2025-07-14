replace(InputList, WillReplace, ByReplace, ResultList) :-
    helper(InputList, WillReplace, ByReplace, [], RevResult),
    reverse(RevResult, ResultList).

helper([], _, _, Acc, Acc).

helper([Head|Tail], WillReplace, ByReplace, Acc, RevResult) :-
    (   Head == WillReplace   ->
                helper(Tail, WillReplace, ByReplace, [ByReplace|Acc], RevResult)
        ;       helper(Tail, WillReplace, ByReplace, [Head|Acc], RevResult)
    ).
