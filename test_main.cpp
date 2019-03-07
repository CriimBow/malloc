/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test_main.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ggranjon <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/05 12:20:44 by ggranjon     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/05 12:20:46 by ggranjon    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

int main()
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;
	char	*str5;
	char	*str6;
	char	*str7;
	char	*str8;

	str = (char*)malloc(11);
	str2 = (char*)malloc(120);
	str3 = (char*)malloc(31);
	str8 = (char*)malloc(12);
	str4 = (char*)malloc(129);
	str5 = (char*)malloc(513);
	str6 = (char*)malloc(1111);
	str7 = (char*)malloc(1111);

	strcpy(str, "test123");
	strcpy(str2, "test12345546557687");
	strcpy(str3, "test123456");
	strcpy(str4, "test1234567890");
	strcpy(str5, "test12345678901");
	strcpy(str6, "test123456789012");

	show_alloc_mem();
	str2 = (char*)realloc(str2, 43);
	printf("ab %li\n", sizeof(t_alloc_block));

	printf("str2 = %p %s\n", (void *)str2, str2);
	printf("str3 = %p %s\n", (void *)str3, str3);
	printf("str4 = %p %s\n", (void *)str4, str4);
	printf("str5 = %p %s\n", (void *)str5, str5);
	printf("str6 = %p %s\n", (void *)str6, str6);

	show_alloc_free_mem();
	free(str2);
	free(str2);
	free(str5);
	free(str6);
	show_alloc_free_mem();
	return 0;
}
