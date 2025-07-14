/* fact */

concat_lists([], List, List).

/* Rule */

concat_lists([Element|List1], List2, [Element|List3]) :-
    concat_lists(List1, List2, List3).
