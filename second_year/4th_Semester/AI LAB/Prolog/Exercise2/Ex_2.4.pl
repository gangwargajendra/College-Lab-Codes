reverse_list(InputList, RevList) :-
    helper(InputList, [], RevList).

helper([], Acc, Acc).

helper([Head|Tail], Acc, RevList) :-
    helper(Tail, [Head|Acc], RevList).
