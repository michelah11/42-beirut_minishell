/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:43:32 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/03/08 19:55:10 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_mem
{
	void			*address;
	struct s_mem	*next;
}	t_mem;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_atoi(const char *nptr);
int				ft_lstsize(t_list *lst);
void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
char			*ft_strchr(char const *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strdup(const char *s);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstlast(t_list *lst);
t_mem			*insert_node(t_mem *node, void *value);
void			delete_list(t_mem *node);
void			*msh_malloc(size_t size, t_mem *node);
char			*msh_itoa(int n, t_mem *mem);
char			*msh_strdup(const char *s, t_mem *mem);
char			*msh_strjoin(char const *s1, char const *s2, t_mem *mem);
char			*msh_strmapi(char const *s, char (*f)(unsigned int, char),
					t_mem *mem);
char			*msh_substr(char const *s, unsigned int start, size_t len,
					t_mem *mem);
void			*msh_calloc(size_t nmemb, size_t size, t_mem *mem);
char			*msh_strtrim(char const *s1, char const *set, t_mem *mem);
char			**msh_split(char const *s, char c, t_mem *mem);
int				msh_isalnum(int c);
int				msh_isalpha(int c);
int				ft_strcmp(char *s1, char *s2);
long long int	msh_atoi(const char *nptr);

#endif
