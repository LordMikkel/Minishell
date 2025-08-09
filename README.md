# Minishell
Minishell - Bash

dia 1:

1. Arquitectura general
Vuestra shell va a seguir este flujo principal:

Prompt → Mostrar la línea y leer input.

Tokenización → Separar la entrada en tokens (palabras, operadores, etc.).

Expansión → Sustituir variables de entorno, tilde (~), y demás.

Construcción del AST → Crear un árbol sintáctico para modelar el comando y su estructura (pipes, redirecciones, etc.).

Ejecución recursiva → Navegar el AST y ejecutar cada nodo (manejo de fork, pipes, redirecciones).

Limpieza de memoria → Liberar todos los recursos de esta iteración.

2. Estructuras de datos clave
Definisteis un t_shell (o s_data) que encapsula todo el estado:

c
Copy
Edit
typedef struct s_data
{
    t_prompt tokens;  // Tokens del comando actual
    t_envp   envp;    // Variables de entorno
    t_parser ast;     // Árbol sintáctico del comando
} t_shell;
El objetivo es pasar t_shell como referencia para que todos los módulos trabajen sobre el mismo estado.

3. Main loop
Inicializa el estado (init).

Instala handlers de señales para el padre.

Bucle infinito:

Mostrar prompt → leer input.

Guardar en histórico.

Llamar a minishell() con el input leído.

Manejar errores.

4. minishell()
Secuencia interna:

c
Copy
Edit
if (!tokenizer(data, input))    return error(...);
if (!expansion(data->tokens, data->envp)) return error(...);
if (!ast(data, data->tokens))   return error(...);
if (!execute_recursive(data, data->ast))  return error(...);
clean_data(data);
Cada etapa devuelve false si falla y dispara limpieza y gestión de error.

5. Manejo de señales
Padre
Usa sigaction con un handler custom que:

No mata el proceso.

Limpia la línea y redibuja el prompt si está esperando input.

Marca un flag global para saber que ocurrió una señal.

Hijo
Restaura señales a SIG_DFL para que se comporten como en bash.

Si recibe SIGINT o SIGQUIT, muere como un comando normal.

El padre detecta con waitpid si el hijo terminó por señal y actúa.

Orden de desarrollo

1.Prompt + lectura de input.

2.Tokenizer básico.

3.Expansión de variables y comillas.

4.Parser para construir AST simple.

5.Ejecución de comandos

6.Señales y limpieza.

7.Refinar memoria y errores.


                ┌───────────────────────────┐
                │         MAIN LOOP         │
                │───────────────────────────│
                │  signals()  // PADRE      │
                │  init(&data)              │
                └─────────────┬─────────────┘
                              │
                              ▼
                   ┌─────────────────────┐
                   │  prompt(&input)     │
                   │  (espera comando)   │
                   └─────────┬───────────┘
                 (SIGINT)    │   [EOF/exit]
                  PADRE      │   clean & exit
                  limpia     │
                  prompt     ▼
               ┌──────────────────────────────┐
               │ 1) TOKENIZER                 │
               │ - Divide en tokens           │
               │ - Identifica pipes, redirs   │
               │ - Maneja quotes              │
               └───────────────┬──────────────┘
                               ▼
               ┌──────────────────────────────┐
               │ 2) EXPANSION                 │
               │ - Sustituye $VAR, $?         │
               │ - Expande wildcards          │
               │ - Respeta quotes             │
               └───────────────┬──────────────┘
                               ▼
               ┌─────────────────────────────┐
               │ 3) AST BUILDER              │
               │ - Construye árbol sintáctico│
               │ - Agrupa comandos/args      │
               │ - Ordena pipes/redirs       │
               └──────────────┬──────────────┘
                              ▼
               ┌─────────────────────────────┐
               │ 4) EXECUTOR                 │
               │ - Recorre AST               │
               │ - fork() para comandos      │
               │ - Redirecciones             │
               │ - Pipes                     │
               └──────────────┬──────────────┘
                              │
                 ┌────────────┴─────────────┐
                 ▼                           ▼
      ┌─────────────────────┐     ┌─────────────────────┐
      │ PADRE               │     │ HIJO                │
      │──────────────────── │     │──────────────────── │
      │ - Espera con        │     │ - Restaura señales  │
      │   waitpid()         │     │   SIG_DFL           │
      │ - Maneja señales    │     │ - Ejecuta comando   │
      │   (Ctrl+C)          │     │ - Si señal → muere  │
      └─────────────────────┘     └─────────────────────┘
                 │                           │
                 │       (exit/señal)        │
                 └───────────┬───────────────┘
                             ▼
                ┌─────────────────────────────┐
                │ clean_data(data)            │
                │ Vuelve al MAIN LOOP         │
                └─────────────────────────────┘


DAY 02:

parseando(t_shell data, t_prompt *prompt)
{
	int i;
	char *start;
	int end;

	i = 0;
	while (str[i] != '\0')
	{
		if ( str[i] == '(')
		{
			prompt->n_parentesis++;
			ft_add_token(str[i]);
		}
		else if (str[i] != unitarios && != espacio)
		{
			prompt->n_cmds++;
			start = str[i];
			while (str[i] != unitarios && != espacio)
			{
				end++;
			}
			ft_add_token(start + end);
		}
	}
	if (!ft_validate(data) || !ft_validate_tokens)
	{

	}


}
int ft_add_token(t_prompt *prompt, char *value)
{
	static int i = 0;
	prompt->tokens->array_tokens[i] = value;
	i++;
	return (0);
}

validate()
{
	if (data->prompt->n_parentesis % 2 == 0 )
		tot be
	else if (data->prompt->n_comd % 2 != 0)
	{
		clean(data);
	}
	if (data->prompt->cmd % 2 == 0 )
		tot be
	else if (data->prompt->n_parentesis % 2 != 0)
	{
		clean(data);
	}
	if (data->prompt->pipe % 2 == 0 )
		tot be
	else if (data->prompt->n_parentesis % 2 != 0)
	{
		clean(data);
	}
	if (data->prompt->n_parentesis % 2 == 0 )
		tot be
	else if (data->prompt->n_parentesis % 2 != 0)
	{
		clean(data);
	}
}

