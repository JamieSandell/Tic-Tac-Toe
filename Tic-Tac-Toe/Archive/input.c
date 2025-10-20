#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // doing the safe pattern (fgets -> parse), so sscanf here is perfectly reasonable.
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "input.h"

#define MAX_INPUT_LENGTH 100

// Helper: Reads a line from stdin, returns InputResult, buffer is filled if successful
static enum InputResult read_input_line(char *buffer, size_t size)
{
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        if (feof(stdin))
        {
            return INPUT_RESULT_EOF;
        }
        if (ferror(stdin))
        {
            return INPUT_RESULT_ERROR;
        }

        return INPUT_RESULT_ERROR;
    }
    return INPUT_RESULT_OK;
}

// Helper: Checks for extra non-whitespace characters after pos in buffer
static bool has_extra_non_whitespace(const char *buffer, int pos)
{
    for (int i = pos; buffer[i] != '\0'; ++i)
    {
        if (!isspace((unsigned char)buffer[i]))
        {
            return true;
        }
    }

    return false;
}

// Helper: Consumes rest of line if input was too long
static void consume_rest_of_line(const char *buffer)
{
    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] != '\n')
    {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
    }
}

enum InputResult get_move_input(Input *const out_input)
{
    if (out_input == NULL)
    {
        return INPUT_RESULT_NULL_POINTER;
    }

    char buffer[MAX_INPUT_LENGTH];
    enum InputResult input_result = read_input_line(buffer, sizeof(buffer));

    if (input_result != INPUT_RESULT_OK)
    {
        return input_result;
    }

    int row;
    int col;
    int pos;

    if (sscanf(buffer, "%d %d %n", &row, &col, &pos) == 2)
    {
        if (has_extra_non_whitespace(buffer, pos))
        {
            consume_rest_of_line(buffer);
            return INPUT_RESULT_INVALID;
        }
    }
    else
    {
        consume_rest_of_line(buffer);
        return INPUT_RESULT_INVALID;
    }

    out_input->row = row;
    out_input->col = col;

    consume_rest_of_line(buffer);
    return INPUT_RESULT_OK;
}

enum InputResult get_yes_no_input(bool *const out_is_yes)
{
    if (out_is_yes == NULL)
    {
        return INPUT_RESULT_NULL_POINTER;
    }

    char buffer[MAX_INPUT_LENGTH];
    enum InputResult input_result = read_input_line(buffer, sizeof(buffer));

    if (input_result != INPUT_RESULT_OK)
    {
        return input_result;
    }

    char ch;
    int pos;

    if (sscanf(buffer, " %c %n", &ch, &pos) == 1)
    {
        if (has_extra_non_whitespace(buffer, pos))
        {
            consume_rest_of_line(buffer);
            return INPUT_RESULT_INVALID;
        }
    }
    else
    {
        consume_rest_of_line(buffer);
        return INPUT_RESULT_INVALID;
    }

    if (ch == 'y' || ch == 'Y')
    {
        *out_is_yes = true;
    }
    else if (ch == 'n' || ch == 'N')
    {
        *out_is_yes = false;
    }
    else
    {
        consume_rest_of_line(buffer);
        return INPUT_RESULT_INVALID;
    }

    consume_rest_of_line(buffer);
    return INPUT_RESULT_OK;
}