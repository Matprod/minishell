/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avengers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Matprod <matprod42@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:27:35 by Matprod           #+#    #+#             */
/*   Updated: 2024/06/06 15:37:28 by Matprod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	check_double_syntax(t_token *token_list)
{
	t_token *tmp;

	tmp = token_list;
	while(tmp->next)
	{
		if (token_list->type == 0 || token_list->type == 1 || token_list->type == 14 ||
		token_list->type == 2 || token_list->type == 3 || token_list->type == 12 ||
		token_list->type == 13)
			tmp->next;
		if (tmp->type == tmp->next->type)
		{
			return (1);
		}
		else
			tmp->next;
	}
	return (0);
}
/* enum s_type{
	NOT_DEFINE,
	TOKEN_WORD,
	TOKEN_DQUOTES,
	TOKEN_SQUOTES,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_REDIRECTIN,
	TOKEN_REDIRECTOUT,
	TOKEN_HEREDOC,
	TOKEN_APPENDOUT,
	TOKEN_LIMITER,
	TOKEN_OPENPAR,
	TOKEN_CLOSEPAR,
	TOKEN_WHITESPACE,
	TOKEN_ENV,
	WORD_FILEIN,
	WORD_FILEOUT,
	WORD_FILEOUT_APPEND,
	WORD_BUILTIN,
	WORD_ABSPATH,
	WORD_CMD,
	WORD_OPTION, // option / argument d'une commande
	WORD_LIMITER,
	WORD_STRING,
	WORD_ERROR, //ERREUR de syntaxe
	WORD_WTF, //dans le cas ou j'ai oublie un cas
};
 */
void init_t_word(t_word *word)
{
	word->redi_in = 0;
	word->redi_out = 0;
	word->here_doc = 0;
	word->append = 0;
	word->operator = 0;
	word->cmd = 0;
}

int enumToString(int enumValue) {
    if (enumValue >= 0 && enumValue < 27) 
	{
        return enumValue;
    } else {
        return -1;
    }
}

void define_word(char **value_oftoken, int *token_list, t_word *boolean, t_env *env)
{
	int i = 0;

	while (token_list[i] && value_oftoken[i] != NULL && i < 16) // i = len of the token list
	{
		//printf("value = %s | token = %d\n", value_oftoken[i], token_list[i]);
		if (token_list[i] == TOKEN_REDIRECTIN)
			boolean->redi_in = 1;
		else if (token_list[i] == TOKEN_REDIRECTOUT)
			boolean->redi_out = 1;
		else if (token_list[i] == TOKEN_HEREDOC)
			boolean->here_doc = 1;
		else if (token_list[i] == TOKEN_APPENDOUT)
			boolean->append = 1;
		else if (token_list[i] == TOKEN_APPENDOUT || token_list[i] == TOKEN_REDIRECTIN ||
				token_list[i] == TOKEN_REDIRECTOUT || token_list[i] == TOKEN_HEREDOC ||
				token_list[i] == TOKEN_PIPE || token_list[i] == TOKEN_AND || token_list[i] == TOKEN_OR)
			boolean->cmd = 0;
		else if (token_list[i] == TOKEN_WORD)
			token_list[i] = check_word(value_oftoken[i], boolean, env);
		else
			return;
		i++;
	}
	return;
}


/* int main(int argc, char **argv, char **env)
{
    // Créer une liste de tokens en utilisant un tableau de chaînes de caractères
	t_all	*p;

	(void)argc;
	(void) **argv;
	p = init_all(env);
	if (!p || p == NULL)
		return (EXIT_FAILURE);
    int tokens[] = {
		TOKEN_REDIRECTIN,
		TOKEN_WORD,
		TOKEN_WORD,
		TOKEN_HEREDOC,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_WORD,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_WORD,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_WORD,
		TOKEN_WORD,
		TOKEN_REDIRECTOUT,
		TOKEN_WORD
	};
	char *value[] = {"<","input.txt","/bin/cat","<<","LIMITER","'|'", "grep", "coucou","'|'","echo", "lol","'|'","ls","-l", ">", "output.txt"};
	t_word word;
	init_t_word(&word);
	define_word(value, tokens, &word, p->env);
	 int i = 0;
	while(tokens[i] && i < 16)
	{
        printf("%s            | token = %d\n",value[i], tokens[i]);
		i++;
	}
	free_all(p);
    return 0;
} */