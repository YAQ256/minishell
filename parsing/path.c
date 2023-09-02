/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:33:53 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/02 08:33:40 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * La función `join_path` toma dos cadenas, `s1` y `s2`, y las concatena con un carácter '/' en el
 * medio, devolviendo la cadena resultante.
 * 
 * @param s1 Una cadena que representa la primera parte de la ruta.
 * @param s2 El parámetro `s2` en la función `join_path` es un puntero a una matriz de caracteres que
 * representa la segunda parte de la ruta que se unirá.
 * 
 * @return La función `join_path` devuelve un puntero a una matriz de caracteres (cadena) que
 * representa la ruta unida de `s1` y `s2`.
 */
char	*join_path(char *s1, char *s2)
{
	char	*output;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (s1[s1_len - 1] == '/')
		s1_len--;
	s2_len = ft_strlen(s2);
	if (s2[0] == '/')
		s2_len--;
	output = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!output)
		return (NULL);
	ft_memcpy(output, s1, s1_len);
	output[s1_len] = '/';
	ft_memcpy(output + s1_len + 1, s2, s2_len);
	output[s1_len + s2_len + 1] = '\0';
	return (output);
}

/**
 * La función `resolve_path` toma un nombre de archivo, una lista de variables de entorno y permisos
 * como entrada, y devuelve la ruta completa del archivo si existe y tiene los permisos especificados.
 * 
 * @param file Una cadena que representa el nombre del archivo o la ruta que debe resolverse.
 * @param envs Una lista enlazada de variables de entorno. Cada nodo de la lista contiene un par
 * clave-valor que representa una variable de entorno.
 * @param perms El parámetro `perms` en la función `resolve_path` es un número entero que representa
 * los permisos necesarios para acceder al archivo. Se utiliza en la función `acceso` para comprobar si
 * se puede acceder al archivo con los permisos dados.
 * 
 * @return La función `resolve_path` devuelve un `char*` que es la ruta resuelta del archivo de
 * entrada.
 */
char	*resolve_path(char *file, t_env *envs, int perms)
{
	t_env	*path;
	char	**paths;
	size_t	i;
	char	*output;

	if (!file || !file[0])
		return (NULL);
	if (access(file, perms) >= 0)
		return (ft_strdup(file));
	path = get_env(envs, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path->value, ':');
	i = 0;
	while (paths[i])
	{
		output = join_path(paths[i], file);
		if (access(output, perms) >= 0)
			break ;
		free(output);
		output = NULL;
		free(paths[i++]);
	}
	free(paths);
	return (output);
}
