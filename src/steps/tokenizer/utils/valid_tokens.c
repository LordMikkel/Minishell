
#include "../../../../inc/minishell.h"

static int check_open_parentesis(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
    int content_flag;

    content_flag = FALSE;
    if (tokens[i].type == PAREN_OPEN)
    {
        while (tokens[i].type)
        {
            if (tokens[i].type == COMMAND)
                content_flag = TRUE;
            if (tokens[i].type == PAREN_CLOSE && i > 1 && content_flag == TRUE)
            {
                prompt->n_parentesis++;
                return (0);
            }
            i++;
        }
        exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    }
    return (0);
}

static int check_closing_parentesis(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
    int content_flag;
    int k;

    content_flag = FALSE;
    k = i;
    if (tokens[i].type == PAREN_CLOSE)
    {
        prompt->n_parentesis++;
        while (tokens[i].type && i >= 1)
        {
            if (tokens[i].type == COMMAND)
                content_flag = TRUE;
            if (tokens[i].type == PAREN_OPEN && i < k && content_flag == TRUE)
            {
                prompt->n_parentesis++;
                return (0);
            }
            i--;
        }
    }
    exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    return (0);
}

/*Esta funcion revisa |. Revisa que haya un cmd a sus lados*/
static int check_pipe(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
    if (tokens[i].type == PIPE)
    {
        if (i > 0 && tokens[i + 1].type && tokens[i - 1].type 
            && ((tokens[i + 1].type == COMMAND
            || tokens[i + 1].type == WORD)
            && (tokens[i - 1].type == COMMAND
            || tokens[i - 1].type == WORD)))
        {
            prompt->n_pipes++;
            return (0);
        }
        exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    }
    return (0);
}
/*Esta funcion revisa || y &&. Revisa que haya un cmd a sus lados*/
static int check_or_and(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
    if (tokens[i].type == OR || tokens[i].type == AND)
    {
        if (i > 0 && tokens[i + 1].type && tokens[i - 1].type 
            && ((tokens[i + 1].type == COMMAND
            || tokens[i + 1].type == WORD)
            && (tokens[i - 1].type == COMMAND
            || tokens[i - 1].type == WORD)))
        {
            return (0);
        }
        exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    }
    return (0);
}

/*Esta funcion revisa cada token, especificamente los | () && ||*/
int valid_tokens(t_shell *data, t_prompt *prompt, t_token *tokens)
{
    int i;

    i = 0;
    while (tokens[i].type)
    {
        check_open_parentesis(data, prompt, tokens, i);
        check_closing_parentesis(data, prompt, tokens, i);
        check_pipe(data, prompt, tokens, i);
        check_or_and(data, prompt, tokens, i);
        i++;
    }
    valid_numbers(data, prompt);
    return (0);
}

