/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:54:14 by gzovkic           #+#    #+#             */
/*   Updated: 2024/11/14 14:59:47 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
char	*make_str(char *buffer);
char	*leftover_check(char *buffer);
char	*line_return(char **container);
int		read_count(int fd, char **container);

char	*get_next_line(int fd)
{
	char		*rt_str;		// str den ich zurück gebe.
	int			byte_length;	// länge der gelesenen bytes.
	static char	*container;		// static char da dieser wert gespeichtert werden muss auch nach dem die funktion beendet wurden ist.

	if (fd < 0 || BUFFER_SIZE <= 0) 				// ob der buffer oder die file invalid ist.
		return (NULL);
	if (!container)									// erstellt den container wenn er nicht so erstellt worden ist.
		container = ft_calloc(1, sizeof(char)); 
	if (!container)
		return (NULL);								// wenn conatiner nicht erstellt werden konnte.
	byte_length = read_count(fd, &container); 		// erstellt im conatiner den ersten string und check ob noch was gelesen werden konnte.
	if (byte_length < 0 || (byte_length == 0 && (!container || !*container)))	//wenn readen gefailed ist oder wenn nichr mehr gelesen werden konnte
	{																			//und der container noch exestiert oder eine value im container ist.
		free(container);	//löscht den in inhalt vom container'
		container = NULL;	//setzt den container auf NULL weil er static ist.
		return (NULL);		// return NULL indikator das nicht mehr gelesen weren konnte,
	}
	rt_str = line_return(&container);	// sucht im container den sting und upadten den container mit den rest der noch im container liegt.
	return (rt_str);					// gubt den gefundenen string zurück.
}

char	*line_return(char **container)
{
	char	*rt_str;	// string der returned wird.
	char	*temp;		//wird benötigt um den container string zu updaten.

	rt_str = make_str(*container);	//suchtnach den ersten \n oder \0 und erstellt in rt_str die line.
	if (!rt_str)					// wenn die line nicht erstellt werden konnte
	{
		free(*container);			//löscht den in inhalt vom container' 
		*container = NULL;			//setzt den container auf NULL weil er static ist.
		return (NULL);				// return NULL indikator das nicht mehr gelesen weren konnte,
	}
	temp = leftover_check(*container);	//sucht nach dem ersten \n oder \0 und kopiert alles was nach dem string ist und speichert es in temp.
	free(*container);					//freed den container.
	*container = temp;					// setzt den pointer von temp zum container.
	return (rt_str);					// returned den gefundenen string.
}

int	read_count(int fd, char **container)
{
	char	buffer[BUFFER_SIZE + 1];	// erstellt den buffer wo das was gereadet wurde gespeicher wird, buffer + 1 das wir den \0 am ende hinzufügen.
	char	*str2;						// erstellt einen temp string wo der container geupdated wird.
	int		buffer_check;				// checkt ob noch was gereadet wurde.

	buffer_check = read(fd, buffer, BUFFER_SIZE);	//readet und speicher die gelesen anzahl der bytes in buffer_check.
	if (buffer_check < 0)							// wenn read eine negative zahl ist. ist der read fehlgeschlagen.
		return (-1);								// return -1 um den fehler anzuzeigen.
	while (buffer_check > 0)					//solange buffer_check einen positiven wert hat wurde was gelesen
	{
		buffer[buffer_check] = '\0';					//setzt auf das ende vom buffer ein \0 um das ende des buffers zu zu bestimmen.
		str2 = ft_strjoin(*container, buffer);			//fügt den container mit dem buffer zusammen und erstllt das ergebnis in str2.
		free(*container);								//freed den container.
		if (!str2)										//wenn str2 nicht erstellt werden konnte.
			return (*container = NULL, -1);				// setzt den container auf NULL und returnt -1.
		*container = str2;								// setzt den pointer von str2 wo der neu erstellte string ist auf container.
		if (ft_strchr(*container, '\n'))				// wenn container ein \n hat geht der aus dem loop raus .
			break ;										// breakt aus dem loop.
		buffer_check = read(fd, buffer, BUFFER_SIZE);	// readet noch mal neu um den loop weiterlaufen zu lassen wenn str noch kein \n hat.
	}
	return (buffer_check);	// return den die anzahl der gerade gelesen bytes.
}

char	*make_str(char *buffer)
{
	char			*str;
	unsigned int	count;
	unsigned int	count2;

	count = 0;
	count2 = 0;
	while (buffer[count] != '\n' && buffer[count] != '\0')
		count++;
	if (buffer[count] == '\n')
		str = ft_calloc(count + 2, sizeof(char));
	else
		str = ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (count > count2)
	{
		str[count2] = buffer[count2];
		count2++;
	}
	if (buffer[count2] == '\n')
		str[count2] = '\n';
	return (str);
}

char	*leftover_check(char *buffer)
{
	int		count;
	int		count2;
	char	*str;

	count = 0;
	count2 = 0;
	while (buffer[count] != '\n' && buffer[count] != '\0')
		count++;
	if (buffer[count] == '\0')
		return (NULL);
	str = ft_calloc(ft_strlen(buffer) - count + 1, sizeof(char));
	if (!str)
		return (NULL);
	count++;
	while (buffer[count] != '\0')
	{
		str[count2] = buffer[count];
		count++;
		count2++;
	}
	return (str);
}
