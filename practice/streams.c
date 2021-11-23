#include <unistd.h>
#include <pthread.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && *str++)
		i++;
	return (i);
}

void *print(void *buf)
{
	int i;

	i = 0;
	while (i++ < 20)
	{
		write(1, (char *)buf, ft_strlen(buf));
		usleep(1000000);
	}
	return NULL;
}

int	main(int ac, char **av)
{
	char *str1;
	char *str2;
	pthread_t t1;
	pthread_t t2;

	str1 = "1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_\n";
	str2 = "_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2\n";
//	print((char *)str1);
	pthread_create(&t1, NULL, print, (void *)str1);
	pthread_create(&t2, NULL, print, (void *)str2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	usleep(3000000);
	write(1, "Exit\n", 5);
	return (0);
}