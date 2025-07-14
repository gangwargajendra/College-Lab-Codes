/* for the first part */

last1(List, Element) :-
    helper(List, Element).

helper([Element|[]], Element).

helper([_|Tail], Element) :-
    helper(Tail, Element).

/* for the second part */

last2(List, Element) :-
    append(_, [Element], List).

