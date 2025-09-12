# Minishell
Minishell - Bash

## POR HACER:

- Bash te abra línea para que completes el comando ver → Modificar balance de ' " ( || && |
  - https://github.com/rogerdevworld/minishell/blob/main/src/bonus/loop_processing.c
  - https://github.com/rogerdevworld/minishell/blob/main/src/bonus/syntax/ft_lexer_2.c#L93

## MIKEL:

- Problemas de simplify tokens → `sds""''"$ls"''$mikel` genera doble NO_SPACE pero creo que no hay problema a malas se podría hacer una función que borre dobles NO_SPACES seguidos.
- `is_double_quote` manejar \ correctamente
- `is_double_quote` seguido de word → NO_SPACE
- Crear envp char **
- bash + argumento debería abrir ese archivo (solo el primero) y tratar de ejecutar los que haya dentro como input
- SHLVL actualizar

## DAVID:

- Arreglar `is_cmd` para que esto lo catalogue como cmd → Token [3]: '/usr/bin/ls' (type: WORD)
- Errores sintáctico
	`(echo) hi` → debería dar error syntax
	`(echo hi && ((echo hi && (echo hi) && echo hi)))` → debería dar error syntax
- Expansiones $?, $$, $!...
- Actualizar el size de env cada vez que se setea con export
- `my_assignation` builtin
- `echo $a && a=1`
- Invalid read → `echo $A`
- Locales seteadas no dejan setear la misma variable a export → no debería ser así
- No setea `export A=2 ls D=5` correctamente como lo hace bash
- `echo "hola $NOEXISTE"` borra toda la string
- Expansion ha de soportar los wildcards *
- Refactorizar expansion para que incorpore `send_tokens_for_expansion`
- Norminette
- Comentarios

## ARQUITECTURA GENERAL

```
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
```

## OPCIÓN PARA FLUJO DE TRABAJO:

1. Si hay token de expansión → Se intenta expandir. Si no se puede, no importa, se ignora y no se intercambia por "".
2. Entonces se aplica una función de juntar (esto en caso de que haya algún NO SPACE token, si no hay este token, no se junta nada).
3. Armamos el árbol
4. Antes de ejecutar si hay token de expansión → Se intenta expandir (Ahora sí de verdad, con "" y todo el rollo) y juntar obligatoriamente (si hay algo que juntar).
5. Ejecutamos
