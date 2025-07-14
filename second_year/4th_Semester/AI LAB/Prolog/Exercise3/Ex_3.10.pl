% Turning right
execute(Pos, north, right, Pos, east).
execute(Pos, east, right, Pos, south).
execute(Pos, south, right, Pos, west).
execute(Pos, west, right, Pos, north).

% Turning left
execute(Pos, north, left, Pos, west).
execute(Pos, west, left, Pos, south).
execute(Pos, south, left, Pos, east).
execute(Pos, east, left, Pos, north).

% Moving forward
execute((X, Y), north, move, (X, Y1), north) :- Y1 is Y + 1.
execute((X, Y), south, move, (X, Y1), south) :- Y1 is Y - 1.
execute((X, Y), east, move, (X1, Y), east)   :- X1 is X + 1.
execute((X, Y), west, move, (X1, Y), west)   :- X1 is X - 1.

% Base case: no commands left
helper(Pos, Orient, [], Pos, Orient).

% Recursive case: handle one command and proceed
helper(Pos, Orient, [Cmd | Cmds], PosFinal, OrientFinal) :-
    execute(Pos, Orient, Cmd, Pos2, Orient2),
    helper(Pos2, Orient2, Cmds, PosFinal, OrientFinal).

% Start at (0, 0), facing north
status(Commands, FinalPosition, FinalOrientation) :-
    helper((0, 0), north, Commands, FinalPosition, FinalOrientation).
