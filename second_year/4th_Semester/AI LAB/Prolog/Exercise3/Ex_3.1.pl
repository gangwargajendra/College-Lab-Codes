distance((X1, Y1), (X2, Y2), Distance) :-
    Dx is  (X2 - X1),
    Dy is  (Y2 - Y1),
    Distance is sqrt(Dx * Dx + Dy * Dy).
