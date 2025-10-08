// tests/test.c
// Minimal home-grown test harness for game_init with board_create/board_destroy

#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "game.h"   // bool game_init(GameState*, Board*)

// ---------- Tiny test macros ----------
static int g_tests_run = 0;
static int g_tests_failed = 0;

#define REQUIRE(cond, msg)                                                        \
    do {                                                                          \
        ++g_tests_run;                                                            \
        if (!(cond)) {                                                            \
            ++g_tests_failed;                                                     \
            fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, (msg));     \
        }                                                                         \
    } while (0)

#define TEST(fn) static void fn(void)

// ---------- Helpers using your API ----------
static Board* make_board(void)
{
    Board* b = board_create();
    return b; // board_create() already resets via board_reset(b)
}

static void destroy_board(Board* b)
{
    if (b) board_destroy(b);
}

static bool board_is_empty_3x3(const Board* b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board_get_cell(b, r, c) != BOARD_CELL_EMPTY) {
                return false;
            }
        }
    }
    return true;
}

static void prefill_board(Board* b)
{
    // Two legal moves to make the board non-empty
    (void)board_process_player_move(b, 0, 0, BOARD_PLAYER_X);
    (void)board_process_player_move(b, 1, 1, BOARD_PLAYER_O);
}

// ---------- Tests ----------
TEST(Null_guard_null_g_should_fail)
{
    Board* b = make_board();
    REQUIRE(b != NULL, "Test setup: board_create returned NULL");

    bool ok = game_init(NULL, b);
    REQUIRE(ok == false, "game_init should return false when GameState* is NULL");

    destroy_board(b);
}

TEST(Null_board_should_fail)
{
    GameState g = (GameState){ 0 };
    bool ok = game_init(&g, NULL);
    REQUIRE(ok == false, "game_init should return false when Board* is NULL");
}

TEST(Happy_path_should_initialise_and_reset_state)
{
    Board* b = make_board();
    REQUIRE(b != NULL, "Test setup: board_create returned NULL");

    GameState g = (GameState){ 0 };
    bool ok = game_init(&g, b);
    REQUIRE(ok == true, "game_init should succeed on valid inputs");

    // Invariants
    REQUIRE(g.board == b, "board pointer should be wired");
    REQUIRE(g.game_over == false, "game should not be over");
    REQUIRE(g.move_count == 0, "move_count should be 0");
    REQUIRE(g.is_player_x_turn == true, "X should start");

    // Baseline status
    REQUIRE(g.status_type == STATUS_TYPE_NONE, "status_type should be NONE");
    // If you’ve added status codes:
    // REQUIRE(g.status_code == GAME_STATUS_NONE, "status_code should be NONE");

    REQUIRE(board_is_empty_3x3(b), "board should be empty after game_init (board_reset)");

    destroy_board(b);
}

TEST(Non_empty_board_should_be_cleared_by_game_init)
{
    Board* b = make_board();
    REQUIRE(b != NULL, "Test setup: board_create returned NULL");

    prefill_board(b);
    REQUIRE(!board_is_empty_3x3(b), "prefill_board failed to dirty the board");

    GameState g = (GameState){ 0 };
    bool ok = game_init(&g, b);
    REQUIRE(ok == true, "game_init should succeed");
    REQUIRE(board_is_empty_3x3(b), "game_init should clear the board (board_reset)");

    destroy_board(b);
}

// ---------- Runner ----------
int main(void)
{
    printf("Running game_init tests...\n");

    Null_guard_null_g_should_fail();
    Null_board_should_fail();
    Happy_path_should_initialise_and_reset_state();
    Non_empty_board_should_be_cleared_by_game_init();

    if (g_tests_failed == 0) {
        printf("[OK] %d tests passed.\n", g_tests_run);
        return 0;
    }
    else {
        printf("[SUMMARY] %d/%d tests failed.\n", g_tests_failed, g_tests_run);
        return 1;
    }
}
