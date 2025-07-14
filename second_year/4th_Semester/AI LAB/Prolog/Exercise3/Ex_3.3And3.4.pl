fastfibo(N, X) :-
    integer(N), N >= 0,
    helper3(0, N, 0, 1, X).

helper3(N, N, X1, _, X1) :-
    !.

helper3(I, N, X1, X2, X) :-
    X3 is (X1 + X2),
    I1 is (I + 1),
    helper3(I1, N, X2, X3, X).








/* This will compute till 40-50, but for large N, it will give stack overflow. */

fibonacci(N, X) :-
    integer(N), N >= 0,
    helper1(N, X).

helper1(0, X) :-
    X is 0.

helper1(1, X) :-
    X is 1.

helper1(N, X) :-
    N1 is N-1,
    N2 is N-2,
    helper1(N1, X1),
    helper1(N2, X2),
    X is X1 + X2.
