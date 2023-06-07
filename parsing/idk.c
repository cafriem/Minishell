

// if (newstr[w_c][0] == '<' || newstr[w_c][0] == '>')
// {
// 	if (newstr[w_c][0] == '>' && newstr[w_c][1] == '>')
// 	{
// 		command->redir[command->redir_amount].direct = APPEND;
// 		if (newstr[w_c][3] != '\0')
// 		{
// 			command->split_pipe = ft_substr(newstr[w_c], 3, ft_strlen(newstr[w_c]));
// 			free (newstr[w_c]);
// 			newstr[w_c] = ft_strdup(command->split_pipe);
// 			free (command->split_pipe);
// 			redirect_str(newstr[w_c], &command, command->redir_amount);
// 			w_c++;
// 		}
// 		else if (newstr[w_c + 1] && (newstr[w_c + 1][0] != '<' || newstr[w_c + 1][0] != '>'))
// 		{
// 			command->split_pipe = ft_substr(newstr[w_c], 3, ft_strlen(newstr[w_c]));
// 			free (newstr[w_c]);
// 			newstr[w_c] = ft_strdup(command->split_pipe);
// 			free (command->split_pipe);
// 			redirect_str(newstr[w_c + 1], &command, command->redir_amount);
// 		}
// 		command->redir_amount++;
// 		// else
// 		// 	FAIL ADD A FAIL PARSE ERROR
// 	}
// 	else if (newstr[w_c][0] == '<' && newstr[w_c][1] == '<')
// 	{
// 		command->redir[command->redir_amount].direct = HERE_DOC;
// 		if (newstr[w_c][3] != '\0')
// 			command->redir[command->redir_amount].file = ft_substr(newstr[w_c], 3, ft_strlen(newstr[w_c]));
// 		else if (newstr[w_c + 1])
// 			command->redir[command->redir_amount].file = ft_strdup(newstr[w_c + 1]);
// 		command->redir_amount++;
// 	}
// 	else if (newstr[w_c][0] == '>')
// 	{
// 		command->redir[command->redir_amount].direct = RE_OUTPUT;
// 		if (newstr[w_c][2] != '\0')
// 			command->redir[command->redir_amount].file = ft_substr(newstr[w_c], 2, ft_strlen(newstr[w_c]));
// 		else if (newstr[w_c + 1])
// 			command->redir[command->redir_amount].file = ft_strdup(newstr[w_c + 1]);
// 		command->redir_amount++;
// 	}
// 	else if (newstr[w_c][0] == '<')
// 	{
// 		command->redir[command->redir_amount].direct = RE_INPUT;
// 		if (newstr[w_c][2] != '\0')
// 			command->redir[command->redir_amount].file = ft_substr(newstr[w_c], 2, ft_strlen(newstr[w_c]));
// 		else if (newstr[w_c + 1])
// 			command->redir[command->redir_amount].file = ft_strdup(newstr[w_c + 1]);
// 		command->redir_amount++;
// 	}
// }
