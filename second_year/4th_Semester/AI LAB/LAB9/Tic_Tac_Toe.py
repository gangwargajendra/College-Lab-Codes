def print_board(board):
    for row in board:
        print(" | ".join(row))
        print("---------")


def check_win(board, player):
    for row in board:
        is_win = True
        for i in range(3):
            if row[i] != player :
                is_win = False
                break
        if is_win:
            return is_win

    for col in range(3):
        is_win = True
        for row in board :
            if row[col] != player :
                is_win = False
                break
        if is_win:
            return is_win

    is_win1 = True
    is_win2 = True
    for i in range(3) :
        if board[i][i] != player:
            is_win1 = False
        if board[i][2-i] != player:
            is_win2 = False
    if is_win1 or is_win2:
        return True

    return False

def get_possible_moves(board):
    possible_moves = []
    for i in range(3) :
        for j in range(3) :
            if board[i][j] == " " :
                possible_moves.append((i, j))
    return possible_moves

def game_over(board):
    return check_win(board, 'X') or check_win(board, 'O') or len(get_possible_moves(board)) == 0


def make_move(board, move, player):
    new_board = []
    for row in board:
        new_board.append(row.copy())
    new_board[move[0]][move[1]] = player
    return new_board


def evaluate(board):
    if check_win(board, 'X'):
        return 1
    elif check_win(board, 'O'):
        return -1
    else:
        return 0


def minimax(board, current_player, ai_player, alpha=-float('inf'), beta=float('inf')):
    if game_over(board):
        return evaluate(board)

    if current_player == 'X':
        best_score = -float('inf')
        for move in get_possible_moves(board):
            new_board = make_move(board, move, 'X')
            score = minimax(new_board, 'O', ai_player, alpha, beta)
            best_score = max(best_score, score)
            alpha = max(alpha, best_score)
            if beta <= alpha:
                break # beta cutoff
        return best_score
    else:
        best_score = float('inf')
        for move in get_possible_moves(board):
            new_board = make_move(board, move, 'O')
            score = minimax(new_board, 'X', ai_player)
            best_score = min(best_score, score)
            beta = min(beta, best_score)
            if beta <= alpha:
                break # alpha cutoff
        return best_score



def get_best_move(board, player):
    if player == 'X' :
        best_score = -float('inf')
    else :
        best_score = float('inf')

    best_move = None
    possible_moves = get_possible_moves(board)

    for move in possible_moves:
        new_board = make_move(board, move, player)
        if player == 'X':
            score = minimax(new_board, 'O', player)
            if score > best_score:
                best_score = score
                best_move = move
        else:
            score = minimax(new_board, 'X', player)
            if score < best_score:
                best_score = score
                best_move = move
    return best_move


def main():
    board = []
    for _ in range(3):
        board.append([' ', ' ', ' '])

    print("Welcome to Tic-Tac-Toe!")
    human = input("Do you want to play as X or O? ").upper()
    while human not in ['X', 'O']:
        human = input("Invalid choice. Please choose X or O: ").upper()

    if human == 'O' :
        ai = 'X'
    else:
        ai = 'O'
    
    if human == 'X' :
        current_player = human
    else:
        current_player = ai

    print(f"You are {human}, I am {ai}.")

    while not game_over(board):
        print_board(board)
        if current_player == human:
            while True :
                move = input("Enter your move (row column): ")
                row, col = map(int, move.split())
                if 1 <= row <= 3 and 1 <= col <= 3:
                    row -= 1
                    col -= 1
                    if board[row][col] == ' ':
                        board[row][col] = human
                        current_player = ai
                        print(f"You played at ({row + 1}, {col + 1})")
                        break
                    else:
                        print("Cell already occupied. Try again.")
                else:
                    print("Invalid input. Enter numbers between 1-3.")
        else:
            print("AI turn...")
            move = get_best_move(board, ai)
            board[move[0]][move[1]] = ai
            current_player = human
            print(f"I play at ({move[0] + 1}, {move[1] + 1})")

    print_board(board)
    if check_win(board, human):
        print("Congratulations! You win!")
    elif check_win(board, ai):
        print("I win!")
    else:
        print("It's a draw!")


if __name__ == "__main__":
    main()