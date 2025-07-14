/* if list is empty */

analyse_list([]) :-
    write('This is an empty list.').

/* if list is not empty */

analyse_list([Element|List1]) :-
    write('This is the head of your list : '),
    write(Element), nl,
    write('This is the tail of your list : '),
    write(List1), nl.


/* we can check that the argument is a list or not using is_list(List). */
/*
 *
 * check_if_list(X) :-
 *   is_list(X),
 *  write('Yes, this is a list.'), nl.
 *
 * check_if_list(_) :-
 *   write('No, this is not a list.'), nl.
 */
