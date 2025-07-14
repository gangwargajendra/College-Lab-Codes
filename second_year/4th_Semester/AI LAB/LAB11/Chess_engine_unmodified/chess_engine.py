import pygame
import chess
import random
import sys
import time

# Constants for the board dimensions and colors
WIDTH = HEIGHT = 640  # Board size in pixels (8x8 squares)
SQ_SIZE = WIDTH // 8
FPS = 15

# Colors for the squares
LIGHT_COLOR = (240, 217, 181)
DARK_COLOR = (181, 136, 99)
HIGHLIGHT_COLOR = (186, 202, 68)

# Global dictionary to store images
IMAGES = {}


def load_images():
    """
    Load chess piece images from the images folder.
    The mapping from piece symbol to image file is as follows:
      White Pieces:
         'P' -> white-pawn.png
         'N' -> white-knight.png
         'B' -> white-bishop.png
         'R' -> white-rook.png
         'Q' -> white-queen.png
         'K' -> white-king.png
      Black Pieces:
         'p' -> black-pawn.png
         'n' -> black-knight.png
         'b' -> black-bishop.png
         'r' -> black-rook.png
         'q' -> black-queen.png
         'k' -> black-king.png
    """
    pieces = {
        "P": "white-pawn.png",
        "N": "white-knight.png",
        "B": "white-bishop.png",
        "R": "white-rook.png",
        "Q": "white-queen.png",
        "K": "white-king.png",
        "p": "black-pawn.png",
        "n": "black-knight.png",
        "b": "black-bishop.png",
        "r": "black-rook.png",
        "q": "black-queen.png",
        "k": "black-king.png"
    }
    for symbol, filename in pieces.items():
        path = "c:\\Users\\dhruv\\OneDrive\\Desktop\\SEM 4\\AI\\AI LAB\\CS22\\Assignment11\\images\\" + filename
        try:
            image = pygame.image.load(path)
        except pygame.error as e:
            print(f"Unable to load image at path: {path}")
            raise e
        IMAGES[symbol] = pygame.transform.scale(image, (SQ_SIZE, SQ_SIZE))


def draw_board(screen, flip_board, selected_sq):
    """
    Draw the chess board with optional highlight for the selected square.
    """
    for rank in range(8):
        for file in range(8):
            # Adjust square positions if board is flipped.
            draw_file = file if not flip_board else 7 - file
            draw_rank = rank if not flip_board else 7 - rank

            x = draw_file * SQ_SIZE
            # Pygame's (0,0) is top-left; we draw from bottom (rank 0 at bottom)
            y = (7 - draw_rank) * SQ_SIZE

            color = LIGHT_COLOR if (file + rank) % 2 == 0 else DARK_COLOR
            rect = pygame.Rect(x, y, SQ_SIZE, SQ_SIZE)
            pygame.draw.rect(screen, color, rect)

            # Highlight the selected square if applicable.
            if selected_sq is not None:
                sel_file = chess.square_file(selected_sq)
                sel_rank = chess.square_rank(selected_sq)
                if flip_board:
                    sel_file = 7 - sel_file
                    sel_rank = 7 - sel_rank
                # Compare with current square coordinates.
                if sel_file == file and sel_rank == rank:
                    pygame.draw.rect(screen, HIGHLIGHT_COLOR, rect, 4)


def draw_pieces(screen, board, flip_board):
    """
    Draw all pieces on the board based on the current board state.
    """
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            file = chess.square_file(square)
            rank = chess.square_rank(square)
            if flip_board:
                file = 7 - file
                rank = 7 - rank
            x = file * SQ_SIZE
            y = (7 - rank) * SQ_SIZE
            symbol = piece.symbol()  # Uppercase for white, lowercase for black.
            screen.blit(IMAGES[symbol], pygame.Rect(x, y, SQ_SIZE, SQ_SIZE))


