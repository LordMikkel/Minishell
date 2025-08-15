
#include "../../../../inc/minishell.h"

int valid_numbers(t_shell *data, t_prompt *prompt)
{
    if (prompt->n_parentesis > 0)
    {
        if (prompt->n_parentesis % 2 != 0)
            exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    }
    if (prompt->n_double_quotes > 0)
    {
        if (prompt->n_single_quotes % 2 != 0)
            exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    }
    if (prompt->n_escape > 0)
    {
        if (prompt->n_escape % 2 != 0)
            exit_error(data, ERR_SYNTAX, EXIT_MISUSE);
    }
    return (0);
}
