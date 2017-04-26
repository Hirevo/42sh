/*
** server.h for server in /home/arthur/test_sock/server
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Wed Dec 21 20:06:39 2016 Arthur Knoepflin
** Last update Wed Apr 26 23:42:56 2017 Arthur Knoepflin
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# define	INVALID_SOCKET	-1
# define	SOCKET_ERROR	-1
# define	closesocket(s)	close(s)
typedef		int		t_socket;
typedef	struct	sockaddr_in	t_sockaddr_in;
typedef struct	sockaddr	t_sockaddr;

# define	MIMETYPE	"mimetype"
# define	CRLF		"\r\n"
# define	MAX_CLIENTS	4096
# define	CHROME		"google-chrome"
# define	FIREFOX		"firefox"
# define	MAGIC		"exec"
# define	PATH_WEB	"http://localhost:"
# define	PATH_DOC	"WebC/"
# define	NF_RESP		"HTTP/1.0 404\r\n\
Access-Control-Allow-Origin: *\r\n\r\n\
<!DOCTYPE html><html><head><title>Configuration</title></head>\
<body><h1>404 Not found</h1>\
Le fichier n'existe po</body>\
</html>"
# define	FB_RESP		"HTTP/1.0 403\r\n\
Access-Control-Allow-Origin: *\r\n\r\n\
<!DOCTYPE html><html><head><title>Configuration</title></head>\
<body><h1>403 Forbiden Acess</h1>\
Ta pas les perms frere</body>\
</html>"
# define	ERROR_RESP	"HTTP/1.0 500\r\n\
Access-Control-Allow-Origin: *\r\n\r\n\
<!DOCTYPE html><html><head><title>Configuration</title></head>\
<body><h1>Internal server error</h1></body></html>"
# define	BASE_RESP	"HTTP/1.0 200\r\n\
Access-Control-Allow-Origin: *\r\n\
Content-type: text/plain\r\n\r\n"
# define	HEAD_RESP	"HTTP/1.0 200\r\n\
Access-Control-Allow-Origin: *\r\n"
# define	BUF_SIZE	4096

/*
** add_env_http.c
*/

void	add_env_http(t_socket, char **, char ***);
void	del_env_http(t_socket, char **, char ***);
void	update_env_http(t_socket, char **, char ***);

/*
** char_double.c
*/

char	**add_to_chardouble(char *, char **);
char	**del_to_chardouble(char *, char **);

/*
** client.c
*/

void	remove_client(t_socket *, int, int *);
int	new_client(t_socket *, int *, fd_set *, t_socket);
int	client_talk(t_socket *, int *, fd_set *, char ***);

/*
** com_serv.c
*/

int	read_client(t_socket, char *);
void	write_client(t_socket, char *);

/*
** decode.c
*/

int	urldecode(char *, char *);

/*
** exec_cmd_http.c
*/

int	exec_cmd_http(t_socket, char **, char ***);

/*
** init_connection.c
*/

int	init_connection(t_socket *);

/*
** indexof.c
*/

int	indexof(char **, char *);

/*
** get_file_http.c
*/

char	*get_file_http(char *);

/*
** my_split_mulchar.c
*/

char	**my_split_mulchar(char *, char *);

/*
** response.c
*/

int	response(t_socket, char *, char ***);

/*
** send_file_http.c
*/

void	send_file_http(t_socket, char *);

/*
** send_mime.c
*/

void	send_mime(t_socket, char *);

static void end_connection(int sock);
static void clear_clients(t_socket *clients, int actual);
char	**my_split(char *, char *);
char	*int_toc(int);
char	**my_split_char(char *, char);
char	*find_navigator(char **);
int	launch_nav(char *, int, char **);
char	*get_env(char **, char *);
int	send_env(t_socket, char **);

#endif /* !SERVER_H_ */