def get_square_from_mouse(pos, flip_board):
    """
    Convert the mouse position (x, y) to a chess square index.
    """
    x, y = pos
    file = x // SQ_SIZE
    rank = 7 - (y // SQ_SIZE)
    if flip_board:
        file = 7 - file
        rank = 7 - rank
    return chess.square(file, rank)


# def get_random_ai_move(board):
#     """
#     Returns a random legal move for the given board.
#     """
#     return random.choice(list(board.legal_moves))

def evaluate_board(board):
    """
    Heuristic evaluation of the board.
    Positive values favor White; negative values favor Black.
    """
    if board.is_checkmate():
        # If the current player is checkmated, return a very low/high score.
        return -9999 if board.turn == chess.WHITE else 9999
    if board.is_stalemate() or board.is_insufficient_material():
        return 0

    values = {
        chess.PAWN: 1,
        chess.KNIGHT: 3,
        chess.BISHOP: 3,
        chess.ROOK: 5,
        chess.QUEEN: 9,
        chess.KING: 0
    }
    total = 0
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            # Add the piece value if White; subtract if Black.
            value = values[piece.piece_type]
            total += value if piece.color == chess.WHITE else -value
    return total


def minimax(board, depth, alpha, beta, maximizing_player):
    """
    Alpha-beta pruning algorithm.
    Returns a tuple of (evaluation score, best move).
    """
    if depth == 0 or board.is_game_over():
        return evaluate_board(board), None

    best_move = None
    if maximizing_player:
        max_eval = -float('inf')
        for move in board.legal_moves:
            board.push(move)
            eval_score, _ = minimax(board, depth - 1, alpha, beta, False)
            board.pop()
            if eval_score > max_eval:
                max_eval = eval_score
                best_move = move
            alpha = max(alpha, eval_score)
            if beta <= alpha:
                break  # Beta cut-off.
        return max_eval, best_move
    else:
        min_eval = float('inf')
        for move in board.legal_moves:
            board.push(move)
            eval_score, _ = minimax(board, depth - 1, alpha, beta, True)
            board.pop()
            if eval_score < min_eval:
                min_eval = eval_score
                best_move = move
            beta = min(beta, eval_score)
            if beta <= alpha:
                break  # Alpha cut-off.
        return min_eval, best_move


def get_best_move(board, depth, alpha, beta):
    """
    Determines the best move for the current board state using alpha-beta pruning.
    """
    maximizing_player = board.turn == chess.WHITE
    _, best_move = minimax(board, depth, alpha, beta, maximizing_player)
    return best_move


def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Chess Game: Human vs. Random AI")
    clock = pygame.time.Clock()
    load_images()

    board = chess.Board()

    # Ask the player to choose a color
    player_color = input("Choose your color (white/black): ").strip().lower()
    if player_color not in ['white', 'black']:
        print("Invalid choice. Defaulting to white.")
        player_color = 'white'
    human_is_white = (player_color == 'white')
    # Flip the board so that the human's pieces appear at the bottom.
    flip_board = not human_is_white

    selected_sq = None  # Currently selected square for a move

    running = True
    while running:
        # Determine whose turn it is.
        human_turn = (board.turn == chess.WHITE and human_is_white) or (
                    board.turn == chess.BLACK and not human_is_white)

        if human_turn:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    pos = pygame.mouse.get_pos()
                    sq = get_square_from_mouse(pos, flip_board)
                    if selected_sq is None:
                        piece = board.piece_at(sq)
                        if piece and ((piece.color == chess.WHITE and human_is_white) or (
                                piece.color == chess.BLACK and not human_is_white)):
                            selected_sq = sq
                    else:
                        move = chess.Move(selected_sq, sq)
                        if move in board.legal_moves:
                            board.push(move)
                        else:
                            print("Illegal move, try again.")
                        selected_sq = None
        else:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()
                    sys.exit()
            time.sleep(0.5)  # Delay for realism.
            # Use alpha-beta pruning to select the AI move.
            ai_move = get_best_move(board, 3, -float('inf'), float('inf'))
            if ai_move is None:
                print("No legal moves available for AI.")
                break
            board.push(ai_move)
            print("AI played:", ai_move.uci())

        # Redraw board and pieces.
        draw_board(screen, flip_board, selected_sq)
        draw_pieces(screen, board, flip_board)
        pygame.display.flip()

        if board.is_game_over():
            print("Game over. Result:", board.result())
            time.sleep(3)
            running = False

        clock.tick(FPS)


if __name__ == "__main__":
    main()
