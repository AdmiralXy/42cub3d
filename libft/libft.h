/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// Libraries

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// Constants

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Structures
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Functions
int		ft_abs(int value);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
int		ft_nbrcmp(int n1, int n2);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	ft_str_replace(char **str, const char *rep, const char *in, int start);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
void	ft_striclear(char *str, int index);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_strs_push_back(char **strs, const char *str);
char	**ft_strs_push_front(char **strs, const char *str);
char	**ft_strscopy(char **strs);
char	**ft_strscreate(char *str);
int		ft_strsfind(char **strs, const char *str);
void	ft_strsfree(char **strs);
char	**ft_strsjoin(char **strs1, char **strs2);
int		ft_strslen(char **strs);
void	ft_strssort(char **strs);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_wdcounter(const char *str, char separator);
void	ft_strpclear(char *str, char *address);
int		get_next_line(int fd, char **line);

#endif
