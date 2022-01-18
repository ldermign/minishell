/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fcts.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:26:06 by ldermign          #+#    #+#             */
/*   Updated: 2022/01/16 23:45:32 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FCTS_H
# define LIBFT_FCTS_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char				*ft_alloc_strcat(char *s1, char *s2);
char				*ft_alloc_strcpy(char *str);
int					ft_atoi(const char *str);
long long int		ft_atol(const char *str);
int					ft_binary(int nbr_to_convert);
void				ft_bzero(void *str, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_free_tab(char **str_tab);
int					ft_int_strchr(const char *str, int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
int					ft_len_int(int nbr);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstdel_all(t_list *alst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *str, int c, size_t len);
int					ft_pos_strchr(const char *str, int c);
int					ft_pos_strstr(char *str, char *needle);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr(int nb);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char *str);
void				ft_putstr_fd(char *s, int fd);
long				ft_random(int max);
char				**ft_split(char const *str, char c);
char				*ft_strcat(char *dst, char *src);
char				*ft_strchr(const char *str, int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcpy(char *dst, char *src);
char				*ft_strdup(char *str);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *dst, char *src, unsigned int nb);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, char *src, unsigned int n);
char				*ft_strnstr(const char *s1, const char *s2, size_t size);
char				*ft_strrchr(const char *str, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_swap(int *a, int *b);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif
