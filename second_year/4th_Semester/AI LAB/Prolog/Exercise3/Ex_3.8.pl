range(Lower, Upper, Result) :-
    helper(Lower, Upper, [], Result).

helper(Lower, Upper, Acc, Acc) :-
    Lower > Upper.

helper(Lower, Upper, Acc, Result) :-
    Previous is Upper - 1,
    helper(Lower, Previous, [Upper|Acc], Result).

