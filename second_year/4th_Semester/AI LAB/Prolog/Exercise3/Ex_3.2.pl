square(N, Char) :-
   integer(N), N > 0,
   helper1(N, N, Char).

helper1(0, _, _) :-
    !.

helper1(Rows, Len, Char) :-
    helper2(Len, Char),
    nl,
    Rows1 is Rows - 1,
    helper1(Rows1, Len, Char).


helper2(0, _) :-
    !.

helper2(Len, Char) :-
    write(Char), write(' '),
    Len1 is Len - 1,
    helper2(Len1, Char).



